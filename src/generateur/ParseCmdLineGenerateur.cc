#include "generateur/ParseCmdLineGenerateur.hh"
#include "tools/Log.hh"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void ParseCmdLineGenerateur::parseLine(variables_map& vm_p, const options_description& desc_p, int argc_p, char** argv_p){
    try {
        store(parse_command_line(argc_p, argv_p, desc_p), vm_p);
        notify(vm_p);
    }catch(exception& err_l) {
        cerr << "Erreur de lecture de la ligne de commande : " << err_l.what() << endl;
        cerr << desc_p << endl;
        exit(-1);
    }
}

void ParseCmdLineGenerateur::parseCfgFile(variables_map& vm_p, const options_description& desc_p, const string& filename_p){
    ifstream ifs_l(filename_p.c_str());
    if ( ! ifs_l ){
        LOG(WARNING) << "Impossible d'ouvrir le fichier d'options du generateur d'instances (" << filename_p << "). Celui-ci est ignore" << endl;
        return;
    }

    try {
        store(parse_config_file(ifs_l, desc_p), vm_p);
        notify(vm_p);
    }catch(exception& err_l) {
        cerr << "Erreur de lecture du fichier d'options du generateur d'instances (" << filename_p << ") : " << err_l.what() << endl;
        cerr << desc_p << endl;
        exit(-1);
    }
}

variables_map ParseCmdLineGenerateur::parse(int argc_p, char** argv_p){
    variables_map result_l;
    options_description desc_l("Options autorisees");
    desc_l.add_options()
        ("help,h", "genere ce message et arrete l'execution")
        ("strategy,s", value<string>()->default_value("default"), "Specifie la strategy de generation a adopter")
        ("writer,w", value<string>()->default_value("default"), "Specifie le format de la sortie")
        ("out,o", value<string>()->default_value(""), "Prefixe des fichiers a ecrire (peut eventuellement contenir un path)")
        ("fromExistingInst", value<string>(), "Dans le cas d'une generation depuis une instance existante, specifie le fichier decrivant cette instance initiale")
        ("fromExistingSol", value<string>(), "Dans le cas d'une generation depuis une intance existante, specifie le fichier decrivant la solution initiale")
        ("optionFile", value<string>(), "Nom d'un fichier contenant des options");

    parseLine(result_l, desc_l, argc_p, argv_p);
    if ( result_l.count("optionFile") ){
        parseCfgFile(result_l, desc_l, result_l["optionFile"].as<string>());
    }

    if ( result_l.count("help") ){
        cout << desc_l << endl;
        exit(0);
    }

    return result_l;
}
