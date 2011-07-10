#ifndef PROCESSDTOIN_HH
#define PROCESSDTOIN_HH
#include <iostream>
using namespace std;

/**
 * Classe en charge de la lecture de la section des Processes, sur le fichier d'instance.
 * Cette classe ne devrait pas etre utilisee directement, mais n'etre manipulee qu'a travers l'#InstanceReaderDtoin
 */
class ContextBO;

class ProcessDtoin {
    public:
        void read(istream& is_p, ContextBO* pContextBO_p);
};

#endif
