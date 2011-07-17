#ifndef INSTANCEWRITERHUMANREADABLE_HH
#define INSTANCEWRITERHUMANREADABLE_HH
#include "dtoout/InstanceWriterInterface.hh"
#include <tr1/unordered_set>
#include <vector>
using namespace std;
using namespace std::tr1;

class ContextBO;
class MachineBO;
class ProcessBO;
class ServiceBO;

/**
 * Ecrit une instance dans un format "human-friendly"
 */
class InstanceWriterHumanReadable : public InstanceWriterInterface {
    protected:
        virtual string writeOnString(ContextBO const * pContextBO_p);

    private:
        static string writeRessources(ContextBO const * pContextBO_p);
        static string writeMachines(ContextBO const * pContextBO_p);
        static string writeServices(ContextBO const * pContextBO_p);
        static string writeProcesses(ContextBO const * pContextBO_p);
        static string writeBalanceCost(ContextBO const * pContextBO_p);
        static string writePoids(ContextBO const * pContextBO_p);

        static string writeMajorTitle(const string& title_p);
        static string writeSectionTitle(const string& title_p);
        static string writeSubTitle(const string& typeEntite_p, int idx_p, int nbTotal_p);
        static string writeTitle(const string& titre_p, int level_p);
        static string writeCarac(const string& caracName_p, int carac_p);
        static string writeListOfCaracs(const string& caracsName_p, const vector<int>& caracs_p);
        static string writeListOfCaracs(const string& caracsName_p, const unordered_set<int>& caracs_p);
        static string writeQuantite(int quantite_p);

};


#endif
