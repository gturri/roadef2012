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

#include "dtoin/InstanceReaderHumanReadable.hh"
#include "bo/BalanceCostBO.hh"
#include "bo/LocationBO.hh"
#include "bo/MachineBO.hh"
#include "bo/MMCBO.hh"
#include "bo/NeighborhoodBO.hh"
#include "bo/ProcessBO.hh"
#include "bo/RessourceBO.hh"
#include "bo/ServiceBO.hh"
#include "tools/Log.hh"
#include <algorithm>
#include <fstream>
#include <vector>
#include <sstream>
#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>
#include <boost/regex.hpp>
#include <boost/tuple/tuple.hpp>
using namespace std;
using namespace boost;

string InstanceReaderHumanReadable::getNextLine(istream& is_p){
    string result_l;
    string copieTrimned_l;
    while ( copieTrimned_l == "" && is_p ){
        getline(is_p, result_l);
        copieTrimned_l = string(result_l);
        trim(copieTrimned_l);
    }
    return result_l;
}

string InstanceReaderHumanReadable::readSectionTitle(const string& ligne_p){
    /* On demande juste au moins 4 'egal' a la fin, car ca coute pas plus cher,
     * et ca permet d'eviter a ceux qui editeront a la main de buter sur ce genre d'erreur
     */
    const static regex regex_l(" *={5} *([[:alpha:]]*) *={4,} *");
    smatch match_l;
    if ( ! regex_match(ligne_p, match_l, regex_l ) ){
        ostringstream oss_l;
        oss_l << "La ligne \"" << ligne_p << "\" ne correspond pas a un titre";
        throw oss_l.str();
    }

    return match_l[1];
}

void InstanceReaderHumanReadable::checkSectionTitle(const string& ligne_p, const string& expectedTitle_p){
    string actualTitle_l(readSectionTitle(ligne_p));
    if ( ! areEqualCaseInsensitive(actualTitle_l, expectedTitle_p) ){
        ostringstream oss_l;
        oss_l << ligne_p << " lue, mais titre de section " << expectedTitle_p << " attendu";
        throw oss_l.str();
    }
}

bool InstanceReaderHumanReadable::areEqualCaseInsensitive(const string& s1_p, const string& s2_p){
    return !(ilexicographical_compare(s1_p, s2_p) || ilexicographical_compare(s2_p, s1_p));
}

vector<int> InstanceReaderHumanReadable::readListe(const string& ligne_p, const string& typeListe_p){
    const static regex regex_l(" *\\* *([[:alpha:]]*) *:(( +[[:digit:]]*)*) *");
    smatch match_l;
    if ( ! regex_match(ligne_p, match_l, regex_l) ){
        ostringstream oss_l;
        oss_l << "La ligne \"" << ligne_p << "\" ne correspond pas a une liste";
        throw oss_l.str();
    }

    if ( ! areEqualCaseInsensitive(typeListe_p, match_l[1]) ){
        ostringstream oss_l;
        oss_l << "La ligne \"" << ligne_p << "\" correspond a une liste de type " << match_l[1] <<", alors qu'une liste de type " << typeListe_p << " est attendue";
        throw oss_l.str();
    }

    vector<int> result_l;
    istringstream iss_l(match_l[2]);
    while ( iss_l ){
        int valo_l;
        iss_l >> valo_l;
        if ( iss_l ){
            result_l.push_back(valo_l);
        }
    }
    return result_l;
}

int InstanceReaderHumanReadable::readQuantite(const string& ligne_p){
    const static regex regex_l(" *quantite *: *([[:digit:]]+) *");
    smatch match_l;
    if ( ! regex_match(ligne_p, match_l, regex_l) ){
        ostringstream oss_l;
        oss_l << "La ligne \"" << ligne_p << "\" ne correspond pas a une quantite";
        throw oss_l.str();
    }

    istringstream iss_l(match_l[1]);
    int result_l;
    iss_l >> result_l;
    return result_l;
}

