#ifndef PARSECMDLINE_HH
#define PARSECMDLINE_HH
#include <boost/program_options.hpp>
using namespace boost::program_options;

class ParseCmdLine{
    public:
        static variables_map parse(int argc, char** argv);
};

#endif
