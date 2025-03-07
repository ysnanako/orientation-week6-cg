#include "parser.h"
using namespace std;

void PARSER::GetFilename(const int& argc, char *argv[])
{
    if(argc == 3)
    {
        this->input_filename = argv[1];
        this->output_filename = argv[2];
    }
    else
    {
        cerr << "Error: Parser should be executed with input file and output file. \n";
        exit(EXIT_FAILURE);
    }
}
void PARSER::ReadFile(ALG &ALG_obj)
{
    fin.open(input_filename);
    if(!fin)
    {
        cerr << "Error: Input .txt file failed. \n";
        exit(EXIT_FAILURE);
    }
    string line;
    while(getline(fin, line))
    {
        if(line.size() < 6)
            continue;
        else if(line.substr(0, 3) == "Lib")
            CreatLib(ALG_obj, line);
        else if(line.substr(0, 4) == "Inst")
            CreatCell(ALG_obj, line);
        else if(line.substr(0, 3) == "Pad")
            CreatPad(ALG_obj, line);
        else if(line.substr(0, 3) == "Net")
            CreatNet(ALG_obj);
        else if(line.substr(0, 3) == "Pin")
            SetPin(ALG_obj, line);          
    }
    cout << "Read " << input_filename << " complete" << "\n"; // debug
    fin.close();
}
void PARSER::CreatLib(ALG &ALG_obj, string line)
{
    stringstream ss(line);
    string s, w, h;
    ss >> s >> s >> w >> h;
    CELL *new_ptr = new CELL(0, 0, stod(w), stod(h));
    ALG_obj.lib_vec.push_back(new_ptr);
}
void PARSER::CreatCell(ALG &ALG_obj, string line)
{
    stringstream ss(line);
    string s, x, y;
    ss >> s >> s >> s >> x >> y;
    size_t index = stoul(s.substr(2, 1)) - 1;
    CELL *lib_ptr = ALG_obj.lib_vec[index];
    CELL *new_ptr = new CELL(stod(x), stod(y), lib_ptr->width, lib_ptr->height);
    ALG_obj.cell_vec.push_back(new_ptr);
}
void PARSER::CreatPad(ALG &ALG_obj, string line)
{
    stringstream ss(line);
    string s, x, y;
    ss >> s >> s >> x >> y;
    CELL *new_ptr = new CELL(stod(x), stod(y), 1, 1);
    ALG_obj.pad_vec.push_back(new_ptr);
}
void PARSER::CreatNet(ALG &ALG_obj)
{
    cur_net_ptr = new NET;
    ALG_obj.net_vec.push_back(cur_net_ptr);
}
void PARSER::SetPin(ALG &ALG_obj, string line)
{
    size_t index = stoul(line.substr(5, 1)) - 1;
    if(line[4] == 'C')
    {
        ALG_obj.cell_vec[index]->pin_net_vec.push_back(cur_net_ptr);
        cur_net_ptr->pin_cell_vec.push_back(ALG_obj.cell_vec[index]);
    }
    if(line[4] == 'P')
    {
        ALG_obj.pad_vec[index]->pin_net_vec.push_back(cur_net_ptr);
        cur_net_ptr->pin_pad_vec.push_back(ALG_obj.pad_vec[index]);
    }  
}
void PARSER::WriteFile(ALG &ALG_obj)
{
    fout.open(output_filename);
    if(!fout)
    {
        cerr << "Error : Output file failed. \n";
        exit(EXIT_FAILURE);
    }
    fout << "COLOR gray\n";
    fout << "SR 0 -0 120 -120\n";
    for(auto cell : ALG_obj.cell_vec)
    {
        fout << "COLOR green\n";
        fout << "SRF " << cell->x << " " << -cell->y << " ";
        fout << cell->x + cell->width << " " << -cell->y - cell->height << "\n";
    }
    for(auto pad : ALG_obj.pad_vec)
    {
        fout << "COLOR cyan\n";
        fout << "SRF " << pad->x << " " << -pad->y << " ";
        fout << pad->x + pad->width << " " << -pad->y - pad->height << "\n";
    }
    for(auto net : ALG_obj.net_vec)
    {
        fout << "COLOR blue\n";
        fout << "SL ";
        for(auto pin_cell : net->pin_cell_vec)
        {
            fout << pin_cell->x + pin_cell->width / 2 << " ";
            fout << -pin_cell->y - pin_cell->height / 2 << " ";
        }
        for(auto pin_pad : net->pin_pad_vec)
        {
            fout << pin_pad->x + pin_pad->width / 2 << " ";
            fout << -pin_pad->y - pin_pad->height / 2 << " ";
        }
        fout << "\n";
    }
    cout << "Write " << output_filename << " complete" << "\n"; // debug
    fout.close();
}