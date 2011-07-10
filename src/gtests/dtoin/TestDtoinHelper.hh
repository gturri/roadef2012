#ifndef TESTDTOINHELPER_HH
#define TESTDTOINHELPER_HH

#include <string>
using namespace std;

class ContextBO;

class TestDtoinHelper {
    public:
        static void loadTestDataRessource(ContextBO* pContextBO_p);
        static void loadTestDataMachine(ContextBO* pContextBO_p);
        static void loadTestDataService(ContextBO* pContextBO_p);
        static void loadTestDataProcess(ContextBO* pContextBO_p);
        static void loadTestDataBalanceCost(ContextBO* pContextBO_p);
        static void loadTestDataPoids(ContextBO* pContextBO_p);
        static void loadTestDataSolInit(ContextBO* pContextBO_p);

    private:
        static string getMachineTestData();
        static string getRessourceTestData();
        static string getServiceTestData();
        static string getProcessTestData();
        static string getBalanceCostTestData();
        static string getPoidsTestData();
        static string getSolInitTestData();
};

#endif
