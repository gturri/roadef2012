#ifndef PROCESSBO_HH
#define PROCESSBO_HH
#include <vector>
using namespace std;

class MachineBO;
class RessourceBO;
class ServiceBO;

class ProcessBO {
    public:
        ProcessBO(int id_p, ServiceBO* pService_p, const vector<int>& vRequirements_p,  int pmc_p);

        int getId() const;
        ServiceBO* getService() const;
        int getRequirement(int idxRess_p) const;
        void setMachineInit(MachineBO* pMachine_p);
        MachineBO* getMachineInit() const;
        int getPMC() const;

    private:
        const int id_m;

        /**
         * Service auquel appartient le process
         */
        ServiceBO* const pService_m;

        /**
         * Ressources necessaires au process
         * requirements[pRess_l->getId()] => quantite necessaire de ressources du type donne
         */
        const vector<int> vRequirements_m;

        /**
         * Machine sur laquel le process est place initialement
         */
        MachineBO* pMachineInit_m;

        /**
         * Process move cost
         * Cad : cout ajoute a la fonction objectif si le process n'est pas sur sa machine initiale
         */
        const int pmc_m;
};


#endif
