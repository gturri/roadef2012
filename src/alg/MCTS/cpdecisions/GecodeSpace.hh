#ifndef GECODESPACE_HH_
#define GECODESPACE_HH_

#include "CPDecisionALG.hh"
#include "bo/ContextBO.hh"
#include <gecode/int.hh>
#include <vector>

class GecodeSpace: public Gecode::Space
{
public:
    GecodeSpace(const ContextBO*);
    GecodeSpace(bool, GecodeSpace&);
    virtual Gecode::Space *copy(bool);

    void addDecision(const CPDecisionALG*);
    typedef std::vector<DecisionALG*> DecisionPool;
    DecisionPool generateDecisions();
    std::vector<int> solution();

protected:
    // machine[ProcessId] == the machine on which ProcessId is affectd
    Gecode::IntVarArray machine_m;
    Gecode::IntVar nbUnmovedProcs_m;
};

#endif //GECODESPACE_HH_
