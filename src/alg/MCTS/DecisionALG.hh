#ifndef DECISIONALG_HH
#define DECISIONALG_HH

class RestrictionALG;
class SolutionALG;

class DecisionALG
{
    public:
        typedef int ProcessId;

        DecisionALG();
        virtual ~DecisionALG();
        
        virtual RestrictionALG * getRestriction(SolutionALG *) const = 0;
        virtual bool workOnProcess(ProcessId) const = 0;
};

#endif
