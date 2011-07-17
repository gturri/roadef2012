#ifndef GENERATEFROMEXISTING_HH
#define GENERATEFROMEXISTING_HH
#include "generateur/alg/StrategyGeneration.hh"

class InstanceReaderInterface;

/**
 * Construit des scenarios a partir d'un existant
 * (pour l'instant on se contente de ressortir tel quel celui qu'on lit:
 * ca permet d'avoir un convertisseur entre les differents formats d'instance)
 */
class GenerateFromExisting : public StrategyGeneration {
    public:
        virtual list<shared_ptr<ContextBO> > generate(const variables_map& arg_p);

    private:
        shared_ptr<InstanceReaderInterface> getReader(const variables_map& arg_p);
};

#endif
