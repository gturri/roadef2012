#include "alg/ContextALG.hh"
#include "bo/ContextBO.hh"
#include "bo/MachineBO.hh"
#include "bo/NeighborhoodBO.hh"
#include "bo/ProcessBO.hh"
#include "bo/ServiceBO.hh"
#include <algorithm>
#include <cassert>
#include <boost/foreach.hpp>
using namespace std;

ContextALG::ContextALG(ContextBO const * pContextBO_p) :
    pContextBO_m(pContextBO_p),
    currentSol_m(pContextBO_m->getSolInit())
{}

ContextBO const * ContextALG::getContextBO() const {
    return pContextBO_m;
}

vector<int> ContextALG::getCurrentSol() const {
    return currentSol_m;
}

void ContextALG::setCurrentSol(const vector<int>& curSol_p){
    assert((int) curSol_p.size() == pContextBO_m->getNbProcesses());
    currentSol_m = curSol_p;
}

unordered_set<int> ContextALG::getNeighsUsedByService(int idxService_p) const {
    return getNeighsUsedByService(pContextBO_m->getService(idxService_p));
}

unordered_set<int> ContextALG::getNeighsUsedByService(ServiceBO const * pService_p) const {
    unordered_set<int> result_l;
    BOOST_FOREACH(int idProcess_l, pService_p->getProcesses()){
        const int idxMachine_l = currentSol_m[idProcess_l];
        const int idxNeigh_l = pContextBO_m->getMachine(idxMachine_l)->getNeighborhood()->getId();
        result_l.insert(idxNeigh_l);
    }

    return result_l;
}
