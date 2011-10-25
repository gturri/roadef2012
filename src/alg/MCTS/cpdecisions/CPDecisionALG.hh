#ifndef CPDECISIONALG_HH
#define CPDECISIONALG_HH

#include "src/alg/MCTS/DecisionALG.hh"

class CPDecisionALG : public DecisionALG
{
public:
    typedef int ProcessId;
    typedef int MachineId;
    
    CPDecisionALG();
    CPDecisionALG(ProcessId, MachineId, MachineId);

    virtual RestrictionALG * getRestriction(SolutionALG *) const;
    virtual bool workOnProcess(ProcessId) const;
    
    ProcessId target_m;
    MachineId min_m;
    MachineId max_m;
};

#endif
