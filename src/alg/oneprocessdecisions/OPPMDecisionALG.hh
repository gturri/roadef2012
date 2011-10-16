#ifndef OPPMDECISIONALG_HH
#define OPPMDECISIONALG_HH

#include "src/alg/DecisionALG.hh"
#include <vector>

class OPPMDecisionALG : public DecisionALG
{
    public:
        typedef int ProcessId;
        typedef int MachineId;
        typedef std::vector<MachineId> MachinePool;
        
        OPPMDecisionALG();
        ~OPPMDecisionALG();
        
        void setTarget(ProcessId);
        void setRestrictedSubset(MachinePool const &);
        
        RestrictionALG * getRestriction(SolutionALG *) const;
        bool workOnProcess(ProcessId) const;
        
    private:
        ProcessId target_m;
        MachinePool subset_m;
        
};

#endif