void InstanceReaderHumanReadable::checkSubTitle(const string& ligne_p, const string& subTitle_p, int idx_p, int total_p){
    const static regex regex_l(" *={4} *([[:alpha:]]*) *([[:digit:]]*) */ *([[:digit:]]*) *={3,} *");
    smatch match_l;
    if ( ! regex_match(ligne_p, match_l, regex_l) ){
        ostringstream oss_l;
        oss_l << "La ligne \"" << ligne_p << "\" ne correspond pas a un sous titre";
        throw oss_l.str();
    }

    if ( !areEqualCaseInsensitive(subTitle_p, match_l[1]) ){
        ostringstream oss_l;
        oss_l << "La ligne \"" << ligne_p << "\" correspond au sous titre " << match_l[1] << ", alors que " << subTitle_p << " est attendu";
        throw oss_l.str();
    }

    int idx_l, total_l;
    {
        istringstream iss_l(match_l[2]);
        iss_l >> idx_l;
    }
    {
        istringstream iss_l(match_l[3]);
        iss_l >> total_l;
    }

    if ( idx_l != idx_p ){
        ostringstream oss_l;
        oss_l << "La ligne \"" << ligne_p << "\" correspond a l'item " << idx_l << " alors que l'item " << idx_p << " est attendu";
        throw oss_l.str();
    }

    if ( total_l != total_p ){
        ostringstream oss_l;
        oss_l << "La ligne \"" << ligne_p << "\" indique un total de " << total_l << " item alors que " << total_p << " items sont attendus";
        throw oss_l.str();

    }
}

int InstanceReaderHumanReadable::readCarac(const string& ligne_p, const string& typeCarac_p){
    const static regex regex_l(" *\\* *([[:alpha:]]*) *: *([[:digit:]]+) *");
    smatch match_l;
    if ( ! regex_match(ligne_p, match_l, regex_l) ){
        ostringstream oss_l;
        oss_l << "La ligne \"" << ligne_p << "\" ne correspond pas a une carac";
        throw oss_l.str();
    }

    if ( !areEqualCaseInsensitive(typeCarac_p, match_l[1]) ){
        ostringstream oss_l;
        oss_l << "La ligne \"" << ligne_p << "\" correspond a la carac " << match_l[1] << " ; carac " << typeCarac_p << " attendue";
        throw oss_l.str();
    }

    istringstream iss_l(match_l[2]);
    int result_l;
    iss_l >> result_l;
    return result_l;
}

void InstanceReaderHumanReadable::readRessources(istream& is_p, ContextBO* pContextBO_p){
    checkSectionTitle(getNextLine(is_p), "Ressources");
    int nbRess_l = readQuantite(getNextLine(is_p));
    LOG(DEBUG) << "Debut de la lecture de " << nbRess_l << " ressources" << endl;

    for ( int idxRess_l=0 ; idxRess_l < nbRess_l ; idxRess_l ++ ){
        LOG(USELESS) << "\tLecture de la ressource " << idxRess_l << endl;
        checkSubTitle(getNextLine(is_p), "Ressource", idxRess_l, nbRess_l);
        bool isTransient_l = readCarac(getNextLine(is_p), "isTransient");
        int poids_l = readCarac(getNextLine(is_p), "weightLoadCost");
        pContextBO_p->addRessource(new RessourceBO(idxRess_l, isTransient_l, poids_l));
    }
}

