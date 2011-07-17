#ifndef INSTANCEWRITERDTOOUT_HH
#define INSTANCEWRITERDTOOUT_HH
#include "dtoout/InstanceWriterInterface.hh"
#include <string>
using namespace std;

class ContextBO;
class MachineBO;
class ProcessBO;
class ServiceBO;

/**
 * Ecrit un ContextBO au format du challenge
 * Cette classe est destinee a etre utilisee :
 * - a des fins de test
 * - par le generateur d'instances
 *
 * Nb : cette classe n'ayant pas vocation a etre utilisee durant l'optim, la clarte du code
 * est clairement privilegiee par rapport au perf (ce qui explique les multiples 
 * conversions string <-> ostringstream dans les deux sens)
 */
class InstanceWriterDtoout : public InstanceWriterInterface {
    public:

    protected:
        virtual string writeOnString(ContextBO const * pContextBO_p);
        static string writeRessources(ContextBO const * pContextBO_p);
        static string writeMachines(ContextBO const * pContextBO_p);
        static string writeServices(ContextBO const * pContextBO_p);
        static string writeProcesses(ContextBO const * pContextBO_p);
        static string writeBalanceCost(ContextBO const * pContextBO_p);
        static string writePoids(ContextBO const * pContextBO_p);

        static string writeMachineCapa(ContextBO const * pContextBO_p, MachineBO* pMachine_p, bool useSafetyCapa_p);
        static string writeMachineSafetyCapa(MachineBO* pMachine_p);
        static string writeMachineMMC(ContextBO const * pContextBO_p, MachineBO* pMachine_p);

        static string writeServiceDependances(ContextBO const * pContextBO_p, ServiceBO* pService_p);
        static string writeProcessRequirements(ContextBO const * pContextBO_p, ProcessBO* pProcess_p);
};

#endif
