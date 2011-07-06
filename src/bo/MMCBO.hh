#ifndef MMCBO_HH
#define MMCBO_HH
#include <vector>
using namespace std;

class MachineBO;

class MMCBO {
    public:
        int getCost(Machine* from_l, Machine* to_l);

    private:
        vector<vector<int> > costs_l; // tq cost_l[from][to]
};

#endif
