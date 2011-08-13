#include "SpaceALG.hh"

#include "SolutionALG.hh"
#include "DecisionALG.hh"
#include "RestrictionALG.hh"
#include "MonteCarloSimulationALG.hh"

SpaceALG::SpaceALG()
: pContext_m(0)
{
}

SpaceALG::~SpaceALG()
{
}


void SpaceALG::addDecision(DecisionALG * decision_p)
{
    decisions_m.push_back(decision_p);
}
 
SpaceALG::DecisionsPool SpaceALG::generateDecisions() const
{
    return DecisionsPool();
}

SpaceALG::BoundValue SpaceALG::bound() const
{
    return 0;
}   

bool SpaceALG::isSolution() const
{
    return false;
}

SolutionALG * SpaceALG::buildSolution() const
{
    SolutionALG * pSolution_l = new SolutionALG;
    for (DecisionsPool::const_iterator it_l=decisions_m.begin(); 
                                       it_l != decisions_m.end(); 
                                       ++it_l)
    {
        DecisionALG * pDec_l = *it_l;
        RestrictionALG * pRestriction_l = pDec_l->getRestriction(pSolution_l);
        pSolution_l->addRestriction(pRestriction_l);        
    }
    MonteCarloSimulationALG monteCarlo_l;
    monteCarlo_l.run(pSolution_l);
    
    return pSolution_l;
}

SpaceALG * SpaceALG::clone()
{
    SpaceALG * pClone_l = new SpaceALG;
    pClone_l->decisions_m = decisions_m;
    return pClone_l;
}
    
void SpaceALG::setpContext(ContextALG * pContext_p)
{
    pContext_m = pContext_p;
}

ContextALG * SpaceALG::getpContext() const
{
    return pContext_m;
}
