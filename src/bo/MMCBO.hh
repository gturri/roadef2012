#ifndef MMCBO_HH
#define MMCBO_HH
#include <vector>
using namespace std;

class MachineBO;

class MMCBO {
    public:
        MMCBO(const vector<vector<int> >& costs_p);
        int getCost(MachineBO* from_p, MachineBO* to_p) const;
        int getCost(int idxMachineFrom_p, int idxMachineTo_p) const;

        vector<int> getCosts(MachineBO* from_p) const;

    private:
        vector<vector<int> > costs_m; // tq cost_m[from][to]
};

#endif
