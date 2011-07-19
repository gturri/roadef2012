#include "generateur/ParseCmdLine.hh"
#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

variables_map ParseCmdLine::parse(int argc_p, char** argv_p){
    variables_map result_l;
    options_description desc_l("Options autorisees");
    desc_l.add_options()
        ("help,h", "genere ce message et arrete l'execution")
        ("strategy,s", value<string>()->default_value("default"), "Specifie la strategy de generation a adopter")
        ("writer,w", value<string>()->default_value("default"), "Specifie le format de la sortie")
        ("out,o", value<string>()->default_value(""), "Prefixe des fichiers a ecrire (peut eventuellement contenir un path)")
        ("fromExistingInst", value<string>(), "Dans le cas d'une generation depuis une instance existante, specifie le fichier decrivant cette instance initiale")
        ("fromExistingSol", value<string>(), "Dans le cas d'une generation depuis une intance existante, specifie le fichier decrivant la solution initiale");

    try {
        store(parse_command_line(argc_p, argv_p, desc_l), result_l);
        notify(result_l);

        if ( result_l.count("help") ){
            cout << desc_l << endl;
            exit(0);
        }
    }catch(exception& err_l) {
        cerr << "Erreur de lecture de la ligne de commande : " << err_l.what() << endl;
        cerr << desc_l << endl;
    }

    return result_l;
}
