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
    std::vector<int> solution();

    // constraints
    void capacity(const ContextBO*);
    void conflict(const ContextBO*);
    //void spread(const ContextBO*);
    void dependency(const ContextBO*);
    void transient(const ContextBO*);

    // Decision management
    void addDecision(const CPDecisionALG*);
    typedef std::vector<DecisionALG*> DecisionPool;
    DecisionPool generateDecisions();

protected:
    // machine[ProcessId] == the machine on which ProcessId is affectd
    Gecode::IntVarArray machine_m;
    // number of assignment equal to the initial solution
    Gecode::IntVar nbUnmovedProcs_m;
    // the boolean matrix proc x mach
    Gecode::BoolVarArray bMatrix_m;
};

#endif //GECODESPACE_HH_
