#ifndef BALANCECOSTDTOIN_HH
#define BALANCECOSTDTOIN_HH
#include <iostream>
using namespace std;

class ContextBO;

class BalanceCostDtoin {
    public:
        void read(istream& ifs_p, ContextBO* pContextBO_p);
};

#endif
