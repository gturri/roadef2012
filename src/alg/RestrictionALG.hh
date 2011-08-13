#ifndef RESTRICTIONALG_HH
#define RESTRICTIONALG_HH

#include "SolutionALG.hh"
#include <list>

class RestrictionALG
{
    public:
        RestrictionALG() {}
        ~RestrictionALG() {}
        
        typedef SolutionALG::ProcessId ProcessId;
        typedef std::list<ProcessId> ProcessPool;
        
        typedef SolutionALG::MachineId MachineId;
        typedef std::list<MachineId> MachinePool;
    
        virtual void filter(ProcessPool &) const = 0;
        virtual void filter(ProcessId const &, MachinePool &) const = 0;
};

#endif
