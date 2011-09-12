#ifndef DECISIONALG_HH
#define DECISIONALG_HH

class RestrictionALG;
class SolutionALG;

class DecisionALG
{
    public:
        DecisionALG();
        ~DecisionALG();
        
        virtual RestrictionALG * getRestriction(SolutionALG *) const = 0;
        virtual bool workOnProcess() const = 0;
};

#endif
