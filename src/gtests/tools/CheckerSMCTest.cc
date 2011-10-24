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

TEST(Checker, checkSMC){
    ContextBO contextBO_l;

    ContextBOBuilder::buildMachine(0, 0, 0, vector<int>(), vector<int>(), &contextBO_l);
    ContextBOBuilder::buildMachine(1, 0, 0, vector<int>(), vector<int>(), &contextBO_l);

    ServiceBO* pService0_l = ContextBOBuilder::buildService(0, 0, unordered_set<int>(), &contextBO_l);
    ServiceBO* pService1_l = ContextBOBuilder::buildService(1, 0, unordered_set<int>(), &contextBO_l);

    ContextBOBuilder::buildProcess(0, pService0_l, vector<int>(), 0, 0, &contextBO_l);
    ContextBOBuilder::buildProcess(1, pService0_l, vector<int>(), 0, 0, &contextBO_l);
    ContextBOBuilder::buildProcess(2, pService1_l, vector<int>(), 0, 1, &contextBO_l);
    ContextBOBuilder::buildProcess(3, pService1_l, vector<int>(), 0, 1, &contextBO_l);
    ContextBOBuilder::buildProcess(4, pService1_l, vector<int>(), 0, 1, &contextBO_l);
    ContextBOBuilder::buildDefaultMMC(&contextBO_l);

    ContextALG contextALG_l(&contextBO_l);
    vector<int> solCur_l;
    solCur_l.push_back(0);
    solCur_l.push_back(1);
    solCur_l.push_back(1);
    solCur_l.push_back(1);
    solCur_l.push_back(1);
    contextALG_l.setCurrentSol(solCur_l);
    Checker checker_l(&contextALG_l);
    EXPECT_EQ(checker_l.computeSMC(), (uint64_t) 1);
}
