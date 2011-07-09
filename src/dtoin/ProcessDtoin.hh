#ifndef PROCESSDTOIN_HH
#define PROCESSDTOIN_HH
#include <iostream>
using namespace std;

class ContextBO;

class ProcessDtoin {
    public:
        void read(istream& ifs_p, ContextBO* pContextBO_p);
};

#endif
