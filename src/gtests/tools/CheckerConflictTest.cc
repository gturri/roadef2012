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

TEST_F(CheckerFixture, checkConflit){  
    ContextBO contextBO_l;
    contextBO_l.addRessource(new RessourceBO(0, false, 0));

    buildMachine(0, 0, 0, vector<int>(1, 15), vector<int>(1, 10), &contextBO_l);
    buildMachine(1, 0, 0, vector<int>(1, 20), vector<int>(1, 10), &contextBO_l);
    ServiceBO* pService0_l = buildService(0, 0, unordered_set<int>(), &contextBO_l);
    ServiceBO* pService1_l = buildService(1, 0, unordered_set<int>(), &contextBO_l);

    buildProcess(0, pService0_l, vector<int>(1, 0), 0, 0, &contextBO_l);
    buildProcess(1, pService0_l, vector<int>(1, 0), 0, 1, &contextBO_l);
    buildProcess(2, pService1_l, vector<int>(1, 0), 0, 0, &contextBO_l);

}
