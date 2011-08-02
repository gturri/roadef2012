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

TEST(Checker, checkPMC){
    Checker checker_l;
    ContextBO contextBO_l;

    ContextBOBuilder::buildMachine(0, 0, 0, vector<int>(), vector<int>(), &contextBO_l);
    ContextBOBuilder::buildMachine(1, 0, 0, vector<int>(), vector<int>(), &contextBO_l);

    ServiceBO* pService_l = ContextBOBuilder::buildService(0, 0, unordered_set<int>(), &contextBO_l);
    ContextBOBuilder::buildProcess(0, pService_l, vector<int>(), 3, 0, &contextBO_l);
    ContextBOBuilder::buildProcess(1, pService_l, vector<int>(), 5, 0, &contextBO_l);
    ContextBOBuilder::buildProcess(2, pService_l, vector<int>(), 7, 0, &contextBO_l);

    ContextALG contextALG_l(&contextBO_l);
    vector<int> solCur_l; solCur_l.push_back(1); solCur_l.push_back(1); solCur_l.push_back(0);
    contextALG_l.setCurrentSol(solCur_l);
    checker_l.setContextALG(&contextALG_l);
    EXPECT_EQ(checker_l.computePMC(), 8);
}
