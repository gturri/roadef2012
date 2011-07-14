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
        virtual string writeOnString(ContextBO* pContextBO_p);
        static string writeRessources(ContextBO* pContextBO_p);
        static string writeMachines(ContextBO* pContextBO_p);
        static string writeServices(ContextBO* pContextBO_p);
        static string writeProcesses(ContextBO* pContextBO_p);
        static string writeBalanceCost(ContextBO* pContextBO_p);
        static string writePoids(ContextBO* pContextBO_p);

        static string writeMachineCapa(ContextBO* pContextBO_p, MachineBO* pMachine_p, bool useSafetyCapa_p);
        static string writeMachineSafetyCapa(MachineBO* pMachine_p);
        static string writeMachineMMC(ContextBO* pContextBO_p, MachineBO* pMachine_p);

        static string writeServiceDependances(ContextBO* pContextBO_p, ServiceBO* pService_p);
        static string writeProcessRequirements(ContextBO* pContextBO_p, ProcessBO* pProcess_p);
};

#endif
