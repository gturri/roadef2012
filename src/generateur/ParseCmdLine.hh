#ifndef PARSECMDLINE_HH
#define PARSECMDLINE_HH
#include <boost/program_options.hpp>
#include <string>
using namespace std;
using namespace boost::program_options;

class ParseCmdLine{
    public:
        static variables_map parse(int argc, char** argv);

    protected:
        static void parseLine(variables_map& vm_p, const options_description& desc_p,  int argc, char** argv);
        static void parseCfgFile(variables_map& vm_p, const options_description& desc_p, const string& filename_p);

};

#endif
