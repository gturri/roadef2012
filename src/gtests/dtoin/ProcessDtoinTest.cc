#include "gtests/dtoin/TestDtoinHelper.hh"
#include "bo/ContextBO.hh"
#include "bo/ProcessBO.hh"
#include "bo/ServiceBO.hh"
#include <gtest/gtest.h>

TEST(dtoin, ProcessDtoin){
    ContextBO context_l;
    TestDtoinHelper::loadTestDataRessource(&context_l);
    TestDtoinHelper::loadTestDataService(&context_l);
    TestDtoinHelper::loadTestDataProcess(&context_l);

    ASSERT_EQ(context_l.getNbProcesses(), 3);
    EXPECT_EQ(context_l.getProcess(0)->getId(), 0);
    EXPECT_EQ(context_l.getProcess(0)->getService(), context_l.getService(0));
    EXPECT_EQ(context_l.getProcess(0)->getRequirement(0), 12);
    EXPECT_EQ(context_l.getProcess(0)->getRequirement(1), 10);
    EXPECT_EQ(context_l.getProcess(0)->getPMC(), 1000);

    EXPECT_EQ(context_l.getProcess(1)->getId(), 1);
    EXPECT_EQ(context_l.getProcess(1)->getService(), context_l.getService(0));
    EXPECT_EQ(context_l.getProcess(1)->getRequirement(0), 10);
    EXPECT_EQ(context_l.getProcess(1)->getRequirement(1), 20);
    EXPECT_EQ(context_l.getProcess(1)->getPMC(), 100);

    EXPECT_EQ(context_l.getProcess(2)->getId(), 2);
    EXPECT_EQ(context_l.getProcess(2)->getService(), context_l.getService(1));
    EXPECT_EQ(context_l.getProcess(2)->getRequirement(0), 6);
    EXPECT_EQ(context_l.getProcess(2)->getRequirement(1), 200);
    EXPECT_EQ(context_l.getProcess(2)->getPMC(), 1);

    ASSERT_EQ(context_l.getService(0)->getNbProcesses(), 2);
    EXPECT_TRUE(context_l.getService(0)->containsProcess(0));
    EXPECT_TRUE(context_l.getService(0)->containsProcess(1));
    EXPECT_FALSE(context_l.getService(0)->containsProcess(2));

    ASSERT_EQ(context_l.getService(1)->getNbProcesses(), 1);
    EXPECT_FALSE(context_l.getService(1)->containsProcess(0));
    EXPECT_FALSE(context_l.getService(1)->containsProcess(1));
    EXPECT_TRUE(context_l.getService(1)->containsProcess(2));
}
