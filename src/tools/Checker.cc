#include "tools/Checker.hh"
#include "tools/Log.hh"
#include "alg/ContextALG.hh"
#include "bo/ContextBO.hh"
#include "bo/LocationBO.hh"
#include "bo/MachineBO.hh"
#include "bo/ProcessBO.hh"
#include "bo/RessourceBO.hh"
#include "bo/ServiceBO.hh"
#include <set>
#include <vector>
using namespace std;

Checker::Checker(ContextALG const * pContextALG_p) :
    pContextALG_m(pContextALG_p)
{}

Checker::Checker()
{}

void Checker::setContextALG(ContextALG const * pContextALG_p){
    pContextALG_m = pContextALG_p;
}

bool Checker::isValid(){
    return checkCapaIncludingTransient()
        && checkConflict()
        && checkSpread()
        && checkDependances();
}

int Checker::computeScore(){
    return computeLoadCost()
        + computeBalanceCost()
        + computePMC()
        + computeSMC()
        + computeMMC();
}

bool Checker::checkCapaIncludingTransient(){
    ContextBO const * pContextBO_l = pContextALG_m->getContextBO();
    const int nbRess_l = pContextBO_l->getNbRessources();

    for ( int idxRess_l=0 ; idxRess_l < nbRess_l ; idxRess_l++ ){
        RessourceBO const * pRess_l = pContextBO_l->getRessource(idxRess_l);
        if ( ! checkCapaIncludingTransient(pRess_l) ){
            return false;
        }
    }
    return true;
}

bool Checker::checkCapaIncludingTransient(RessourceBO const * pRess_p){
    ContextBO const * pContextBO_l = pContextALG_m->getContextBO();
    const vector<int> currentSol_l = pContextALG_m->getCurrentSol();
    vector<int> vUsedRess_l(pContextBO_l->getNbMachines(), 0);

    const int nbProcess_l = pContextBO_l->getNbProcesses();
    for ( int idxP_l=0 ; idxP_l < nbProcess_l ; idxP_l++ ){
        ProcessBO const * pProcess_l = pContextBO_l->getProcess(idxP_l);
        const int idxCurMachine_l = currentSol_l[idxP_l];
        vUsedRess_l[idxCurMachine_l] += pProcess_l->getRequirement(pRess_p);

        if ( pRess_p->isTransient() ){
            int idxMachineInit_l = pProcess_l->getMachineInit()->getId();
            if ( idxCurMachine_l != idxMachineInit_l ){
                vUsedRess_l[idxMachineInit_l] += pProcess_l->getRequirement(pRess_p);
            }
        }
    }

    const int nbMachines_l = pContextBO_l->getNbMachines();
    for ( int idxMachine_l=0 ; idxMachine_l < nbMachines_l ; idxMachine_l++ ){
        const int capa_l = pContextBO_l->getMachine(idxMachine_l)->getCapa(pRess_p);
        if ( vUsedRess_l[idxMachine_l] > capa_l ){
            LOG(DEBUG) << "La solution viole la contrainte de capa pour la ressource " 
                << pRess_p->getId() << " sur la machine " << idxMachine_l 
                << " (requirement : " << vUsedRess_l[idxMachine_l] << ", capa : " << capa_l << ")" << endl;
            return false;
        }
    }

    return true;
}

bool Checker::checkConflict(){
    set<pair<int, int> > assocesMachineService_l;
    const vector<int> curSol_l = pContextALG_m->getCurrentSol();
    ContextBO const * pContextBO_l = pContextALG_m->getContextBO();

    for ( int idxP_l=0 ; idxP_l < pContextBO_l->getNbProcesses() ; idxP_l++ ){
        const int idxCurMachine_l = curSol_l[idxP_l];
        const int idxService_l = pContextBO_l->getProcess(idxP_l)->getService()->getId();
        pair<int, int> assoceMachineService_l(idxCurMachine_l, idxService_l);
        if ( assocesMachineService_l.find(assoceMachineService_l) != assocesMachineService_l.end() ){
            LOG(DEBUG) << "La solution viole la contrainte de conflit : plusieurs processes du service "
                << idxService_l << " sur la machine " << idxCurMachine_l << endl;
            return false;
        }
        assocesMachineService_l.insert(assoceMachineService_l);
    }

    return true;
}

bool Checker::checkSpread(){
    const vector<int> curSol_l = pContextALG_m->getCurrentSol();
    ContextBO const * pContextBO_l = pContextALG_m->getContextBO();
    vector<set<int> > memory_l(pContextBO_l->getNbServices());; //memory_l[idxService] => liste des locations utilisees

    for ( int idxP_l=0 ; idxP_l < pContextBO_l->getNbProcesses() ; idxP_l++ ){
        const int idxService_l = pContextBO_l->getProcess(idxP_l)->getService()->getId();
        const int idxLocation_l = pContextBO_l->getMachine(curSol_l[idxP_l])->getLocation()->getId();
        memory_l[idxService_l].insert(idxLocation_l);
    }

    for ( int idxS_l=0 ; idxS_l < pContextBO_l->getNbServices() ; idxS_l++ ){
        const int spreadMin_l = pContextBO_l->getService(idxS_l)->getSpreadMin();
        if ( spreadMin_l > (int) memory_l[idxS_l].size() ){
            LOG(DEBUG) << "La solution viole la contrainte de spread : le service "
                << idxS_l << " s'etend sur " << memory_l[idxS_l].size() 
                << " locations mais a un spread min de " << spreadMin_l << endl;
            return false;
        }
    }

    return true;
}

bool Checker::checkDependances(){
    return true;
}

int Checker::computeLoadCost(){
    return 0;
}

int Checker::computeBalanceCost(){
    return 0;
}

int Checker::computePMC(){
    return 0;
}

int Checker::computeSMC(){
    return 0;
}

int Checker::computeMMC(){
    return 0;
}

