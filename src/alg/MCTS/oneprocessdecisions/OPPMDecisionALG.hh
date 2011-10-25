#ifndef OPPMDECISIONALG_HH
#define OPPMDECISIONALG_HH

#include "src/alg/MCTS/DecisionALG.hh"
#include <vector>

class OPPMDecisionALG : public DecisionALG
{
    public:
        typedef int ProcessId;
        typedef int MachineId;
        typedef std::vector<MachineId> MachinePool;
        
        OPPMDecisionALG();
        virtual ~OPPMDecisionALG();
        
        virtual void setTarget(ProcessId);
        virtual void setRestrictedSubset(MachinePool const &);
        
        virtual RestrictionALG * getRestriction(SolutionALG *) const;
        virtual bool workOnProcess(ProcessId) const;
        
    private:
        ProcessId target_m;
        MachinePool subset_m;
};

#endif
