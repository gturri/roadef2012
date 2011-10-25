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
        /**
         * @param Le ContextBO qui decrit l'instance traitee par ce ContextALG
         * @param Doit-on ecrire une sol des qu'une meilleure sol est trouvee ?
         * (si ce ContextALG decrit un sous pb, cette variable doit etre FALSE !)
         * @param Doit-on checker la sol init fournie par le ContextBO ?
         */
        ContextALG(ContextBO const * pContextBO_p, bool mustWriteBestSol_p=true, bool solInitToCheck_p=false);
        ContextBO const * getContextBO() const;

        /* TODO : ecrire des tests pour ces methodes
         * TODO : ajouter un cache pour ces methodes (et gestion de son invalidation lors de la modif de la sol) (ou pas, si c'est au detriment des perfs et qu'il vaut mieux que les classes clientes le gere...)
         */
        unordered_set<int> getNeighsUsedByService(int idxService_p) const;
        unordered_set<int> getNeighsUsedByService(ServiceBO const * pService_p) const;

        /* TODO : tester cette methode */
        /* TODO : ameliorer les perfs de cette methode par exemple en calculant
         * tous les resultats, et en gerant un cache...
         */
        /**
         * Retourne la quantite de ressource consomme par les process d'une machine donnee
         */
        int getRessUsedOnMachine(int idxRess_p, int idxMachine_p) const;

        void setMustWriteBestSol(bool mustWriteBestSol_p);

        vector<int> getCurrentSol() const;
        void setCurrentSol(const vector<int>& curSol_p);

        /**
         * Evalue "from scratch" la solution soumise, et la memorise s'il s'agit de la meilleure
         * Attention : methode lente a cause de l'evaluation
         * @param La solution a evaluer
         * @param FALSE si on peut supposer que la validite est ok, TRUE s'il faut la verifier
         * @return TRUE si une maj a ete effectuee
         */
        bool checkCompletAndMajBestSol(const vector<int>& candidatBestSol_p, bool checkValidite_p);

        /**
         * Maj la meilleure solution si celle fournie est mieux.
         * Attention : on fait confiance a la classe cliente pour fournir un score correct
         * @return TRUE si une maj a ete effectuee
         */
        bool checkRapideAndMajBestSol(const vector<int>& candidatBestSol_p, uint64_t score_p);

        vector<int> getBestSol() const;
        uint64_t getScoreBestSol() const;

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

        /**
         * Meilleure solution trouvee jusqu'ici.
         * Attention : on accorde une grande confiance aux classes clientes pour
         * la maj de cet attribut (pour des raisons de perf')
         */
        vector<int> bestSol_m;

        /**
         * score de la meilleure solution
         */
        uint64_t bestScore_m;

        /**
         * Quand une meilleure sol est trouvee, celle-ci est aussitot ecrite.
         * Ce comportement n'est pas souhaitable lorsque l'on travaille sur un sous-contexte
         * Cette attribut permet de piloter ce comportement
         */
        bool mustWriteBestSol_m;
};

#endif
