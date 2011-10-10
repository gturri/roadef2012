#ifndef SEQUENCESTRATEGYOPTIM_HH
#define SEQUENCESTRATEGYOPTIM_HH
#include "alg/StrategyOptim.hh"
#include <list>
using namespace std;

class SequenceStrategyOptim : public StrategyOptim {
    public:
        ~SequenceStrategyOptim();

        ContextALG run(ContextALG contextAlg_p, time_t heureFinMaxPreconisee_p, const variables_map& opt_p);



    private:
        /**
         * Succession de methodes a faire tourner
         */
        list<StrategyOptim*> sequence_m;
};


#endif
