#ifndef PARSECMDLINEGENERATEUR_HH
#define PARSECMDLINEGENERATEUR_HH
#include <boost/program_options.hpp>
#include <string>
using namespace std;
using namespace boost::program_options;

class ParseCmdLineGenerateur{
    public:
        static variables_map parse(int argc, char** argv);

    protected:
        static void parseLine(variables_map& vm_p, const options_description& desc_p,  int argc, char** argv);
        static void parseCfgFile(variables_map& vm_p, const options_description& desc_p, const string& filename_p);

};

#endif
