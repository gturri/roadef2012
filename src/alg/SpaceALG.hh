#ifndef SPACEALG_HH
#define SPACEALG_HH

#include <vector>

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
        int origEval_m;
        ContextALG * pContext_m;
        EvaluationSystemALG * pEvaluationSystem_m;
        ConstraintSystemALG * pConstraintSystem_m;
        DecisionsPool decisions_m;
};

#endif
