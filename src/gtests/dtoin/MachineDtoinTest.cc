#include "bo/ContextBO.hh"
#include "bo/LocationBO.hh"
#include "bo/MachineBO.hh"
#include "bo/MMCBO.hh"
#include "bo/NeighborhoodBO.hh"
#include "gtests/dtoin/TestDtoinHelper.hh"
#include <gtest/gtest.h>

TEST(dtoin, MachineDtoin){
    ContextBO context_l;
    TestDtoinHelper::loadTestDataRessource(&context_l);
    TestDtoinHelper::loadTestDataMachine(&context_l);

    ASSERT_EQ(context_l.getNbMachines(), 4);
    ASSERT_EQ(context_l.getNbLocations(), 3);
    ASSERT_EQ(context_l.getNbNeighborhoods(), 2);

    //Machine 0
    EXPECT_EQ(context_l.getMachine(0)->getId(), 0);
    EXPECT_EQ(context_l.getMachine(0)->getNeighborhood()->getId(), 0);
    EXPECT_EQ(context_l.getMachine(0)->getLocation()->getId(), 0);
    EXPECT_EQ(context_l.getMachine(0)->getCapa(0), 30);
    EXPECT_EQ(context_l.getMachine(0)->getCapa(1), 400);
    EXPECT_EQ(context_l.getMachine(0)->getSafetyCapa(0), 16);
    EXPECT_EQ(context_l.getMachine(0)->getSafetyCapa(1), 80);
    
    //Machine 1
    EXPECT_EQ(context_l.getMachine(1)->getId(), 1);
    EXPECT_EQ(context_l.getMachine(1)->getNeighborhood()->getId(), 0);
    EXPECT_EQ(context_l.getMachine(1)->getLocation()->getId(), 0);
    EXPECT_EQ(context_l.getMachine(1)->getCapa(0), 10);
    EXPECT_EQ(context_l.getMachine(1)->getCapa(1), 240);
    EXPECT_EQ(context_l.getMachine(1)->getSafetyCapa(0), 8);
    EXPECT_EQ(context_l.getMachine(1)->getSafetyCapa(1), 160);

    //Machine 2
    EXPECT_EQ(context_l.getMachine(2)->getId(), 2);
    EXPECT_EQ(context_l.getMachine(2)->getNeighborhood()->getId(), 1);
    EXPECT_EQ(context_l.getMachine(2)->getLocation()->getId(), 1);
    EXPECT_EQ(context_l.getMachine(2)->getCapa(0), 15);
    EXPECT_EQ(context_l.getMachine(2)->getCapa(1), 100);
    EXPECT_EQ(context_l.getMachine(2)->getSafetyCapa(0), 12);
    EXPECT_EQ(context_l.getMachine(2)->getSafetyCapa(1), 80);

    //Machine 3
    EXPECT_EQ(context_l.getMachine(3)->getId(), 3);
    EXPECT_EQ(context_l.getMachine(3)->getNeighborhood()->getId(), 1);
    EXPECT_EQ(context_l.getMachine(3)->getLocation()->getId(), 2);
    EXPECT_EQ(context_l.getMachine(3)->getCapa(0), 10);
    EXPECT_EQ(context_l.getMachine(3)->getCapa(1), 100);
    EXPECT_EQ(context_l.getMachine(3)->getSafetyCapa(0), 8);
    EXPECT_EQ(context_l.getMachine(3)->getSafetyCapa(1), 80);

    //MMC
    MMCBO* pMMC_l = context_l.getMMCBO();
    EXPECT_EQ(pMMC_l->getCost(0, 0), 0);
    EXPECT_EQ(pMMC_l->getCost(0, 1), 1);
    EXPECT_EQ(pMMC_l->getCost(0, 2), 4);
    EXPECT_EQ(pMMC_l->getCost(0, 3), 5);
    EXPECT_EQ(pMMC_l->getCost(1, 0), 1);
    EXPECT_EQ(pMMC_l->getCost(1, 1), 0);
    EXPECT_EQ(pMMC_l->getCost(1, 2), 3);
    EXPECT_EQ(pMMC_l->getCost(1, 3), 4);
    EXPECT_EQ(pMMC_l->getCost(2, 0), 4);
    EXPECT_EQ(pMMC_l->getCost(2, 1), 3);
    EXPECT_EQ(pMMC_l->getCost(2, 2), 0);
    EXPECT_EQ(pMMC_l->getCost(2, 3), 2);
    EXPECT_EQ(pMMC_l->getCost(3, 0), 5);
    EXPECT_EQ(pMMC_l->getCost(3, 1), 4);
    EXPECT_EQ(pMMC_l->getCost(3, 2), 2);
    EXPECT_EQ(pMMC_l->getCost(3, 3), 0);
}