void InstanceReaderHumanReadable::readMachines(istream& is_p, ContextBO* pContextBO_p){
    checkSectionTitle(getNextLine(is_p), "Machines");
    int nbMachines_l = readQuantite(getNextLine(is_p));
    LOG(DEBUG) << "Debut de la lecture de " << nbMachines_l << " machines" << endl;

    //1ere passe pour recuperer la totalite des data
    vector<tuple<int, int, int, vector<int>, vector<int> > > vDatas_l;
    int nbNeigh_l(0), nbLoc_l(0);
    vector<vector<int> > vMmcData_l;
    for ( int idxMachine_l=0 ; idxMachine_l < nbMachines_l ; idxMachine_l++ ){
        LOG(USELESS) << "\tLecture de la machine " << idxMachine_l << endl;
        checkSubTitle(getNextLine(is_p), "Machine", idxMachine_l, nbMachines_l);
        int idxNeigh_l = readCarac(getNextLine(is_p), "Neighborhood");
        nbNeigh_l = max(nbNeigh_l, idxNeigh_l);
        int idxLoc_l = readCarac(getNextLine(is_p), "Location");
        nbLoc_l = max(nbLoc_l, idxLoc_l);
        vector<int> vCapas_l = readListe(getNextLine(is_p), "Capa");
        vector<int> vSafetyCapas_l = readListe(getNextLine(is_p), "SafetyCapa");
        vMmcData_l.push_back(readListe(getNextLine(is_p), "MMC"));

        if ( (int) vMmcData_l.back().size() != nbMachines_l ){
            ostringstream oss_l;
            oss_l << "La machine " << idxMachine_l << " decrit " << vMmcData_l.back().size()
                << " mmc, alors que qu'il y a " << nbMachines_l;
            throw oss_l.str();
        }

        vDatas_l.push_back(make_tuple(idxMachine_l, idxNeigh_l, idxLoc_l, vCapas_l, vSafetyCapas_l));
    }

    //2nde passe pour instancier les objets
    LOG(DEBUG) << "Creation de " << nbNeigh_l + 1 << " neighborhoods et " << nbLoc_l + 1 << " locations" << endl;
    for(int idxNeigh_l=0 ; idxNeigh_l <= nbNeigh_l ; idxNeigh_l++ ){
        LOG(USELESS) << "\tCreation du neighborhood " << idxNeigh_l << endl;
        pContextBO_p->addNeighborhood(new NeighborhoodBO(idxNeigh_l));
    }
    for(int idxLoc_l=0 ; idxLoc_l <= nbLoc_l ; idxLoc_l++ ){
        LOG(USELESS) << "\tCreation de la location " << idxLoc_l << endl;
        pContextBO_p->addLocation(new LocationBO(idxLoc_l));
    }
    for ( vector<tuple<int, int, int, vector<int>, vector<int> > >::iterator it_l=vDatas_l.begin() ; it_l != vDatas_l.end() ; it_l++){
        NeighborhoodBO* pNeigh_l = pContextBO_p->getNeighborhood(get<1>(*it_l));
        LocationBO* pLoc_l = pContextBO_p->getLocation(get<2>(*it_l));
        pContextBO_p->addMachine(new MachineBO(get<0>(*it_l), pLoc_l, pNeigh_l, get<3>(*it_l), get<4>(*it_l)));
    }

    pContextBO_p->setMMCBO(new MMCBO(vMmcData_l));
}

void InstanceReaderHumanReadable::readServices(istream& is_p, ContextBO* pContextBO_p){
    checkSectionTitle(getNextLine(is_p), "Services");
    int nbServices_l = readQuantite(getNextLine(is_p));
    LOG(DEBUG) << "Debut de la lecture de " << nbServices_l << " services" << endl;

    for ( int idxS_l=0 ; idxS_l < nbServices_l ; idxS_l++ ){
        LOG(USELESS) << "\tLecture du service " << idxS_l << endl;
        checkSubTitle(getNextLine(is_p), "Service", idxS_l, nbServices_l);
        int spreadMin_l = readCarac(getNextLine(is_p), "SpreadMin");
        vector<int> vDependances_l = readListe(getNextLine(is_p), "Dependances");
        unordered_set<int> sDependances_l(vDependances_l.begin(), vDependances_l.end());
        pContextBO_p->addService(new ServiceBO(idxS_l, spreadMin_l, sDependances_l));
    }
}

