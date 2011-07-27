#ifndef SOLUTIONALG_HH
#define SOLUTIONALG_HH

#include <vector>

class SolutionALG
{
    public:
        SolutionALG();
        ~SolutionALG();

        typedef int MachineId;
        typedef int ProcessId;

        void unassign(ProcessId);
        void assign(ProcessId, MachineId);

        double evaluate();

    private:
        typedef std::vector<int> ExplicitRepresentation;
        ExplicitRepresentation assignment_m;

        double incrementalValue_m;
};

#endif
