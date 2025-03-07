#ifndef _PARSER_H_
#define _PARSER_H_

#include <bits/stdc++.h>
#include "alg.h"
using namespace std;

class PARSER
{
    public:
    string input_filename, output_filename;
    void GetFilename(const int& argc, char *argv[]);
    void ReadFile(ALG &);
    void WriteFile(ALG &);
    private:
    ifstream fin;
    ofstream fout;
    NET *cur_net_ptr;
    void CreatLib(ALG &, string);
    void CreatCell(ALG &, string);
    void CreatPad(ALG &, string);
    void CreatNet(ALG &);
    void SetPin(ALG &, string);
};

#endif