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

#ifndef MACHINEDTOIN_HH
#define MACHINEDTOIN_HH
#include <iostream>
#include <vector>
using namespace std;

class ContextBO;
class LocationBO;
class NeighborhoodBO;
class RessourceBO;

/**
 * Classe en charge de la lecture de la partie Machine du fichier d'instance.
 * Cette classe ne devrait pas etre appellee directement : l'#InstanceReaderDtoin se charge de la manipuler
 *
 * A l'attention de ceux qui s'interessent au package dtoin (cad peu de monde : cf remarque ci dessus)
 * Attention : c'est une classe jetable : on l'instancie, on appelle read une fois, et puis c'est tout.
 * Une instance n'est pas faite pour etre utilisable deux fois (parce que semantiquement ca n'a pas de sens, et parce que c'est plus simple de l'implanter ainsi)
 */
class MachineDtoin{
    public:
        MachineDtoin();

        /**
         * @param is_p Le flux a lire
         * @param pContextBO_p Le context a peupler
         */
        void read(istream& is_p, ContextBO* pContextBO_p);

    private:
        vector<int> readQteRess(istream& is_p);
        void readMMCForOneMachine(istream& is_p, int idxCurMachine_p);

        void sendMMC() const;
        void sendLocations() const;
        void sendNeighborhoods() const;

        /**
         * Si la location demandee n'existe pas, elle est creee a la volee
         */
        LocationBO* getLocation(int idx_p);

        /**
         * Si le neighborhood n'existe pas, il est cree a la volee
         */
        NeighborhoodBO* getNeighborhood(int idx_p);

        vector<LocationBO*> pLoc_m;
        vector<NeighborhoodBO*> pNeigh_m;
        ContextBO* pContext_m;
        
        vector<vector<int> > mmcCosts_m;


        bool alreadyUsed_m;
};

#endif
