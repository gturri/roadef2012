#include "dtoout/SolutionDtoout.hh"
#include <gtest/gtest.h>

TEST(SolutionDtoout, keepBestScore){
    SolutionDtoout::reinit("/dev/null");
    uint64_t score_l = 666;
    vector<int> sol_l(5);

    ASSERT_TRUE(SolutionDtoout::writeSol(sol_l, score_l));
    ASSERT_EQ(score_l, SolutionDtoout::getBestScore());
    ASSERT_EQ(sol_l, SolutionDtoout::getBestSol());
}

TEST(SolutionDtoout, writeOnlyIfBetterScore){
    SolutionDtoout::reinit("/dev/null");

    uint64_t score1_l = 1337;
    vector<int> sol1_l(1);
    uint64_t score2_l = 69;
    vector<int> sol2_l(2);
    uint64_t score3_l = 666;
    vector<int> sol3_l(3);

    ASSERT_TRUE(SolutionDtoout::writeSol(sol1_l, score1_l));
    ASSERT_TRUE(SolutionDtoout::writeSol(sol2_l, score2_l));
    ASSERT_FALSE(SolutionDtoout::writeSol(sol3_l, score3_l));

    ASSERT_EQ(score2_l, SolutionDtoout::getBestScore());
    ASSERT_EQ(sol2_l, SolutionDtoout::getBestSol());
}
