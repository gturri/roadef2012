#ifndef POIDSDTOIN_HH
#define POIDSDTOIN_HH
#include <iostream>
using namespace std;

class ContextBO;

/**
 * Classe en charge de la lecture des poids des objectifs, sur le fichier d'instance
 * Cette classe ne devrait pas etre utilisee directement, mais n'etre manipulee qu'a travers l'#InstanceReaderDtoin
 */
class PoidsDtoin {
    public:
        void read(istream& is_p, ContextBO* pContextBO_p);
};

#endif
