#ifndef STRATEGYSELECTER_HH
#define STRATEGYSELECTER_HH
#include <boost/program_options.hpp>
using namespace boost::program_options;

class StrategyOptim;

/**
 * Factory de strategies d'optim
 */
class StrategySelecter {
    public:
        /**
         * Etant donne les arguments de la ligne de commande, retourne la strategie d'optim souhaitee
         * Il appartient a la classe cliente de deleter cet objet retourne
         */
        static StrategyOptim* buildStrategy(const variables_map& opt_p);
};

#endif
