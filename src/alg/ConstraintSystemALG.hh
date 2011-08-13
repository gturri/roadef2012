#ifndef CONSTRAINTSYSTEMALG_HH
#define CONSTRAINTSYSTEMALG_HH

#include "RestrictionALG.hh"

class ConstraintSystemALG : public RestrictionALG
{
    public:
        typedef RestrictionALG::ProcessId ProcessId;
        typedef RestrictionALG::ProcessPool ProcessPool;
        typedef RestrictionALG::MachinePool MachinePool;
        
        ConstraintSystemALG();
        ~ConstraintSystemALG();
        
        void filter(ProcessPool &) const;
        void filter(ProcessId const &, MachinePool &) const;
    
};

#endif
