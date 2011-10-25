#include "ConstraintSystemALG.hh"
#include "alg/ContextALG.hh"
#include "bo/ContextBO.hh"

ConstraintSystemALG::ConstraintSystemALG()
: pContext_m(0)
{
    
}

ConstraintSystemALG::~ConstraintSystemALG()
{
}

void ConstraintSystemALG::setpContext(ContextALG * pContext_p)
{
    pContext_m = pContext_p;
}

ContextALG * ConstraintSystemALG::getpContext() const
{
    return pContext_m;
}

ConstraintSystemALG::MachinePool ConstraintSystemALG::getLegalMachinePool(ProcessId process_l) const
{
    ConstraintSystemALG::MachinePool return_l;
    
    int nbMachines_l = pContext_m->getContextBO()->getNbMachines();
    
    for(int i_l = 0; i_l < nbMachines_l; ++i_l)
    {
        return_l.push_back(i_l);
    }
    
    return return_l;
}

void ConstraintSystemALG::unassign(ProcessId, MachineId)
{
    
}

void ConstraintSystemALG::assign(ProcessId,MachineId)
{
    
}


void ConstraintSystemALG::filter(ProcessPool & processPool_p) const
{
    
}

void ConstraintSystemALG::filter( ProcessId const & process_p, 
                                  MachinePool & machinePool_p) const
{
    
}
