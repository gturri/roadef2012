#include "generateur/ParseCmdLine.hh"
#include <string>
using namespace std;

variables_map ParseCmdLine::parse(int argc_p, char** argv_p){
    options_description desc_l("Options autorisees");
    desc_l.add_options()
        ("help", "genere ce message")
        ("strategy,s", value<string>(), "Specifie la strategy de generation a adopter");

    variables_map result_l;
    store(parse_command_line(argc_p, argv_p, desc_l), result_l);
    notify(result_l);

    if ( result_l.count("help") ){
        cout << desc_l << endl;
    }

    return result_l;
}
