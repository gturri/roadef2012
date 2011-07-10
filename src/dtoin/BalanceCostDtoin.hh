#ifndef BALANCECOSTDTOIN_HH
#define BALANCECOSTDTOIN_HH
#include <iostream>
using namespace std;

class ContextBO;

/**
 * Classe en charge de lire la section BalanceCost du fichier d'instance.
 * Cette classe ne devrait pas etre utilisee directement, mais n'etre manipulee qu'a travers l'#InstanceReaderDtoin
 */
class BalanceCostDtoin {
    public:
        void read(istream& is_p, ContextBO* pContextBO_p);
};

#endif
