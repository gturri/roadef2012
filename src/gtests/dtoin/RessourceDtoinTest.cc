#include "bo/ContextBO.hh"
#include "bo/RessourceBO.hh"
#include "gtests/dtoin/TestDtoinHelper.hh"
#include <gtest/gtest.h>

TEST(dtoin, RessourceDtoin){
    ContextBO context_l;
    TestDtoinHelper::loadTestDataRessource(&context_l);

    ASSERT_EQ(context_l.getNbRessources(), 2);

    RessourceBO* ress1_l = context_l.getRessource(0);
    EXPECT_EQ(ress1_l->getId(), 0);
    EXPECT_TRUE(ress1_l->isTransient());
    EXPECT_EQ(ress1_l->getWeightLoadCost(), 100);

    RessourceBO* ress2_l = context_l.getRessource(1);
    EXPECT_EQ(ress2_l->getId(), 1);
    EXPECT_FALSE(ress2_l->isTransient());
    EXPECT_EQ(ress2_l->getWeightLoadCost(), 10);
}
