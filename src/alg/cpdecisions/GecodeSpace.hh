#ifndef GECODESPACE_HH_
#define GECODESPACE_HH_

#include "bo/ContextBO.hh"
#include <gecode/int.hh>
#include <vector>

class GecodeSpace: public Gecode::Space
{
public:
    GecodeSpace(const ContextBO*);
    GecodeSpace(bool, GecodeSpace&);

    virtual Gecode::Space *copy(bool);
    std::vector<int> solution() const;

protected:
    // machine[ProcessId] == the machine on which ProcessId is affectd
    Gecode::IntVarArray machine_m;
};

#endif //GECODESPACE_HH_
