#include "tools/random/RandomGenerateur.hh"
#include <gtest/gtest.h>

TEST(RandomGenerateur, generateurUniformeDouble){
    double borneMin_l(3), borneSup_l(7);
    RandomGenerateur* randomGen_l = RandomGenerateur::getInstance();
    double realisation_l = randomGen_l->generateUniformeDouble(borneMin_l, borneSup_l);
    EXPECT_GE(realisation_l, borneMin_l);
    EXPECT_LT(realisation_l, borneSup_l);
}

