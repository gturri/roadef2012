#include "alg/ContextALG.hh"
#include "bo/ContextBO.hh"
#include "bo/MMCBO.hh"
#include "bo/RessourceBO.hh"
#include "bo/ServiceBO.hh"
#include "gtests/ContextBOBuilder.hh"
#include "tools/Checker.hh"
#include <vector>
#include <tr1/unordered_set>
#include <gtest/gtest.h>
using namespace std;
using namespace std::tr1;

TEST(Checker, checkMMC){
    ContextBO contextBO_l;

    ContextBOBuilder::buildMachine(0, 0, 0, vector<int>(), vector<int>(), &contextBO_l);
    ContextBOBuilder::buildMachine(1, 0, 0, vector<int>(), vector<int>(), &contextBO_l);

    ServiceBO* pService_l = ContextBOBuilder::buildService(0, 0, unordered_set<int>(), &contextBO_l);
    ContextBOBuilder::buildProcess(0, pService_l, vector<int>(), 0, 0, &contextBO_l);
    ContextBOBuilder::buildProcess(1, pService_l, vector<int>(), 0, 0, &contextBO_l);
    ContextBOBuilder::buildProcess(2, pService_l, vector<int>(), 0, 1, &contextBO_l);
    ContextBOBuilder::buildProcess(3, pService_l, vector<int>(), 0, 1, &contextBO_l);

    vector<vector<int> > mmcbo_l(2, vector<int>(2, 0));
    mmcbo_l[0][0]=0; mmcbo_l[0][1]=10;
    mmcbo_l[1][0]=7; mmcbo_l[1][1]=0;
    contextBO_l.setMMCBO(new MMCBO(mmcbo_l));

    ContextALG contextALG_l(&contextBO_l);
    vector<int> solCur_l(4, 0);
    solCur_l[0]=1;
    solCur_l[1]=0;
    solCur_l[2]=0;
    solCur_l[3]=0;
    contextALG_l.setCurrentSol(solCur_l);
    Checker checker_l(&contextALG_l);
    EXPECT_EQ(checker_l.computeMMC(), (uint64_t) 24);
}
