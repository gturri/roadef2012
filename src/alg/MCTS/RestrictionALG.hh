#ifndef RESTRICTIONALG_HH
#define RESTRICTIONALG_HH

#include "SolutionALG.hh"
#include <vector>

class RestrictionALG
{
    public:
        RestrictionALG() {}
        virtual ~RestrictionALG() {}
        
        typedef SolutionALG::ProcessId ProcessId;
        typedef std::vector<ProcessId> ProcessPool;
        
        typedef SolutionALG::MachineId MachineId;
        typedef std::vector<MachineId> MachinePool;
    
        virtual void filter(ProcessPool &) const = 0;
        virtual void filter(ProcessId const &, MachinePool &) const = 0;
};

#endif
