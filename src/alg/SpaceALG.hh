#ifndef SPACEALG_HH
#define SPACEALG_HH

#include <vector>

class ContextALG;
class DecisionALG;
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

    private:        
        ContextALG * pContext_m;
        DecisionsPool decisions_m;
};

#endif
