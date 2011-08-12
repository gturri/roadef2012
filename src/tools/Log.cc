#include "tools/Log.hh"
#include <boost/regex.hpp>
using namespace boost;

vector<string> LogHelper::vLogStrLvl_g = LogHelper::buildLogLvl();

/* Ci dessous : duplication de code, car on "redefinit" les levels de log
 * Ceci s'explique par le fait que dans le .hh on s'adresse au preprocesseur,
 * et ici, au compilo.
 *
 * Et puis de toute facon, c'est pas un "tool" qui va etre appelle a subir
 * de grosses maintenances, donc je ne pense pas que se soit si genant...
 */
vector<string> LogHelper::buildLogLvl(){
    vector<string> result_l;
    result_l.push_back("USELESS");
    result_l.push_back("DEBUG");
    result_l.push_back("INFO");
    result_l.push_back("WARNING");
    result_l.push_back("ERREUR");
    result_l.push_back("WTF");

    return result_l;
}

string LogHelper::extractFilename(const string& path_p){
    const static regex regex_l("([[:alpha:].]*)\\z");
    smatch match_l;
    if ( regex_search(path_p, match_l, regex_l) ){
        return match_l[1];
    } else {
        return path_p;
    }
}
