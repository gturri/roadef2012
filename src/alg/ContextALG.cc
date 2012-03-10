/*
 * Copyright (c) 2011 Pierre-Etienne Bougué <pe.bougue(a)gmail.com>
 * Copyright (c) 2011 Florian Colin <florian.colin28(a)gmail.com>
 * Copyright (c) 2011 Kamal Fadlaoui <kamal.fadlaoui(a)gmail.com>
 * Copyright (c) 2011 Quentin Lequy <quentin.lequy(a)gmail.com>
 * Copyright (c) 2011 Guillaume Pinot <guillaume.pinot(a)tremplin-utc.net>
 * Copyright (c) 2011 Cédric Royer <cedroyer(a)gmail.com>
 * Copyright (c) 2011 Guillaume Turri <guillaume.turri(a)gmail.com>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */

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
    return SolutionDtoout::getBestScore();
}

bool ContextALG::checkCompletAndMajBestSol(const vector<int>& candidatBestSol_p, bool checkValidite_p){
    Checker checker_l(pContextBO_m, candidatBestSol_p);
    if ( checkValidite_p && !checker_l.isValid() ){
        return false;
    }

    return SolutionDtoout::writeSol(candidatBestSol_p, checker_l.computeScore());
}
