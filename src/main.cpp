#include "alg.h"
#include "parser.h"
using namespace std;

int main(int argc, char *argv[])
{  
    PARSER PARSER_obj;
    ALG ALG_obj;
    
    PARSER_obj.GetFilename(argc, argv);
    PARSER_obj.ReadFile(ALG_obj);

    ALG_obj.Iterate();
    
    PARSER_obj.WriteFile(ALG_obj);

    return EXIT_SUCCESS; 
}