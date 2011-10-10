#ifndef OPPMSPACEALG_HH
#define OPPMSPACEALG_HH

#include "src/alg/SpaceALG.hh"

class OPPMSpaceALG : public SpaceALG
{
    public:
        OPPMSpaceALG();
        ~OPPMSpaceALG();

        typedef SpaceALG::DecisionsPool DecisionsPool;
        virtual DecisionsPool generateDecisions() const;
        virtual SpaceALG * clone();
};

#endif
