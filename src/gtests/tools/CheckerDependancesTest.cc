#include "alg/ContextALG.hh"
#include "bo/ContextBO.hh"
#include "gtests/tools/CheckerFixture.hh"

TEST_F(CheckerFixture, CheckerDependances){
    ContextBO contextBO_l;

    buildMachine(0, 0, 0, vector<int>(), vector<int>(), &contextBO_l);
    buildMachine(1, 0, 0, vector<int>(), vector<int>(), &contextBO_l);
    buildMachine(2, 0, 1, vector<int>(), vector<int>(), &contextBO_l);
    buildMachine(3, 0, 1, vector<int>(), vector<int>(), &contextBO_l);

    unordered_set<int> dep_l;
    dep_l.insert(1);
    ServiceBO* pService0_l = buildService(0, 0, dep_l, &contextBO_l);
    ServiceBO* pService1_l = buildService(1, 0, unordered_set<int>(), &contextBO_l);
    buildProcess(0, pService0_l, vector<int>(), 0, 0, &contextBO_l);
    buildProcess(1, pService0_l, vector<int>(), 0, 2, &contextBO_l);
    buildProcess(2, pService1_l, vector<int>(), 0, 1, &contextBO_l);
    buildProcess(3, pService1_l, vector<int>(), 0, 2, &contextBO_l);

    ContextALG contextALG_l(&contextBO_l);
    setContextALG(&contextALG_l);
    EXPECT_TRUE(checkDependances());

    vector<int> curSol_l = contextALG_l.getCurrentSol();
    curSol_l[0]=0 ; curSol_l[1]=1 ; curSol_l[2]=2 ; curSol_l[3]=3;
    contextALG_l.setCurrentSol(curSol_l);
    EXPECT_FALSE(checkDependances());
}
