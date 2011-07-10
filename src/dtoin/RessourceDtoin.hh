#ifndef RESSOURCEDTOIN_HH
#define RESSOURCEDTOIN_HH
#include <fstream>
using namespace std;

class ContextBO;

class RessourceDtoin {
    public:
        /**
         * @param is_p Le flux a lire
         * @param pContextBO_p Le context a peupler
         */
        void read(istream& is_p, ContextBO* pContextBO_p);

};

#endif
