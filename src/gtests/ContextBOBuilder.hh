#include <vector>
#include <tr1/unordered_set>
using namespace std;
using namespace std::tr1;

class BalanceCostBO;
class ContextBO;
class LocationBO;
class ProcessBO;
class MachineBO;
class NeighborhoodBO;
class ServiceBO;

class ContextBOBuilder {
    public:
        /**
         * Cree un process et l'ajoute au context
         */
        static ProcessBO* buildProcess(int idP_p, ServiceBO* pService_p, const vector<int>& vRequirements_p, int pmc_p, int idxMachineInit_p, ContextBO* pContextBO_p);

        static ServiceBO* buildService(int idS_p, int spreadMin_p, const unordered_set<int>& sDependances_p, ContextBO* pContextBO_p);

        static LocationBO* buildLocation(int idLoc_p, ContextBO* pContextBO_p);
        static NeighborhoodBO* buildNeigh(int idNeigh_p, ContextBO* pContextBO_p);
        static MachineBO* buildMachine(int idMachine_p, int idLoc_p, int idNeigh_p, const vector<int>& capa_p, const vector<int>& safetyCapa_p, ContextBO* pContextBO_p);

        static BalanceCostBO* buildBalanceCost(int idxRess1_p, int idxRess2_p, int target_p, int poids_p, ContextBO* pContextBO_p);

        /**
         * Ajoute un MMCBO ayant la taille adequate, et des couts tous nuls
         */
        static void buildDefaultMMC(ContextBO* pContextBO_p);


};

