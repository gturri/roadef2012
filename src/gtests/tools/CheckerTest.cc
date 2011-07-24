#include "tools/Checker.hh"
#include "alg/ContextALG.hh"
#include "bo/ContextBO.hh"
#include "bo/LocationBO.hh"
#include "bo/MachineBO.hh"
#include "bo/NeighborhoodBO.hh"
#include "bo/ProcessBO.hh"
#include "bo/RessourceBO.hh"
#include "bo/ServiceBO.hh"
#include <vector>
#include <tr1/unordered_set>
#include <gtest/gtest.h>
using namespace std;
using namespace std::tr1;

//FIXME : refactorer afin de supprimer les duplications de code.

class CheckerFixture : public Checker, public testing::Test
{};

TEST_F(CheckerFixture, checkCapaNotTransient){
    ContextBO contextBO_l;
    contextBO_l.addRessource(new RessourceBO(0, false, 0));
    LocationBO* pLoc_l = new LocationBO(0);
    contextBO_l.addLocation(pLoc_l);
    NeighborhoodBO* pNeigh_l = new NeighborhoodBO(0);
    contextBO_l.addNeighborhood(pNeigh_l);

    contextBO_l.addMachine(new MachineBO(0, pLoc_l, pNeigh_l, vector<int>(1, 15), vector<int>(1, 10)));
    contextBO_l.addMachine(new MachineBO(1, pLoc_l, pNeigh_l, vector<int>(1, 20), vector<int>(1, 10)));
    ServiceBO* pService_l = new ServiceBO(0, 0, unordered_set<int>());
    contextBO_l.addService(pService_l);

    ProcessBO* pProcess1_l = new ProcessBO(0, pService_l, vector<int>(1, 14), 0);
    pProcess1_l->setMachineInit(contextBO_l.getMachine(0));
    ProcessBO* pProcess2_l = new ProcessBO(1, pService_l, vector<int>(1, 4), 0);
    pProcess2_l->setMachineInit(contextBO_l.getMachine(1));
    contextBO_l.addProcess(pProcess1_l);
    contextBO_l.addProcess(pProcess2_l);

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
    LocationBO* pLoc_l = new LocationBO(0);
    contextBO_l.addLocation(pLoc_l);
    NeighborhoodBO* pNeigh_l = new NeighborhoodBO(0);
    contextBO_l.addNeighborhood(pNeigh_l);

    contextBO_l.addMachine(new MachineBO(0, pLoc_l, pNeigh_l, vector<int>(1, 15), vector<int>(1, 10)));
    contextBO_l.addMachine(new MachineBO(1, pLoc_l, pNeigh_l, vector<int>(1, 20), vector<int>(1, 10)));
    ServiceBO* pService_l = new ServiceBO(0, 0, unordered_set<int>());
    contextBO_l.addService(pService_l);

    ProcessBO* pProcess1_l = new ProcessBO(0, pService_l, vector<int>(1, 14), 0);
    pProcess1_l->setMachineInit(contextBO_l.getMachine(0));
    ProcessBO* pProcess2_l = new ProcessBO(1, pService_l, vector<int>(1, 4), 0);
    pProcess2_l->setMachineInit(contextBO_l.getMachine(1));
    contextBO_l.addProcess(pProcess1_l);
    contextBO_l.addProcess(pProcess2_l);

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
