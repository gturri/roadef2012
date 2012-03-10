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

#ifndef SOLUTIONALG_HH
#define SOLUTIONALG_HH

#include <vector>
#include <cstring>

class ConstraintSystemALG;
class EvaluationSystemALG;
class RestrictionALG;

class SolutionALG
{
    public:
        explicit SolutionALG(size_t);
        ~SolutionALG();

        typedef int ProcessId;
        typedef int MachineId;

        static const MachineId unassigned;
        static const MachineId failToAssign;
                
        void addRestriction(RestrictionALG *); 
        void setpConstraintSystem(ConstraintSystemALG *); 
        void setpEvaluationSystem(EvaluationSystemALG *); 

        std::vector<ProcessId> getAvaiableProcesses() const;
        std::vector<MachineId> getAvaiableMachines(ProcessId) const;
        const std::vector<MachineId> &getSolution() const {return assignment_m;}

        void unassign(ProcessId);
        void assign(ProcessId, MachineId);

        double evaluate();
        
    private:
        typedef std::vector<RestrictionALG *> RestrictionPool;
        RestrictionPool restrictions_m;     
        
        typedef std::vector<MachineId> ExplicitRepresentation;
        ExplicitRepresentation assignment_m;

        ConstraintSystemALG * pConstraintSystem_m;
        EvaluationSystemALG * pEvaluationSystem_m;
        double incrementalValue_m;
};

#endif
