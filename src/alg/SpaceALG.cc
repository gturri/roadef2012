#include "SpaceALG.hh"

#include "ContextALG.hh"
#include "SolutionALG.hh"
#include "DecisionALG.hh"
#include "RestrictionALG.hh"
#include "MonteCarloSimulationALG.hh"

#include <iostream>
#include "bo/ContextBO.hh"

SpaceALG::SpaceALG()
: pContext_m(0), decisions_m()
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
    std::cerr << "Mauvaise surcharge" << std::endl;
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
    ContextBO const * pContext_l = getpContext()->getContextBO();
    int nbProcesses_l = pContext_l->getNbProcesses();
    
    std::cerr << "On construit une solution" << std::endl;
    SolutionALG * pSolution_l = new SolutionALG(nbProcesses_l);
    
    pSolution_l->setpConstraintSystem(pConstraintSystem_m);
    pSolution_l->setpEvaluationSystem(pEvaluationSystem_m);
    
    for (DecisionsPool::const_iterator it_l=decisions_m.begin(); 
                                       it_l != decisions_m.end(); 
                                       ++it_l)
    {
        DecisionALG * pDec_l = *it_l;
        RestrictionALG * pRestriction_l = pDec_l->getRestriction(pSolution_l);
        pSolution_l->addRestriction(pRestriction_l);        
    }

    std::cerr << "On appelle la methode de monte carlo" << std::endl;
    MonteCarloSimulationALG monteCarlo_l;
    monteCarlo_l.run(pSolution_l);
    
    return pSolution_l;
}

SpaceALG * SpaceALG::clone()
{
    SpaceALG * pClone_l = new SpaceALG;
    pClone_l->decisions_m = decisions_m;
    pClone_l->pConstraintSystem_m = pConstraintSystem_m;
    pClone_l->pEvaluationSystem_m = pEvaluationSystem_m;
    
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

void SpaceALG::setpConstraintSystem(ConstraintSystemALG * pSystem_p)
{
    pConstraintSystem_m = pSystem_p;
}

void SpaceALG::setpEvaluationSystem(EvaluationSystemALG * pSystem_p)
{
    pEvaluationSystem_m = pSystem_p;
}

