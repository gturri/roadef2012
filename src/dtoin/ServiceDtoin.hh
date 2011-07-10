#ifndef SERVICEDTOIN_HH
#define SERVICEDTOIN_HH
#include <fstream>
using namespace std;

class ContextBO;

class ServiceDtoin{
    public:
        void read(istream& is_p, ContextBO* pContextBO_p);

};

#endif