void InstanceReaderHumanReadable::readProcesses(istream& is_p, ContextBO* pContextBO_p){
    checkSectionTitle(getNextLine(is_p), "Processes");
    int nbProcesses_l = readQuantite(getNextLine(is_p));
    LOG(DEBUG) << "Debut de la lecture de " << nbProcesses_l << " processes" << endl;

    for ( int idxP_l=0 ; idxP_l < nbProcesses_l ; idxP_l++ ){
        LOG(USELESS) << "\tLecture du service " << idxP_l << endl;
        checkSubTitle(getNextLine(is_p), "Process", idxP_l, nbProcesses_l);
        int idxService_l = readCarac(getNextLine(is_p), "Service");
        vector<int> vRequirements_l = readListe(getNextLine(is_p), "RessourcesRequises");
        int pmc_l = readCarac(getNextLine(is_p), "PMC");
        if ( idxService_l >= pContextBO_p->getNbServices() ){
            ostringstream oss_l;
            oss_l << "Le process " << idxP_l << " appartient au service " << idxService_l << " mais seulement " << pContextBO_p->getNbServices() << " ont ete crees";
            throw oss_l.str();
        }
        ServiceBO* pService_l = pContextBO_p->getService(idxService_l);
        pContextBO_p->addProcess(new ProcessBO(idxP_l, pService_l, vRequirements_l, pmc_l));
    }
}

void InstanceReaderHumanReadable::readBalanceCosts(istream& is_p, ContextBO* pContextBO_p){
    //TODO
    checkSectionTitle(getNextLine(is_p), "BalanceCosts");
    int nbBC_l = readQuantite(getNextLine(is_p));
    int nbRess_l = pContextBO_p->getNbRessources();
    LOG(DEBUG) << "Debut de la lecture de " << nbBC_l << " balance costs" << endl;

    for ( int idxBC_l=0 ; idxBC_l < nbBC_l ; idxBC_l++ ){
        LOG(USELESS) << "\tLecture de balance cost " << idxBC_l << endl;
        checkSubTitle(getNextLine(is_p), "BalanceCost", idxBC_l, nbBC_l);
        int idxRess1_l = readCarac(getNextLine(is_p), "Ress1");
        int idxRess2_l = readCarac(getNextLine(is_p), "Ress2");
        int target_l = readCarac(getNextLine(is_p), "Target");
        int poids_l = readCarac(getNextLine(is_p), "Poids");

        if ( idxRess1_l >= nbRess_l || idxRess2_l >= nbRess_l ){
            ostringstream oss_l;
            oss_l << "Le balance cost " << idxBC_l << " fait intervenir les ressources " << idxRess1_l << " et " << idxRess2_l <<", mais seules " << nbRess_l << " Ressources sont definies";
            throw oss_l.str();
        }
        RessourceBO* pRess1_l = pContextBO_p->getRessource(idxRess1_l);
        RessourceBO* pRess2_l = pContextBO_p->getRessource(idxRess2_l);
        pContextBO_p->addBalanceCost(new BalanceCostBO(pRess1_l, pRess2_l, target_l, poids_l));
    }
}

void InstanceReaderHumanReadable::readPoids(istream& is_p, ContextBO* pContextBO_p){
    checkSectionTitle(getNextLine(is_p), "Poids");
    pContextBO_p->setPoidsPMC(readCarac(getNextLine(is_p), "PMC"));
    pContextBO_p->setPoidsSMC(readCarac(getNextLine(is_p), "SMC"));
    pContextBO_p->setPoidsMMC(readCarac(getNextLine(is_p), "MMC"));
}

ContextBO InstanceReaderHumanReadable::read(const string& instance_filename_p){
    ifstream ifs_l(instance_filename_p.c_str());
    if ( ! ifs_l ){
        ostringstream oss_l;
        oss_l << "Impossible d'ouvrir le fichier d'instance " << instance_filename_p;
        throw oss_l.str();
    }

    ContextBO result_l;
    getNextLine(ifs_l); //Sauter la premiere ligne
    readRessources(ifs_l, &result_l);
    readMachines(ifs_l, &result_l);
    readServices(ifs_l, &result_l);
    readProcesses(ifs_l, &result_l);
    readBalanceCosts(ifs_l, &result_l);
    readPoids(ifs_l, &result_l);

    string lastLine_l(getNextLine(ifs_l));
    if ( lastLine_l != "" ){
        ostringstream oss_l;
        oss_l << "Presence d'au moins une ligne en trop a la fin du fichier " << instance_filename_p << " : \"" << lastLine_l << "\"";
        throw oss_l.str();
    }

    return result_l;
}
