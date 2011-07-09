#ifndef TESTDTOINHELPER_HH
#define TESTDTOINHELPER_HH

#include <string>
using namespace std;

class ContextBO;

class TestDtoinHelper {
    public:
        static string getMachineTestData();
        static string getRessourceTestData();
        static string getServiceTestData();

        static void loadTestDataRessource(ContextBO* pContextBO_p);
        static void loadTestDataMachine(ContextBO* pContextBO_p);
        static void loadTestDataService(ContextBO* pContextBO_p);
};

#endif
