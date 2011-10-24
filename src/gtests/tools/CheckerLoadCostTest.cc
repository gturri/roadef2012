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

TEST(Checker, checkLoadCost){
    ContextBO contextBO_l;
    contextBO_l.addRessource(new RessourceBO(0, true, 7));
    contextBO_l.addRessource(new RessourceBO(1, false, 11));

    vector<int> capasM0_l; capasM0_l.push_back(5); capasM0_l.push_back(5);
    vector<int> capasM1_l; capasM1_l.push_back(5); capasM1_l.push_back(5);
    vector<int> scM0_l; scM0_l.push_back(2);  scM0_l.push_back(4);
    vector<int> scM1_l; scM1_l.push_back(1); scM1_l.push_back(3);
    ContextBOBuilder::buildMachine(0, 0, 0, capasM0_l, scM0_l, &contextBO_l);
    ContextBOBuilder::buildMachine(1, 0, 0, capasM1_l, scM1_l, &contextBO_l);

    ServiceBO* pService_l = ContextBOBuilder::buildService(0, 0, unordered_set<int>(), &contextBO_l);
    vector<int> reqP0_l; reqP0_l.push_back(3); reqP0_l.push_back(1);
    ContextBOBuilder::buildProcess(0, pService_l, reqP0_l, 0, 0, &contextBO_l);
    ContextBOBuilder::buildDefaultMMC(&contextBO_l);

    ContextALG contextALG_l(&contextBO_l);
    contextALG_l.setCurrentSol(vector<int>(1, 1));
    Checker checker_l(&contextALG_l);
    EXPECT_EQ(checker_l.computeLoadCost(0), (uint64_t) 14);
    EXPECT_EQ(checker_l.computeLoadCost(1), (uint64_t) 0);
    EXPECT_EQ(checker_l.computeLoadCost(), (uint64_t) 14);
}
