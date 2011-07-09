#include "dtoin/RessourceDtoin.hh"
#include "bo/ContextBO.hh"
#include "bo/RessourceBO.hh"
#include "gtests/dtoin/TestDtoinHelper.hh"
#include <sstream>
#include <gtest/gtest.h>
using namespace std;

TEST(dtoin, RessourceDtoin){
    RessourceDtoin reader_l;
    istringstream ifs_l(TestDtoinHelper::getRessourceData());
    ContextBO context_l;

    reader_l.read(ifs_l, &context_l);
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
