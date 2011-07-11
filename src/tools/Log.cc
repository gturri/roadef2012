#include "tools/Log.hh"

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
