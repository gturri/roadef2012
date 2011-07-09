#include "bo/ContextBO.hh"
#include "gtests/dtoin/TestDtoinHelper.hh"
#include <gtest/gtest.h>

TEST(dtoin, PoidsDtoin){
    ContextBO context_l;
    TestDtoinHelper::loadTestDataPoids(&context_l);

    EXPECT_EQ(context_l.getPoidsPMC(), 1);
    EXPECT_EQ(context_l.getPoidsSMC(), 10);
    EXPECT_EQ(context_l.getPoidsMMC(), 100);
}
