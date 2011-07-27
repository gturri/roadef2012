#ifndef SPACEALG_HH
#define SPACEALG_HH

#include <vector>

class ContextALG;
class DecisionALG;
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
        DecisionsPool generateDecisions();
        BoundValue bound();
        SolutionALG * buildSolution();
        SpaceALG * clone();

        void setpContext(ContextALG *);
        ContextALG * getpContext() const;

    private:
        ContextALG * pContext_m;
};

#endif
