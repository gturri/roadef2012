#include "tools/Log.hh"

vector<string> LogHelper::vLogStrLvl_g;

/* Ci dessous : duplication de code, car on "redefinit" les levels de log
 * Ceci s'explique par le fait que dans le .hh on s'adresse au preprocesseur,
 * et ici, au compilo.
 *
 * Et puis de toute facon, c'est pas un "tool" qui va etre appelle a subir
 * de grosses maintenances, donc je ne pense pas que se soit si genant...
 */
void LogHelper::init(){
    static bool initDone_l(false);
    if ( initDone_l ){
        return;
    }
    initDone_l = true;
    vLogStrLvl_g.push_back("USELESS");
    vLogStrLvl_g.push_back("DEBUG");
    vLogStrLvl_g.push_back("INFO");
    vLogStrLvl_g.push_back("WARNING");
    vLogStrLvl_g.push_back("ERREUR");
    vLogStrLvl_g.push_back("WTF");
}
