#ifndef SOLUTIONALG_HH
#define SOLUTIONALG_HH

#include <vector>

class ConstraintSystemALG;
class EvaluationSystemALG;
class RestrictionALG;

class SolutionALG
{
    public:
        SolutionALG();
        ~SolutionALG();

        typedef int ProcessId;
        typedef int MachineId;

        static const MachineId unassigned = -1;
                
        void addRestriction(RestrictionALG *); 
        void setpConstraintSystem(ConstraintSystemALG *); 
        void setpEvaluationSystem(EvaluationSystemALG *); 

        std::vector<ProcessId> getAvaiableProcesses() const;
        std::vector<MachineId> getAvaiableMachines(ProcessId) const;

        void unassign(ProcessId);
        void assign(ProcessId, MachineId);

        double evaluate();
        
    private:
        typedef std::vector<RestrictionALG *> RestrictionPool;
        RestrictionPool restrictions_m;     
        
        typedef std::vector<MachineId> ExplicitRepresentation;
        ExplicitRepresentation assignment_m;

        ConstraintSystemALG * pConstraintSystem_m;
        EvaluationSystemALG * pEvaluationSystem_m;
        double incrementalValue_m;
};

#endif
