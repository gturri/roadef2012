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

#include "dtoin/SolutionDtoin.hh"
#include "bo/ContextBO.hh"
#include "bo/ProcessBO.hh"
#include "tools/Log.hh"
#include <fstream>
#include <sstream>

void SolutionDtoin::read(const string& solFileName_p, ContextBO* pContextBO_p){
    ifstream ifs_l(solFileName_p.c_str());
    if ( ! ifs_l ){
        ostringstream oss_l;
        oss_l << "Impossible d'ouvrir le fichier de solution a lire " << solFileName_p << endl;
        throw oss_l.str();
    }
    read(ifs_l, pContextBO_p);
}

void SolutionDtoin::read(istream& is_p, ContextBO* pContextBO_p){
    int nbProcesses_l = pContextBO_p->getNbProcesses();
    for ( int idxP_l=0 ; idxP_l < nbProcesses_l ; idxP_l++ ){
        int idxMachine_l;
        is_p >> idxMachine_l;
        MachineBO* pMachine_l = pContextBO_p->getMachine(idxMachine_l);
        pContextBO_p->getProcess(idxP_l)->setMachineInit(pMachine_l);
    }
    LOG(INFO) << "Fin de la lecture du fichier de solution initiale" << endl;
}
