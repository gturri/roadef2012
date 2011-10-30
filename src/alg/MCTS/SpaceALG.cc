#include "SpaceALG.hh"

#include "alg/ContextALG.hh"
#include "dtoout/SolutionDtoout.hh"
#include "SolutionALG.hh"
#include "DecisionALG.hh"
#include "RestrictionALG.hh"
#include "MonteCarloSimulationALG.hh"

#include <iostream>
#include "bo/ContextBO.hh"
#include "tools/Log.hh"
#include "tools/Checker.hh"

SpaceALG::SpaceALG() :
    origEval_m(1), pContext_m(0), pEvaluationSystem_m(0), pConstraintSystem_m(0)
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
    LOG(WTF) << "Mauvaise surcharge" << std::endl;
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

double SpaceALG::evaluate() const
{
    ContextBO const * pContext_l = getpContext()->getContextBO();
    int nbProcesses_l = pContext_l->getNbProcesses();
    
    LOG(USELESS) << "On construit une solution" << std::endl;
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

    LOG(USELESS) << "On appelle la methode de monte carlo avec " 
                 << decisions_m.size() << " restrictions" << std::endl;
    MonteCarloSimulationALG monteCarlo_l;
    monteCarlo_l.run(pSolution_l);

    double eval_l = 0;
    const std::vector<int> &sol_l = pSolution_l->getSolution();
    Checker checker_l(pContext_m->getContextBO(), pSolution_l->getSolution());
    if (checker_l.isValid()){
        uint64_t intEval_l = checker_l.computeScore();
        eval_l = (double) origEval_m / (origEval_m + intEval_l);
        if (SolutionDtoout::writeSol(sol_l, intEval_l)) {
            LOG(INFO) << "Better solution: " << intEval_l
                      << ", eval = " << eval_l << endl;
        }
    }

    delete pSolution_l;

    return eval_l;
}

SpaceALG * SpaceALG::clone()
{
    return new SpaceALG(*this);
}
    
void SpaceALG::setpContext(ContextALG * pContext_p)
{
    pContext_m = pContext_p;
    origEval_m = pContext_p->getScoreBestSol();
    LOG(INFO) << "firstEval = " << origEval_m << std::endl;
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

