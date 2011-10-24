#ifndef PRINTDEBUGSTRATEGY_HH
#define PRINTDEBUGSTRATEGY_HH
#include "alg/StrategyOptim.hh"

/**
 * Utile pour du debug : crache des logs decrivant une solution
 */
class PrintDebugStrategy : public StrategyOptim {
        virtual ContextALG run(ContextALG contextAlg_p, time_t heureFinMaxPreconisee_p, const variables_map& opt_p);
};


#endif
