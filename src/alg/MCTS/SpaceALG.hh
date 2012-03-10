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

#ifndef SPACEALG_HH
#define SPACEALG_HH

#include <vector>
#include <stdint.h>

class ConstraintSystemALG;
class ContextALG;
class DecisionALG;
class EvaluationSystemALG;
class RestrictionALG;
class SolutionALG;


/** Brouillon d'une classe Space qui represente la forme courante de l'espace
    des solutions. Elle s'appuyera completer au fur et a mesure du parcours de
    l'arbre de decision
*/

class SpaceALG
{
    public:
        SpaceALG();
        virtual ~SpaceALG();

        typedef double BoundValue;
        typedef std::vector<DecisionALG *> DecisionsPool;

        virtual void addDecision(DecisionALG *);
        virtual DecisionsPool generateDecisions() const;
        virtual BoundValue bound() const;
        virtual bool isSolution() const;
        virtual double evaluate() const;
        virtual SpaceALG * clone();

        virtual void setpContext(ContextALG *);
        virtual ContextALG * getpContext() const;

        virtual void setpConstraintSystem(ConstraintSystemALG *); 
        virtual void setpEvaluationSystem(EvaluationSystemALG *); 

    protected:
        uint64_t origEval_m;
        ContextALG * pContext_m;
        EvaluationSystemALG * pEvaluationSystem_m;
        ConstraintSystemALG * pConstraintSystem_m;
        DecisionsPool decisions_m;
};

#endif
