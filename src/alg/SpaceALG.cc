#include "SpaceALG.hh"


SpaceALG::SpaceALG()
: pContext_m(0)
{
}

SpaceALG::~SpaceALG()
{
}


void SpaceALG::addDecision(DecisionALG * decision_p)
{
}
 
SpaceALG::DecisionsPool SpaceALG::generateDecisions()
{
    return DecisionsPool();
}

SpaceALG::BoundValue SpaceALG::bound()
{
}   

SolutionALG * SpaceALG::buildSolution()
{
    return 0;
}

SpaceALG * SpaceALG::clone()
{
    return 0;
}
    
void SpaceALG::setpContext(ContextALG * pContext_p)
{
    pContext_m = pContext_p;
}

ContextALG * SpaceALG::getpContext() const
{
    return pContext_m;
}
