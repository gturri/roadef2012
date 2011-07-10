#include "gtests/dtoin/TestDtoinHelper.hh"
#include "dtoin/BalanceCostDtoin.hh"
#include "dtoin/MachineDtoin.hh"
#include "dtoin/PoidsDtoin.hh"
#include "dtoin/ProcessDtoin.hh"
#include "dtoin/RessourceDtoin.hh"
#include "dtoin/ServiceDtoin.hh"
#include <sstream>
using namespace std;

void TestDtoinHelper::loadTestDataRessource(ContextBO* pContextBO_p){
    RessourceDtoin reader_l;
    istringstream iss_l(getRessourceTestData());
    reader_l.read(iss_l, pContextBO_p);
}

void TestDtoinHelper::loadTestDataMachine(ContextBO* pContextBO_p){
    MachineDtoin reader_l;
    istringstream iss_l(getMachineTestData());
    reader_l.read(iss_l, pContextBO_p);
}

void TestDtoinHelper::loadTestDataService(ContextBO* pContextBO_p){
    ServiceDtoin reader_l;
    istringstream iss_l(getServiceTestData());
    reader_l.read(iss_l, pContextBO_p);
}

void TestDtoinHelper::loadTestDataProcess(ContextBO* pContextBO_p){
    ProcessDtoin reader_l;
    istringstream iss_l(getProcessTestData());
    reader_l.read(iss_l, pContextBO_p);
}

void TestDtoinHelper::loadTestDataBalanceCost(ContextBO* pContextBO_p){
    BalanceCostDtoin reader_l;
    istringstream iss_l(getBalanceCostTestData());
    reader_l.read(iss_l, pContextBO_p);
}

void TestDtoinHelper::loadTestDataPoids(ContextBO* pContextBO_p){
    PoidsDtoin reader_l;
    istringstream iss_l(getPoidsTestData());
    reader_l.read(iss_l, pContextBO_p);
}

string TestDtoinHelper::getMachineTestData(){
    return string("4 \
 \
0 \
0 \
30 400 \
16 80 \
0 1 4 5 \
 \
0 \
0 \
10 240 \
8 160 \
1 0 3 4 \
 \
1 \
1 \
15 100 \
12 80 \
4 3 0 2 \
 \
1 \
2 \
10 100 \
8 80 \
5 4 2 0");
}

string TestDtoinHelper::getRessourceTestData(){
    return string("2 \
 \
1 \
100 \
 \
0 \
10");
}

string TestDtoinHelper::getServiceTestData(){
    return string("2 \
 \
2 \
0 \
 \
1 \
1 \
0 \
 \
3 \
0 \
12 10 \
1000 \
 \
0 \
10 20 \
100 \
 \
1 \
6 200 \
1");
}

string TestDtoinHelper::getProcessTestData(){
    return string("3 \
0 \
12 10 \
1000 \
\
0 \
10 20 \
100 \
\
1 \
6 200 \
1");
}

string TestDtoinHelper::getBalanceCostTestData(){
    return string("1 \
0 1 20 \
10");
}

string TestDtoinHelper::getPoidsTestData(){
    return string("1 \
10 \
100");
}
