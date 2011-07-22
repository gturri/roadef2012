#include "alg/ContextALG.hh"
#include "bo/ContextBO.hh"
#include "bo/RessourceBO.hh"
#include "bo/ServiceBO.hh"
#include "gtests/ContextBOBuilder.hh"
#include "tools/Checker.hh"
#include <vector>
#include <tr1/unordered_set>
#include <gtest/gtest.h>
using namespace std;
using namespace std::tr1;

TEST(Checker, checkBalanceCost){
    ContextBO contextBO_l;
    contextBO_l.addRessource(new RessourceBO(0, false, 0));
    contextBO_l.addRessource(new RessourceBO(1, false, 0));

    vector<int> capasM0_l; capasM0_l.push_back(7); capasM0_l.push_back(9);
    vector<int> capasM1_l; capasM1_l.push_back(3); capasM1_l.push_back(6);
    ContextBOBuilder::buildMachine(0, 0, 0, capasM0_l, vector<int>(2, 0), &contextBO_l);
    ContextBOBuilder::buildMachine(1, 0, 0, capasM1_l, vector<int>(2, 0), &contextBO_l);

    ServiceBO* pService_l = ContextBOBuilder::buildService(0, 0, unordered_set<int>(), &contextBO_l);
    vector<int> reqP0_l; reqP0_l.push_back(4); reqP0_l.push_back(5);
    vector<int> reqP1_l; reqP1_l.push_back(1); reqP1_l.push_back(1);
    ContextBOBuilder::buildProcess(0, pService_l, reqP0_l, 0, 0, &contextBO_l);
    ContextBOBuilder::buildProcess(1, pService_l, reqP1_l, 0, 1, &contextBO_l);
    ContextBOBuilder::buildDefaultMMC(&contextBO_l);

    ContextBOBuilder::buildBalanceCost(0, 1, 2, 7, &contextBO_l);

    ContextALG contextALG_l(&contextBO_l);
    Checker checker_l(&contextALG_l);
    EXPECT_EQ(checker_l.computeBalanceCost(0), 14);
    EXPECT_EQ(checker_l.computeBalanceCost(1), 0);
    EXPECT_EQ(checker_l.computeBalanceCost(), 14);
}
