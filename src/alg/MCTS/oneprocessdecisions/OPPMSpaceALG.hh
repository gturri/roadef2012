#ifndef OPPMSPACEALG_HH
#define OPPMSPACEALG_HH

#include "src/alg/MCTS/SpaceALG.hh"

class OPPMSpaceALG : public SpaceALG
{
public:
    OPPMSpaceALG();
    virtual ~OPPMSpaceALG();

    typedef SpaceALG::DecisionsPool DecisionsPool;
    virtual DecisionsPool generateDecisions() const;
    virtual SpaceALG * clone();
    virtual bool isSolution() const;
};

#endif
