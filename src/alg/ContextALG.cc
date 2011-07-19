#include "alg/ContextALG.hh"
#include "bo/ContextBO.hh"
#include "bo/MachineBO.hh"
#include "bo/ProcessBO.hh"
#include <algorithm>
using namespace std;

ContextALG::ContextALG(ContextBO const * pContextBO_p) :
    pContextBO_m(pContextBO_p)
{
    const int nbProcesses_l = pContextBO_m->getNbProcesses();
    currentSol_m.reserve(nbProcesses_l);

    for ( int idxP_l=0 ; idxP_l < nbProcesses_l ; idxP_l++ ){
        currentSol_m.push_back(pContextBO_m->getProcess(idxP_l)->getMachineInit()->getId());
    }
}

ContextBO const * ContextALG::getContextBO() const {
    return pContextBO_m;
}

vector<int> ContextALG::getCurrentSol() const {
    return currentSol_m;
}
