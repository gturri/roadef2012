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

#include "SolutionALG.hh"
#include "RestrictionALG.hh"
#include "ConstraintSystemALG.hh"
#include "EvaluationSystemALG.hh"

#include <list>

const SolutionALG::MachineId SolutionALG::unassigned = -1;
const SolutionALG::MachineId SolutionALG::failToAssign = -2;

SolutionALG::SolutionALG(size_t nbProcesses_p)
:assignment_m(nbProcesses_p,unassigned),incrementalValue_m(0.0)
{
}

SolutionALG::~SolutionALG()
{
    for (RestrictionPool::const_iterator it_l = restrictions_m.begin(); 
         it_l != restrictions_m.end(); ++it_l) {
        RestrictionALG * pRestriction_l = *it_l;
        if (pRestriction_l != pConstraintSystem_m)
            delete pRestriction_l;
    }
}

void SolutionALG::unassign(ProcessId process_p)
{
    pConstraintSystem_m->unassign(process_p, assignment_m[process_p]);
    assignment_m[process_p] = unassigned;
}

void SolutionALG::assign(ProcessId process_p, MachineId machine_p)
{
   assignment_m[process_p] = machine_p;
   pConstraintSystem_m->assign(process_p, machine_p);
}

double SolutionALG::evaluate()
{
    return pEvaluationSystem_m->evaluate(assignment_m);
}

std::vector<SolutionALG::ProcessId> SolutionALG::getAvaiableProcesses() const
{
    std::vector<SolutionALG::ProcessId> return_l;
    
    std::vector<ProcessId> unassigned_l;
    ProcessId current_l = 0;
    ProcessId end_l = assignment_m.size();
    for( ; current_l < end_l; ++current_l)
    {
        if (assignment_m[current_l] == unassigned)
        {
            unassigned_l.push_back(current_l);
        }
    }
    
    for (RestrictionPool::const_iterator it_l = restrictions_m.begin(); 
                                         it_l != restrictions_m.end();
                                         ++it_l)
    {
        RestrictionALG * pRestriction_l = *it_l;
        pRestriction_l->filter(unassigned_l);
    }
    
    return_l.insert(return_l.begin(), unassigned_l.begin(), unassigned_l.end());
    
    return return_l;
}
        
std::vector<SolutionALG::MachineId> 
    SolutionALG::getAvaiableMachines(ProcessId process_p) const
{
    std::vector<SolutionALG::MachineId> return_l;
    
    std::vector<MachineId> possibles_l = pConstraintSystem_m->getLegalMachinePool(process_p);
     
    for (RestrictionPool::const_iterator it_l = restrictions_m.begin(); 
                                         it_l != restrictions_m.end();
                                         ++it_l)
    {
        RestrictionALG * pRestriction_l = *it_l;
        pRestriction_l->filter(process_p,possibles_l);
    }
    
    return_l.insert(return_l.begin(), possibles_l.begin(), possibles_l.end());
    
    return return_l;
}

void SolutionALG::addRestriction(RestrictionALG * pRestriction_p)
{
    restrictions_m.push_back(pRestriction_p);
}

void SolutionALG::setpConstraintSystem(ConstraintSystemALG * pSystem_p)
{
    pConstraintSystem_m = pSystem_p;
    addRestriction(pConstraintSystem_m);
}

void SolutionALG::setpEvaluationSystem(EvaluationSystemALG * pSystem_p)
{
    pEvaluationSystem_m = pSystem_p;
}
