#ifndef RESSOURCEDTOIN_HH
#define RESSOURCEDTOIN_HH
#include <fstream>
using namespace std;

class ContextBO;

class RessourceDtoin {
    public:
        /**
         * @param ifs_p Le flux a lire
         * @param pContextBO_p Le context a peupler
         */
        void read(ifstream& ifs_p, ContextBO* pContextBO_p);

};

#endif
