#include "OPPMDecisionALG.hh"
#include "OPPMRestrictionALG.hh"

OPPMDecisionALG::OPPMDecisionALG()
{
}

OPPMDecisionALG::~OPPMDecisionALG()
{
}

void OPPMDecisionALG::setTarget(ProcessId target_p)
{
    target_m = target_p;
}

void OPPMDecisionALG::setRestrictedSubset(MachinePool const & subset_p)
{
    subset_m = subset_p;
}

bool OPPMDecisionALG::workOnProcess(ProcessId process_p) const
{
    return (process_p != target_m);
}

RestrictionALG * OPPMDecisionALG::getRestriction(SolutionALG * pSolution_p) const
{
    return new OPPMRestrictionALG(target_m,subset_m);  
}
