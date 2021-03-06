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

#include "dtoout/InstanceWriterDtoout.hh"
#include "bo/BalanceCostBO.hh"
#include "bo/ContextBO.hh"
#include "bo/LocationBO.hh"
#include "bo/MachineBO.hh"
#include "bo/MMCBO.hh"
#include "bo/NeighborhoodBO.hh"
#include "bo/ProcessBO.hh"
#include "bo/RessourceBO.hh"
#include "bo/ServiceBO.hh"
#include <iostream>
#include <sstream>
using namespace std;

string InstanceWriterDtoout::writeOnString(ContextBO const * pContextBO_p){
    ostringstream oss_l;
    oss_l << writeRessources(pContextBO_p)
        << writeMachines(pContextBO_p)
        << writeServices(pContextBO_p)
        << writeProcesses(pContextBO_p)
        << writeBalanceCost(pContextBO_p)
        << writePoids(pContextBO_p);
    return oss_l.str();
}

string InstanceWriterDtoout::writeRessources(ContextBO const * pContextBO_p){
    ostringstream oss_l;
    int nbRess_l = pContextBO_p->getNbRessources();
    oss_l << nbRess_l << endl;

    for ( int idxRess_l=0 ; idxRess_l < nbRess_l ; idxRess_l++ ){
        RessourceBO* pRess_l = pContextBO_p->getRessource(idxRess_l);
        oss_l << endl
            << pRess_l->isTransient() << endl
            << pRess_l->getWeightLoadCost() << endl;
    }
    return oss_l.str();
}

string InstanceWriterDtoout::writeMachines(ContextBO const * pContextBO_p){
    ostringstream oss_l;
    int nbMachines_l = pContextBO_p->getNbMachines();
    oss_l << nbMachines_l << endl;

    for ( int idxMachine_l=0 ; idxMachine_l < nbMachines_l ; idxMachine_l++ ){
        MachineBO* pMachine_l = pContextBO_p->getMachine(idxMachine_l);
        oss_l << endl
            << pMachine_l->getNeighborhood()->getId() << endl
            << pMachine_l->getLocation()->getId() << endl
            << writeMachineCapa(pContextBO_p, pMachine_l, false) << endl
            << writeMachineCapa(pContextBO_p, pMachine_l, true) << endl
            << writeMachineMMC(pContextBO_p, pMachine_l) << endl;
    }

    return oss_l.str();
}

string InstanceWriterDtoout::writeMachineCapa(ContextBO const * pContextBO_p, MachineBO* pMachine_p, bool useSafetyCapa_p){
    ostringstream oss_l;
    int nbRess_l = pContextBO_p->getNbRessources();

    for ( int idxRess_l=0 ; idxRess_l < nbRess_l ; idxRess_l++ ){
        if ( useSafetyCapa_p ){
            oss_l << pMachine_p->getSafetyCapa(idxRess_l);
        } else {
            oss_l << pMachine_p->getCapa(idxRess_l);
        }

        if ( idxRess_l != nbRess_l -1 ){
            oss_l << " ";
        }
    }

    return oss_l.str();
}

string InstanceWriterDtoout::writeMachineMMC(ContextBO const * pContextBO_p, MachineBO* pMachine_p){
    ostringstream oss_l;
    MMCBO* pMMC_l = pContextBO_p->getMMCBO();
    int nbMachines_l = pContextBO_p->getNbMachines();
    for (int idxMachine_l=0 ; idxMachine_l < nbMachines_l ; idxMachine_l++ ){
        oss_l << pMMC_l->getCost(pMachine_p->getId(), idxMachine_l);
        if ( idxMachine_l != nbMachines_l -1 ){
            oss_l << " ";
        }
    }

    return oss_l.str();
}

string InstanceWriterDtoout::writeServices(ContextBO const * pContextBO_p){
    ostringstream oss_l;
    int nbServices_l = pContextBO_p->getNbServices();
    oss_l << nbServices_l << endl;

    for ( int idxService_l=0 ; idxService_l < nbServices_l ; idxService_l++ ){
        ServiceBO* pService_l = pContextBO_p->getService(idxService_l);

        oss_l << endl
            << pService_l->getSpreadMin() << endl
            << writeServiceDependances(pContextBO_p, pService_l) << endl;
    }
    return oss_l.str();
}

string InstanceWriterDtoout::writeServiceDependances(ContextBO const * pContextBO_p, ServiceBO* pService_p){
    int nbServices_l = pContextBO_p->getNbServices();
    ostringstream oss_l;
    oss_l << pService_p->getNbServicesIDependOn();
    if ( pService_p->getNbServicesIDependOn() == 0 ){
        //Permet de ne pas se prendre la tete avec le endl qui risque de faire un double saut de ligne sinon
        return oss_l.str();
    }
    
    oss_l << endl;

    bool premiereDepTrouvee_l(false);
    for ( int idxService_l=0 ; idxService_l < nbServices_l ; idxService_l++ ){
        if ( pService_p->iDependOn(idxService_l) ){
            if ( premiereDepTrouvee_l ){
                oss_l << " ";
            }
            premiereDepTrouvee_l = true;
            oss_l << idxService_l;
        }
    }
    return oss_l.str();
}

string InstanceWriterDtoout::writeProcesses(ContextBO const * pContextBO_p){
    ostringstream oss_l;
    int nbProcesses_l = pContextBO_p->getNbProcesses();
    oss_l << nbProcesses_l;

    for ( int idxP_l=0 ; idxP_l < nbProcesses_l ; idxP_l++ ){
        ProcessBO* pProcess_l = pContextBO_p->getProcess(idxP_l);
        oss_l << endl
            << pProcess_l->getService()->getId() << endl
            << writeProcessRequirements(pContextBO_p, pProcess_l) << endl
            << pProcess_l->getPMC() << endl;
    }

    return oss_l.str();
}

string InstanceWriterDtoout::writeProcessRequirements(ContextBO const * pContextBO_p, ProcessBO* pProcess_p){
    ostringstream oss_l;
    int nbRess_l = pContextBO_p->getNbRessources();
    for ( int idxRess_l=0 ; idxRess_l < nbRess_l ; idxRess_l++ ){
        oss_l << pProcess_p->getRequirement(idxRess_l);
        if ( idxRess_l != nbRess_l - 1 ){
            oss_l << " ";
        }
    }
    return oss_l.str();
}

string InstanceWriterDtoout::writeBalanceCost(ContextBO const * pContextBO_p){
    ostringstream oss_l;
    int nbBC_l = pContextBO_p->getNbBalanceCosts();
    oss_l << nbBC_l;
    if ( nbBC_l == 0 ){
        oss_l << endl;
    }

    for ( int idxBC_l=0 ; idxBC_l < nbBC_l ; idxBC_l++ ){
        BalanceCostBO* pBC_l = pContextBO_p->getBalanceCost(idxBC_l);
        oss_l << endl
            << pBC_l->getRessource1()->getId() << " "
            << pBC_l->getRessource2()->getId() << " "
            << pBC_l->getTarget() << endl
            << pBC_l->getPoids() << endl;
    }

    return oss_l.str();
}

string InstanceWriterDtoout::writePoids(ContextBO const * pContextBO_p){
    ostringstream oss_l;
    oss_l << pContextBO_p->getPoidsPMC() << endl
        << pContextBO_p->getPoidsSMC() << endl
        << pContextBO_p->getPoidsMMC() << endl;
    return oss_l.str();
}
