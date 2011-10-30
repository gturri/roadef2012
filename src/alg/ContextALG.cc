#include "alg/ContextALG.hh"
#include "bo/ContextBO.hh"
#include "bo/MachineBO.hh"
#include "bo/NeighborhoodBO.hh"
#include "bo/ProcessBO.hh"
#include "bo/ServiceBO.hh"
#include "dtoout/SolutionDtoout.hh"
#include "tools/Checker.hh"
#include <algorithm>
#include <cassert>
#include <boost/foreach.hpp>
#include <limits>
using namespace std;

ContextALG::ContextALG(ContextBO const * pContextBO_p, bool mustWriteBestSol_p, bool solInitToCheck_p) :
    pContextBO_m(pContextBO_p),
    currentSol_m(pContextBO_p->getSolInit()),
    bestScore_m(numeric_limits<int>::max()),
    mustWriteBestSol_m(mustWriteBestSol_p)
{}

void ContextALG::setMustWriteBestSol(bool mustWriteBestSol_p){
    mustWriteBestSol_m = mustWriteBestSol_p;
}

ContextBO const * ContextALG::getContextBO() const {
    return pContextBO_m;
}

const vector<int>& ContextALG::getCurrentSol() const {
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

int ContextALG::getRessUsedOnMachine(int idxRess_p, int idxMachine_p) const {
    int result_l(0);
    for ( int idxP_l=0 ; idxP_l < (int) currentSol_m.size() ; idxP_l++ ){
        if ( currentSol_m[idxP_l] == idxMachine_p ){
            result_l += pContextBO_m->getProcess(idxP_l)->getRequirement(idxRess_p);
        }
    }

    return result_l;
}

uint64_t ContextALG::getScoreBestSol() const {
    return bestScore_m;
}

bool ContextALG::checkCompletAndMajBestSol(const vector<int>& candidatBestSol_p, bool checkValidite_p){
    Checker checker_l(pContextBO_m, candidatBestSol_p);
    if ( checkValidite_p && !checker_l.isValid() ){
        return false;
    }

    return checkRapideAndMajBestSol(candidatBestSol_p, checker_l.computeScore());
}

bool ContextALG::checkRapideAndMajBestSol(const vector<int>& candidatBestSol_p, uint64_t score_p){
    return SolutionDtoout::writeSol(candidatBestSol_p, score_p);
}
