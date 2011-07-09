#include "dtoin/ServiceDtoin.hh"
#include "bo/ContextBO.hh"
#include "bo/ServiceBO.hh"
#include "gtests/dtoin/TestDtoinHelper.hh"
#include <sstream>
#include <gtest/gtest.h>
using namespace std;

TEST(dtoin, ServiceDtoin){
    ServiceDtoin reader_l;
    istringstream ifs_l(TestDtoinHelper::getServiceData());
    ContextBO context_l;
    reader_l.read(ifs_l, &context_l);

    ASSERT_EQ(context_l.getNbServices(), 2);

    EXPECT_EQ(context_l.getService(0)->getId(), 0);
    EXPECT_EQ(context_l.getService(0)->getSpreadMin(), 2);
    EXPECT_EQ(context_l.getService(0)->getNbServicesIDependOn(), 0);
    EXPECT_FALSE(context_l.getService(0)->iDependOn(0));
    EXPECT_FALSE(context_l.getService(0)->iDependOn(1));

    EXPECT_EQ(context_l.getService(1)->getId(), 1);
    EXPECT_EQ(context_l.getService(1)->getSpreadMin(), 1);
    EXPECT_EQ(context_l.getService(1)->getNbServicesIDependOn(), 1);
    EXPECT_TRUE(context_l.getService(1)->iDependOn(0));
    EXPECT_FALSE(context_l.getService(1)->iDependOn(1));



}
