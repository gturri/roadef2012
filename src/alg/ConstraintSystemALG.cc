#include "ConstraintSystemALG.hh"


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
