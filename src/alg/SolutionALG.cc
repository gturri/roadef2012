#include "SolutionALG.hh"

SolutionALG::SolutionALG()
:assignment_m(),incrementalValue_m(0.0)
{
}

SolutionALG::~SolutionALG()
{
}

void SolutionALG::unassign(ProcessId)
{
}

void SolutionALG::assign(ProcessId, MachineId)
{
}

double SolutionALG::evaluate()
{
    return incrementalValue_m;
}

