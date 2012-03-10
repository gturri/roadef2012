/*
 * Copyright (c) 2011 Pierre-Etienne Bougué <pe.bougue(a)gmail.com>
 * Copyright (c) 2011 Florian Colin <florian.colin28(a)gmail.com>
 * Copyright (c) 2011 Kamal Fadlaoui <kamal.fadlaoui(a)gmail.com>
 * Copyright (c) 2011 Quentin Lequy <quentin.lequy(a)gmail.com>
 * Copyright (c) 2011 Guillaume Pinot <guillaume.pinot(a)tremplin-utc.net>
 * Copyright (c) 2011 Cédric Royer <cedroyer(a)gmail.com>
 * Copyright (c) 2011 Guillaume Turri <guillaume.turri(a)gmail.com>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */

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
