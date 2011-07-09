#ifndef CONTEXTBO_HH
#define CONTEXTBO_HH
#include <vector>
using namespace std;

class RessourceBO;
class MachineBO;
class LocationBO;
class NeighborhoodBO;
class MMCBO;
class ProcessBO;
class ServiceBO;
class BalanceCostBO;

/* FIXME : Cette classe est enorme a cause de duplication de code. Ne pas hesiter a refactorer
 * (mais uniquement a condition d'avoir une bonne solution, et de ne pas deporter ce bourbier de code au niveau des classes clientes)
 */

/**
 * Represente une instance, et permet d'acceder a chacune des entites de celle-ci
 */
class ContextBO {
    public:
        ContextBO();
        ~ContextBO();

        void setMMCBO(MMCBO* pMMC_p);
        MMCBO* getMMCBO() const;

        void addRessource(RessourceBO* pRess_p);
        int getNbRessources() const;
        RessourceBO* getRessource(int id_p) const;

        void addLocation(LocationBO* pLoc_p);
        int getNbLocations() const;
        LocationBO* getLocation(int idx_p) const;

        void addNeighborhood(NeighborhoodBO* pNeigh_p);
        int getNbNeighborhoods() const;
        NeighborhoodBO* getNeihborhood(int idx_p) const;

        void addMachine(MachineBO* pMachine_p);
        int getNbMachines() const;
        MachineBO* getMachine(int idx_p) const;

        void addService(ServiceBO* pService_p);
        int getNbServices() const;
        ServiceBO* getService(int idx_p) const;

        void addProcess(ProcessBO* pProcess_p);
        int getNbProcesses() const;
        ProcessBO* getProcess(int idx_p) const;
        
        void addBalanceCost(BalanceCostBO* pBalanceCost_p);
        int getNbBalanceCosts() const;
        BalanceCostBO* getBalanceCost(int idx_p) const;

        void setPoidsPMC(int poids_p);
        int getPoidsPMC() const;

        void setPoidsSMC(int poids_p);
        int getPoidsSMC() const;

        void setPoidsMMC(int poids_p);
        int getPoidsMMC() const;

    private:
        vector<RessourceBO*> ressources_m;
        vector<MachineBO*> machines_m;
        vector<LocationBO*> locations_m;
        vector<NeighborhoodBO*> neighborhoods_m;
        vector<ServiceBO*> services_m;
        vector<ProcessBO*> processes_m;
        vector<BalanceCostBO*> balanceCosts_m;
        MMCBO* pMMCBO_m;

        /**
         * Poids du critere Process Move Cost
         */
        int poidsPMC_m;

        /**
         * Poids du critere Service Move Cost
         */
        int poidsSMC_m;

        /**
         * Poids du critere Machine Move Cost
         */
        int poidsMMC_m;

};

#endif
