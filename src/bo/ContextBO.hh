#ifndef CONTEXTBO_HH
#define CONTEXTBO_HH
#include <vector>
using namespace std;

class RessourceBO;

//FIXME : Si cette classe grossi trop, ajouter des managerBO pour chaque type d'objet gere actuellement par le ContextBO
class ContextBO {
    public:
        ~ContextBO();

        void addRessource(RessourceBO* pRess_p);
        int getNbRessources() const;
        RessourceBO* getRessource(int id_p) const;

    private:
        vector<RessourceBO*> ressources_m;
};

#endif
