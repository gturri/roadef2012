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

#ifndef MACHINEBO_HH
#define MACHINEBO_HH
#include <vector>
using namespace std;

class LocationBO;
class NeighborhoodBO;
class RessourceBO;

class MachineBO {
    public:
        MachineBO(int id_p, LocationBO* location_p, NeighborhoodBO* neighborhood_p, const vector<int>& capa_p, const vector<int> safetyCapa_p);
        bool operator==(MachineBO& machine_p) const;
        bool operator!=(MachineBO& machine_p) const;

        int getId() const;
        LocationBO* getLocation() const;
        NeighborhoodBO* getNeighborhood() const;
        int getCapa(int idxRess_p) const;
        int getCapa(RessourceBO const * pRess_p) const;
        vector<int> getCapas() const;
        int getSafetyCapa(int idxRess_p) const;
        vector<int> getSafetyCapas() const;

    private:
        int id_m;
        LocationBO* const location_m;
        NeighborhoodBO* const neighborhood_m;

        /**
         * capa_m[idxRess] = capacite de la machine par rapport a cette ressource
         */
        const vector<int> capa_m;

        /**
         * safetyCapa_m[idxRess] = capacite de securite de la machine par rapport a cette ressource
         */
        const vector<int> safetyCapa_m;
};

#endif
