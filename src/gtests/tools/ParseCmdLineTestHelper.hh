#ifndef PARSECMDLINETESTHELPER_HH
#define PARSECMDLINETESTHELPER_HH
#include <string>
#include <vector>
using namespace std;

class ParseCmdLineTestHelper{
    public:
        ParseCmdLineTestHelper();
        ~ParseCmdLineTestHelper();

        char** argv();
        int argc();
    
        void addCmdLineArg(const string& arg_p);

    private:
        vector<string> options_m;
        char** argv_m;

        /**
         * Permet de savoir s'il faut deleter #argv_m
         */
        bool argvCreated_m;
};

#endif
