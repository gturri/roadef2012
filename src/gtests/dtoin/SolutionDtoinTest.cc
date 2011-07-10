#include "bo/ContextBO.hh"
#include "bo/ProcessBO.hh"
#include "gtests/dtoin/TestDtoinHelper.hh"
#include <gtest/gtest.h>

TEST(dtoin, SolutionDtoin){
    ContextBO context_l;
    TestDtoinHelper::loadTestDataRessource(&context_l);
    TestDtoinHelper::loadTestDataMachine(&context_l);
    TestDtoinHelper::loadTestDataService(&context_l);
    TestDtoinHelper::loadTestDataProcess(&context_l);
    TestDtoinHelper::loadTestDataSolInit(&context_l);

    EXPECT_EQ(context_l.getProcess(0)->getMachineInit(), context_l.getMachine(0));
    EXPECT_EQ(context_l.getProcess(1)->getMachineInit(), context_l.getMachine(3));
    EXPECT_EQ(context_l.getProcess(2)->getMachineInit(), context_l.getMachine(0));
}
