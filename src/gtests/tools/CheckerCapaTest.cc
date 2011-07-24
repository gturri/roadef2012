#include "alg/ContextALG.hh"
#include "bo/ContextBO.hh"
#include "bo/LocationBO.hh"
#include "bo/MachineBO.hh"
#include "bo/NeighborhoodBO.hh"
#include "bo/ProcessBO.hh"
#include "bo/RessourceBO.hh"
#include "bo/ServiceBO.hh"
#include "gtests/tools/CheckerFixture.hh"
#include <vector>
#include <tr1/unordered_set>
#include <gtest/gtest.h>
using namespace std;
using namespace std::tr1;

TEST_F(CheckerFixture, checkCapaNotTransient){
    ContextBO contextBO_l;
    contextBO_l.addRessource(new RessourceBO(0, false, 0));

    buildMachine(0, 0, 0, vector<int>(1, 15), vector<int>(1, 10), &contextBO_l);
    buildMachine(1, 0, 0, vector<int>(1, 20), vector<int>(1, 10), &contextBO_l);

    ServiceBO* pService_l = buildService(0, 0, unordered_set<int>(), &contextBO_l);
    buildProcess(0, pService_l, vector<int>(1, 14), 0, 0, &contextBO_l);
    buildProcess(1, pService_l, vector<int>(1, 4), 0, 1, &contextBO_l);

    ContextALG contextALG_l(&contextBO_l);
    setContextALG(&contextALG_l);
    EXPECT_TRUE(checkCapaIncludingTransient());

    contextALG_l.setCurrentSol(vector<int>(2, 0));
    EXPECT_FALSE(checkCapaIncludingTransient());

    contextALG_l.setCurrentSol(vector<int>(2, 1));
    EXPECT_TRUE(checkCapaIncludingTransient());

    vector<int> curSol_l(2, 0);
    curSol_l[0] = 1;
    contextALG_l.setCurrentSol(curSol_l);
    EXPECT_TRUE(checkCapaIncludingTransient());
}

TEST_F(CheckerFixture, checkCapaTransient){
    ContextBO contextBO_l;
    contextBO_l.addRessource(new RessourceBO(0, true, 0));

    buildMachine(0, 0, 0, vector<int>(1, 15), vector<int>(1, 10), &contextBO_l);
    buildMachine(1, 0, 0, vector<int>(1, 20), vector<int>(1, 10), &contextBO_l);

    ServiceBO* pService_l = new ServiceBO(0, 0, unordered_set<int>());
    contextBO_l.addService(pService_l);
    buildProcess(0, pService_l, vector<int>(1, 14), 0, 0, &contextBO_l);
    buildProcess(1, pService_l, vector<int>(1, 4), 0, 1, &contextBO_l);

    ContextALG contextALG_l(&contextBO_l);
    setContextALG(&contextALG_l);
    EXPECT_TRUE(checkCapaIncludingTransient());

    contextALG_l.setCurrentSol(vector<int>(2, 0));
    EXPECT_FALSE(checkCapaIncludingTransient());

    contextALG_l.setCurrentSol(vector<int>(2, 1));
    EXPECT_TRUE(checkCapaIncludingTransient());

    vector<int> curSol_l(2, 0);
    curSol_l[0] = 1;
    contextALG_l.setCurrentSol(curSol_l);
    EXPECT_FALSE(checkCapaIncludingTransient());
}
