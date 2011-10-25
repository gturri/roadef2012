#ifndef EVALUATIONSYSTEMALG_HH
#define EVALUATIONSYSTEMALG_HH

#include "SolutionALG.hh"

class ContextALG;

class EvaluationSystemALG
{
    public:
        typedef SolutionALG::ProcessId ProcessId;
        typedef SolutionALG::MachineId MachineId;
        typedef std::vector<MachineId> ExplicitRepresentation;
      
        EvaluationSystemALG();
        ~EvaluationSystemALG();
        
        double evaluate(ExplicitRepresentation const &);
        
        void setpContext(ContextALG *);
        ContextALG * getpContext() const;
        
    private:
        ContextALG * pContext_m;
};

#endif