#include "bo/BalanceCostBO.hh"
#include "bo/ContextBO.hh"
#include "gtests/dtoin/TestDtoinHelper.hh"
#include <gtest/gtest.h>

TEST(dtoin, BalanceCostDtoin){
    ContextBO context_l;
    TestDtoinHelper::loadTestDataRessource(&context_l);
    TestDtoinHelper::loadTestDataBalanceCost(&context_l);

    ASSERT_EQ(context_l.getNbBalanceCosts(), 1);
    EXPECT_EQ(context_l.getBalanceCost(0)->getRessource1(), context_l.getRessource(0));
    EXPECT_EQ(context_l.getBalanceCost(0)->getRessource2(), context_l.getRessource(1));
    EXPECT_EQ(context_l.getBalanceCost(0)->getTarget(), 20);
    EXPECT_EQ(context_l.getBalanceCost(0)->getPoids(), 10);
}
