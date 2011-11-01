#include "dtoout/SolutionDtoout.hh"
#include "tools/ParseCmdLine.hh"
#include <iostream>
using namespace std;

#define TEAM_ID "S32"

string ParseCmdLine::getHelp(){
    ostringstream oss_l;
    oss_l << getOptions()
        << "  -name                    Affiche l'id de l'equipe" << endl;
    return oss_l.str();
}

options_description ParseCmdLine::getOptions(){
    options_description result_l("Options autorisees");
    result_l.add_options()
        ("help,h", "genere ce message et arrete l'execution")
        ("time,t", value<int>()->default_value(300), "temps max du run (en secondes)")
        ("param,p", value<string>()->default_value(""), "Nom du fichier d'instance")
        ("init,i", value<string>()->default_value(""), "Nom du fichier de solution initiale")
        ("out,o", value<string>()->default_value("defaultOutfile.txt"), "Nom du fichier a ecrire")
        ("seed,s", value<int>()->default_value(0), "graine du generateur aleatoire")
        ("name", value<string>(), "Affiche l'id de l'equipe")
        ("strategy", value<string>(), "Nom de la strategy a construire");

    return result_l;
}

variables_map ParseCmdLine::parse(int argc_p, char** argv_p){
    variables_map result_l;

    try {
        store(command_line_parser(argc_p, argv_p).
                options(getOptions()).
                allow_unregistered().
                extra_parser(parseName).
                run(), result_l
                );
        notify(result_l);
    }catch(exception& err_l) {
        cerr << "Erreur de lecture de la ligne de commande : " << err_l.what() << endl;
        cerr << getHelp() << endl;
        exit(-1);
    }

    return result_l;
}

pair<string, string> parseName(const string& arg_p){
    if ( arg_p == "-name" ){
        return make_pair("name", "true");
    } else {
        return make_pair(string(), string());
    }
}

void ParseCmdLine::traitementOptionsSimples(const variables_map& opt_p){
    if ( opt_p.count("help") ){
        cout << getHelp() << endl;
        exit(0);
    }

    if ( opt_p.count("name") ){
        cout << TEAM_ID << endl;
        if ( opt_p["param"].as<string>() == "" ){
            exit(0);
        }
    }

    string outFileName_l = opt_p["out"].as<string>();
    SolutionDtoout::setOutFileName(outFileName_l);

}
