#include "EvaluationSystemALG.hh"
#include "tools/Checker.hh"

EvaluationSystemALG::EvaluationSystemALG()
: pContext_m(0)
{
    
}

EvaluationSystemALG::~EvaluationSystemALG()
{
}

void EvaluationSystemALG::setpContext(ContextALG * pContext_p)
{
    pContext_m = pContext_p;
}

ContextALG * EvaluationSystemALG::getpContext() const
{
    return pContext_m;
}

double EvaluationSystemALG::evaluate(ExplicitRepresentation const & solution_p)
{
    return 0.0;
}
