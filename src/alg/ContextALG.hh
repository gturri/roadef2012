#ifndef CONTEXTALG_HH
#define CONTEXTALG_HH
#include <vector>
#include <tr1/unordered_set>
using namespace std;
using namespace std::tr1;

class ContextBO;
class ServiceBO;

class ContextALG {
    public:
        ContextALG(ContextBO const * pContextBO_p);
        ContextBO const * getContextBO() const;

        /* TODO : ecrire des tests pour ces methodes
         * TODO : ajouter un cache pour ces methodes (et gestion de son invalidation lors de la modif de la sol) (ou pas, si c'est au detriment des perfs et qu'il vaut mieux que les classes clientes le gere...)
         */
        unordered_set<int> getNeighsUsedByService(int idxService_p) const;
        unordered_set<int> getNeighsUsedByService(ServiceBO const * pService_p) const;

        vector<int> getCurrentSol() const;
        void setCurrentSol(const vector<int>& curSol_p);

    private:
        /**
         * Represente l'instance en cours.
         * Plusieurs ContextALG peuvent partager le meme ContextBO,
         * donc il va appartenir aux classes clients de gerer le delete du ContextBO
         * De meme, cet attribut ne justifie ni un operator= ni un cpy ctr customise
         */
        ContextBO const * pContextBO_m;

        /**
         * vecteur de taille nbProcesses representant la solution actuelle
         * currentSol_m[idxProcess] = idxMachine sur laquelle il est affecte
         */
        vector<int> currentSol_m;
};

#endif
