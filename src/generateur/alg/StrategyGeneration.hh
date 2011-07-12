#ifndef STRATEGYGENERATION_HH
#define STRATEGYGENERATION_HH
#include <list>
#include <memory>
#include <boost/program_options.hpp>
using namespace std;
using namespace boost::program_options;

class ContextBO;

class StrategyGeneration {
    public:
        virtual ~StrategyGeneration() = 0;

        /**
         * Methode de generation d'instance.
         * @param arg_p Les arguments fournis au binaire (via la ligne de commande)
         *  afin de permettre a chaque classe concrete de solliciter ces propres arguments
         * @return la liste des instances generees, sous forme d'une liste de ContextBO
         * Il suffit ensuite de fournir ces ContextBO a un writer pour generer les fichiers souhaites
         * (Les perfs n'etant pas cruciales sur ce binaire, on en se prive pas d'utiliser des smart pointers)
         */
        virtual list<shared_ptr<ContextBO*> > generate(const variables_map& arg_p) = 0;
};

#endif
