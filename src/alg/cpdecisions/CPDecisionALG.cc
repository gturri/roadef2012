#include "CPDecisionALG.hh"

CPDecisionALG::CPDecisionALG() : target_m(-1), min_m(-1), max_m(-1)
{
}

CPDecisionALG::CPDecisionALG(ProcessId target_p, MachineId min_p, MachineId max_p) :
    target_m(target_p), min_m(min_p), max_m(max_p)
{
}

RestrictionALG * CPDecisionALG::getRestriction(SolutionALG *) const
{
    return 0;
}

bool CPDecisionALG::workOnProcess(ProcessId proc_p) const
{
    return target_m == proc_p;
}
