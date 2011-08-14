#ifndef CONSTRAINTSYSTEMALG_HH
#define CONSTRAINTSYSTEMALG_HH

#include "RestrictionALG.hh"

class ContextALG;

class ConstraintSystemALG : public RestrictionALG
{
    public:
        typedef RestrictionALG::ProcessId ProcessId;
        typedef RestrictionALG::ProcessPool ProcessPool;
        typedef RestrictionALG::MachineId MachineId;
        typedef RestrictionALG::MachinePool MachinePool;
        
        ConstraintSystemALG();
        ~ConstraintSystemALG();
        
        void unassign(ProcessId, MachineId);
        void assign(ProcessId, MachineId);
        
        void filter(ProcessPool &) const;
        void filter(ProcessId const &, MachinePool &) const;
    
        void setpContext(ContextALG *);
        ContextALG * getpContext() const;
        
    private:
        ContextALG * pContext_m;
};

#endif
