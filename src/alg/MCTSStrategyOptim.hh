#ifndef MCTSSTRATEGYOPTIM_HH
#define MCTSSTRATEGYOPTIM_HH
#include "alg/StrategyOptim.hh"

/**
 * Squelette de strategie d'optimisation, avec un peu de viande autours,
 * histoire d'illustrer l'utilisation de cette abstraction
 */
class MCTSStrategyOptim : public StrategyOptim {
        virtual ContextALG run(ContextALG contextAlg_p, time_t heureFinMaxPreconisee_p);

};

#endif
