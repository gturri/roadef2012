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

#include "generateur/alg/GenerateFromExisting.hh"
#include "dtoin/InstanceReaderInterface.hh"
#include "dtoin/InstanceReaderDtoin.hh"
#include "dtoin/InstanceReaderHumanReadable.hh"
#include "dtoin/SolutionDtoin.hh"
#include "tools/Log.hh"
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

list<shared_ptr<ContextBO> > GenerateFromExisting::generate(const variables_map& args_p){
    shared_ptr<InstanceReaderInterface> pReader_l = getReader(args_p);
    string inFilename_l = args_p["fromExistingInst"].as<string>();
    list<shared_ptr<ContextBO> > result_l;
    ContextBO contextInit_l = pReader_l->read(inFilename_l);

    if ( ! args_p.count("fromExistingSol") ){
        ostringstream oss_l;
        oss_l << "Strategie de generation demandee : \"From existing\", mais pas de solution initiale fourni. Utiliser l'option --fromExistingSol nomFichier" << endl;
        throw oss_l.str();
    }

    SolutionDtoin::read(args_p["fromExistingSol"].as<string>(), &contextInit_l);

    result_l.push_back(shared_ptr<ContextBO>(new ContextBO(contextInit_l)));
    return result_l;
}

shared_ptr<InstanceReaderInterface> GenerateFromExisting::getReader(const variables_map& args_p){
    if ( ! args_p.count("fromExistingInst") ){
        ostringstream oss_l;
        oss_l << "Strategie de generation demandee : \"From existing\", mais pas d'instance initiale fournie. Utiliser l'option --fromExistingInst nomFichier" << endl;
        throw oss_l.str();
    }

    string filename_l = args_p["fromExistingInst"].as<string>();
    ifstream ifs_l(filename_l.c_str());
    if ( ! ifs_l ){
        ostringstream oss_l;
        oss_l << "Impossible d'ouvir le fichier d'instance " << filename_l <<endl;
        throw oss_l.str();
    }

    shared_ptr<InstanceReaderInterface> result_l;

    char firstChar_l;
    ifs_l >> firstChar_l;
    if ( firstChar_l == '=' ){
        //LOG(DEBUG) << "Reader choisi : human readable" << endl;
        result_l = shared_ptr<InstanceReaderInterface>(new InstanceReaderHumanReadable);
    } else {
        //LOG(DEBUG) << "Reader choisi : par defaut" << endl;
        result_l = shared_ptr<InstanceReaderInterface>(new InstanceReaderDtoin);
    }

    return result_l;
}
