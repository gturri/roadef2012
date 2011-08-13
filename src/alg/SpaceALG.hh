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
        ~SpaceALG();

        typedef double BoundValue;
        typedef std::vector<DecisionALG *> DecisionsPool;

        void addDecision(DecisionALG *);
        DecisionsPool generateDecisions() const;
        BoundValue bound() const;
        bool isSolution() const;
        SolutionALG * buildSolution() const;
        SpaceALG * clone();

        void setpContext(ContextALG *);
        ContextALG * getpContext() const;

        void setpConstraintSystem(ConstraintSystemALG *); 
        void setpEvaluationSystem(EvaluationSystemALG *); 

    private:        
        ContextALG * pContext_m;
        EvaluationSystemALG * pEvaluationSystem_m;
        ConstraintSystemALG * pConstraintSystem_m;
        DecisionsPool decisions_m;
};

#endif
