#ifndef STRATEGYOPTIM_HH
#define STRATEGYOPTIM_HH
#include "alg/ContextALG.hh"
#include <ctime>


/**
 * Interface dont derive toutes les methodes d'optims,
 * afin de simplifier la manipulation de celles-ci
 */
class StrategyOptim {
    public:
        virtual ~StrategyOptim();

        /**
         * Effectue une optim en partant d'une solution initiale,
         * se charge d'ecrire la meilleure solution trouvee via le SolutionDtoout,
         * et renvoie la solution "finale" voulu
         * @param contextAlg_p La solution initiale
         * @param heureFinMaxPreconisee La date de fin a laquelle la strategie devrait retourner au plus tard. La strategie est toutefois libre de respecter ou non cette indication
         * @return Une solution "finale". Il peut s'agir de la meilleure solution trouvee,
         * de l'etat final, d'autre chose...
         */
        virtual ContextALG run(ContextALG contextAlg_p, time_t heureFinMaxPreconisee_p) = 0;
};

#endif
