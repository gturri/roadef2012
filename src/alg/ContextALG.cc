#include "alg/ContextALG.hh"
#include "bo/ContextBO.hh"
#include "bo/MachineBO.hh"
#include "bo/ProcessBO.hh"
#include <algorithm>
#include <cassert>
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
    assert(curSol_p.size() == pContextBO_m->getNbProcesses());
    currentSol_m = curSol_p;
}
