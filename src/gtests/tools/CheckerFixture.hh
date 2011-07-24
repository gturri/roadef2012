#include "tools/Checker.hh"
#include <vector>
#include <tr1/unordered_set>
#include <gtest/gtest.h>
using namespace std;
using namespace std::tr1;

class ContextBO;
class LocationBO;
class ProcessBO;
class NeighborhoodBO;
class ServiceBO;

class CheckerFixture : public Checker, public testing::Test{
    public:
        /**
         * Cree un process et l'ajoute au context
         */
        ProcessBO* buildProcess(int idP_p, ServiceBO* pService_p, const vector<int>& vRequirements_p, int pmc_p, int idxMachineInit_p, ContextBO* pContextBO_p);

        ServiceBO* buildService(int idS_p, int spreadMin_p, const unordered_set<int>& sDependances_p, ContextBO* pContextBO_p);

        LocationBO* buildLocation(int idLoc_p, ContextBO* pContextBO_p);
        NeighborhoodBO* buildNeigh(int idNeigh_p, ContextBO* pContextBO_p);
        MachineBO* buildMachine(int idMachine_p, int idLoc_p, int idNeigh_p, const vector<int>& capa_p, const vector<int>& safetyCapa_p, ContextBO* pContextBO_p);


};

