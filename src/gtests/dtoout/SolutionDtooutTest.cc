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

TEST(SolutionDtoout, throwIfWrongFile){
    SolutionDtoout::reinit("/W/T/F.txt");
    ASSERT_ANY_THROW(SolutionDtoout::writeSol(vector<int>(), 42));
}

TEST(SolutionDtoout, unlockIfWrongFile){
    //FIXME : Le risque, si le teste plante, c'est qu'au lieu d'un echec, on reste bloque dans une etreinte fatale...
    //Fix eventuel : lancer le writeSol dans un thread, l'attendre 1s, puis s'il n'a pas abouti, le killer et signaler un echec
    //(mais, on risque un faux positif sur une machine surchargee... (ou attendre 10s ? Mais ca devient long pour un test U, en cas d'echec...)
    SolutionDtoout::reinit("/W/T/F.txt");
    ASSERT_ANY_THROW(SolutionDtoout::writeSol(vector<int>(), 42));
    ASSERT_ANY_THROW(SolutionDtoout::writeSol(vector<int>(), 13));

}
