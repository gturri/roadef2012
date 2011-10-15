#include "EvaluationSystemALG.hh"
#include "ContextALG.hh"
#include "bo/ContextBO.hh"
#include "tools/Checker.hh"

#include "tools/Log.hh"

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
    double value_l = 0.0;
    size_t size_l = solution_p.size();
    int nbMachines = pContext_m->getContextBO()->getNbMachines();
    for(size_t i_l = 0; i_l < size_l; ++i_l)
    {
        value_l += solution_p[i_l];
    }
    value_l /= size_l;
    value_l /= nbMachines;
    
    LOG(USELESS) << "On evalue la solution a " << value_l 
                 << " avec " << size_l 
                 << " process et " << nbMachines << " machines" << std::endl;
    if( value_l >= 0)
    {
        return value_l;
    }
    else
    {
        return 0.0;
    }
}
