#ifndef DUMMYSTRATEGYGENERATION_HH
#define DUMMYSTRATEGYGENERATION_HH
#include "generateur/alg/StrategyGeneration.hh"

/**
 * Genere une instance ultra minimaliste, dans le seul but de voir si le generateur tourne
 */

class DummyStrategyGeneration : public StrategyGeneration {
    public:
        virtual list<shared_ptr<ContextBO> > generate(const variables_map& arg_p);

        void buildRessources(shared_ptr<ContextBO> pContextBO_p);
        void buildMachines(shared_ptr<ContextBO> pContextBO_p);
        void buildMMC(shared_ptr<ContextBO> pContextBO_p);
        void buildServices(shared_ptr<ContextBO> pContextBO_p);
        void buildProcesses(shared_ptr<ContextBO> pContextBO_p);
        void buildBalanceCosts(shared_ptr<ContextBO> pContextBO_p);
        void buildPoids(shared_ptr<ContextBO> pContextBO_p);
};

#endif
