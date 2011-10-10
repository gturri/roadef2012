#ifndef PARSECMDLINE_HH
#define PARSECMDLINE_HH
#include <boost/program_options.hpp>
#include <map>
#include <string>
using namespace std;
using namespace boost::program_options;

class ParseCmdLine{
    public:
        static variables_map parse(int argc, char** argv);

        /**
         * Genere le message d'aide
         */
        static string getHelp();

        /**
         * Execute apres le parsage, pour gerer le cas des options qui peuvent l'etre ici
         */
        static void traitementOptionsSimples(const variables_map& opt_p);

    protected:
        static options_description getOptions();
};


pair<string, string> parseName(const string& arg_p);

#endif
