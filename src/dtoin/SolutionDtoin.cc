#include "dtoin/SolutionDtoin.hh"
#include "bo/ContextBO.hh"
#include "bo/ProcessBO.hh"
#include "tools/Log.hh"
#include <fstream>
#include <sstream>

void SolutionDtoin::read(const string& solFileName_p, ContextBO* pContextBO_p){
    ifstream ifs_l(solFileName_p.c_str());
    if ( ! ifs_l ){
        ostringstream oss_l;
        oss_l << "Impossible d'ouvrir le fichier de solution a lire " << solFileName_p << endl;
        throw oss_l.str();
    }
    read(ifs_l, pContextBO_p);
}

void SolutionDtoin::read(istream& is_p, ContextBO* pContextBO_p){
    int nbProcesses_l = pContextBO_p->getNbProcesses();
    for ( int idxP_l=0 ; idxP_l < nbProcesses_l ; idxP_l++ ){
        int idxMachine_l;
        is_p >> idxMachine_l;
        MachineBO* pMachine_l = pContextBO_p->getMachine(idxMachine_l);
        pContextBO_p->getProcess(idxP_l)->setMachineInit(pMachine_l);
    }
    LOG(INFO) << "Fin de la lecture du fichier de solution initiale" << endl;
}
