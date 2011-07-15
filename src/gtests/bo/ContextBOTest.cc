#include "bo/ContextBO.hh"
#include "generateur/alg/DummyStrategyGeneration.hh"
#include <gtest/gtest.h>

TEST(ContextBO, cpyCtr){
    /* Mise en place de l'environnement de test.
     * Plutot que de creer un Context a la main, on tire profit des strategies de generation simples
     */
    DummyStrategyGeneration generateur_l;
    variables_map args_p;
    list<shared_ptr<ContextBO> > lpContexts_l = generateur_l.generate(args_p);
    ContextBO contextCopie_l(*(lpContexts_l.front()));

    //Les copies doivent etre egales
    EXPECT_EQ(contextCopie_l, *(lpContexts_l.front()));

    //mais elles ne doivent pas pointer sur les memes objets (sinon, risque de double delete, par leurs dtors)
    EXPECT_NE(contextCopie_l.getRessource(0), lpContexts_l.front()->getRessource(0));
    EXPECT_NE(contextCopie_l.getLocation(0), lpContexts_l.front()->getLocation(0));
    EXPECT_NE(contextCopie_l.getMachine(0), lpContexts_l.front()->getMachine(0));
    EXPECT_NE(contextCopie_l.getService(0), lpContexts_l.front()->getService(0));
    EXPECT_NE(contextCopie_l.getProcess(0), lpContexts_l.front()->getProcess(0));
    //TODO : ajouter ce test lorsque le contexte initiale contiendra au moins un balance cost
    //EXPECT_NE(contextCopie_l->getBalanceCost(0), context_l->getBalanceCost(0));
    EXPECT_NE(contextCopie_l.getMMCBO(), lpContexts_l.front()->getMMCBO());
}
