#include "bo/ContextBO.hh"
#include "generateur/alg/DummyStrategyGeneration.hh"
#include <gtest/gtest.h>

void testEgaliteContextsBO(const ContextBO& context1_l, const ContextBO& context2_l){
    //Les copies doivent etre egales
    EXPECT_EQ(context1_l, context2_l);

    //mais elles ne doivent pas pointer sur les memes objets (sinon, risque de double delete, par leurs dtors)
    EXPECT_NE(context1_l.getRessource(0), context2_l.getRessource(0));
    EXPECT_NE(context1_l.getLocation(0), context2_l.getLocation(0));
    EXPECT_NE(context1_l.getMachine(0), context2_l.getMachine(0));
    EXPECT_NE(context1_l.getService(0), context2_l.getService(0));
    EXPECT_NE(context1_l.getProcess(0), context2_l.getProcess(0));
    //TODO : ajouter ce test lorsque le contexte initial contiendra au moins un balance cost
    //EXPECT_NE(context1_l->getBalanceCost(0), context2_l->getBalanceCost(0));
    EXPECT_NE(context1_l.getMMCBO(), context2_l.getMMCBO());
}

TEST(ContextBO, cpyCtr){
    /* Mise en place de l'environnement de test.
     * Plutot que de creer un Context a la main, on tire profit des strategies de generation simples
     */
    DummyStrategyGeneration generateur_l;
    variables_map args_p;
    list<shared_ptr<ContextBO> > lpContexts_l = generateur_l.generate(args_p);
    ContextBO contextCopie_l(*(lpContexts_l.front()));

    testEgaliteContextsBO(contextCopie_l, *(lpContexts_l.front()));

    /* L'egalite des sols init n'est pas verifiee par == car il s'agit de donnees redondantes
     * On le teste tout de meme afin de voir qu'on n'a pas fait n'importe quoi avec la manipulation de pointeurs
     */
    EXPECT_EQ(contextCopie_l.getSolInit(), lpContexts_l.front()->getSolInit());
}

//FIXME : eventuellement utiliser une fixture pour factoriser le code de mise en place de l'environnement de test
TEST(ContextBO, operatorEgal){
    DummyStrategyGeneration generateur_l;
    variables_map args_p;
    list<shared_ptr<ContextBO> > lpContexts_l = generateur_l.generate(args_p);

    ContextBO contextCopie_l;
    contextCopie_l = *(lpContexts_l.front());
    testEgaliteContextsBO(contextCopie_l, *(lpContexts_l.front()));
}

TEST(ContextBO, getSolInit){
    DummyStrategyGeneration generateur_l;
    variables_map args_p;
    list<shared_ptr<ContextBO> > lpContexts_l = generateur_l.generate(args_p);

    vector<int> vSolExpected_l(1, 0);

    EXPECT_EQ(vSolExpected_l, lpContexts_l.front()->getSolInit());
}
