#include "gtests/tools/ParseCmdLineTestHelper.hh"
#include <cassert>
#include <cstring>

ParseCmdLineTestHelper::ParseCmdLineTestHelper() :
    argv_m(0),
    argvCreated_m(false)
{}

ParseCmdLineTestHelper::~ParseCmdLineTestHelper(){
    if ( argvCreated_m ){
        for ( int idx_l=0 ; idx_l < argc() ; idx_l++ ){
            delete[] argv_m[idx_l];
        }
    }

    delete[] argv_m;
}

char** ParseCmdLineTestHelper::argv(){
    if ( ! argvCreated_m ){
        argvCreated_m = true;
        int nbOpt_l = argc();
        argv_m = new char*[nbOpt_l];

        argv_m[0] = new char[15];
        strcpy(argv_m[0], "nomBinaire");

        for ( int idx_l=0 ; idx_l < (int) options_m.size() ; idx_l++ ){
            argv_m[idx_l+1] = new char[options_m[idx_l].size() + 1];
            strcpy(argv_m[idx_l+1], options_m[idx_l].c_str());
        }
    }

    return argv_m;
}

int ParseCmdLineTestHelper::argc(){
    return options_m.size()+1;
}

void ParseCmdLineTestHelper::addCmdLineArg(const string& arg_p){
    assert(!argvCreated_m);
    options_m.push_back(arg_p);
}
