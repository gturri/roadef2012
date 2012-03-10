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

#include "OPPMSpaceALG.hh"
#include "OPPMDecisionALG.hh"

#include "alg/ContextALG.hh"
#include "alg/MCTS/DecisionALG.hh"
#include "bo/ContextBO.hh"
#include "tools/Log.hh"
#include <list>

#include <iostream>
using namespace std;

OPPMSpaceALG::OPPMSpaceALG()
{
}

OPPMSpaceALG::~OPPMSpaceALG()
{
}

SpaceALG * OPPMSpaceALG::clone()
{
    OPPMSpaceALG * pClone_l = new OPPMSpaceALG;
    pClone_l->setpContext(getpContext());
    pClone_l->setpConstraintSystem(pConstraintSystem_m);
    pClone_l->setpEvaluationSystem(pEvaluationSystem_m);
    
    // transmission des decisions, memoire gerer par l'arbre
    for(DecisionsPool::iterator it_l = decisions_m.begin();
                                it_l != decisions_m.end();
                                ++it_l )
    {
        pClone_l->decisions_m.push_back(*it_l);
    }
    return pClone_l;
}

bool OPPMSpaceALG::isSolution() const
{
    ContextBO const * pContext_l = getpContext()->getContextBO();
    int nbProcesses_l = pContext_l->getNbProcesses();
    for(int process_l = 0; process_l < nbProcesses_l; ++process_l)
    {
        bool dontAppearInDecisions_l = true;
        for (DecisionsPool::const_iterator it_l = decisions_m.begin();
             it_l != decisions_m.end(); ++it_l) {
            if ( (*it_l)->workOnProcess(process_l)) {
                dontAppearInDecisions_l = false;
                break;
            }
        }
        if (dontAppearInDecisions_l) {
            return false;
        }
    }

    LOG(DEBUG) << "on a une solution" << std::endl;
    return true;
}

 
OPPMSpaceALG::DecisionsPool OPPMSpaceALG::generateDecisions() const
{
    ContextBO const * pContext_l = getpContext()->getContextBO();
    int target_l = -1;
    int nbProcesses_l = pContext_l->getNbProcesses();
    for(int process_l = 0; target_l == -1 && process_l<nbProcesses_l; ++process_l)
    {
        bool dontAppearInDecisions_l = true;
        for (DecisionsPool::const_iterator it_l = decisions_m.begin();
             dontAppearInDecisions_l && it_l != decisions_m.end();
             ++it_l)
        {
            if ( (*it_l)->workOnProcess(process_l))
            {
                dontAppearInDecisions_l = false;
            }
        }
        if (dontAppearInDecisions_l)
        {
            target_l = process_l;
        }
    }

    if (target_l == -1)
    {
        return DecisionsPool();
    }

    DecisionsPool returnedDecisions_l;
    int nbMachines_l = pContext_l->getNbMachines();
    for (int machine_l = 0; machine_l < nbMachines_l; ++machine_l)
    {
        OPPMDecisionALG * pDecision_l = new OPPMDecisionALG;
        OPPMDecisionALG::MachinePool pool_l;
        pool_l.push_back(machine_l);
        pDecision_l->setRestrictedSubset(pool_l);
        pDecision_l->setTarget(target_l);
        returnedDecisions_l.push_back(pDecision_l);
    }
    
    return returnedDecisions_l;
}
