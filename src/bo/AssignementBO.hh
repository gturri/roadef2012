#ifndef ASSIGNEMENTBO_HH
#define ASSIGNEMENTBO_HH
#include <tr1/unordered_set>
using namespace std::tr1;

class ProcessBO;
class MachineBO;

class AssignementBO{
    private:
        unordered_map<ProcessBO*, MachineBO*> assignement_m;
};

#endif
