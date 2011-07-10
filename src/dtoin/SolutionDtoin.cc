#include "dtoin/SolutionDtoin.hh"
#include "bo/ContextBO.hh"
#include "bo/ProcessBO.hh"

void SolutionDtoin::read(istream& is_p, ContextBO* pContextBO_p){
    int nbProcesses_l = pContextBO_p->getNbProcesses();
    for ( int idxP_l=0 ; idxP_l < nbProcesses_l ; idxP_l++ ){
        int idxMachine_l;
        is_p >> idxMachine_l;
        MachineBO* pMachine_l = pContextBO_p->getMachine(idxMachine_l);
        pContextBO_p->getProcess(idxP_l)->setMachineInit(pMachine_l);
    }
}
