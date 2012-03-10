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

#ifndef SERVICEBO_HH
#define SERVICEBO_HH
#include <tr1/unordered_set>
#include <tr1/unordered_map>
using namespace std::tr1;

class ProcessBO;
class NeighborhoodBO;

class ServiceBO {
    public:
        ServiceBO(int id_p, int spreadMin_p, const unordered_set<int>& sDependances_p);

        int getId() const;
        int getSpreadMin() const;

        /**
         * Retourne le nombre de services dont "this" depend
         */
        int getNbServicesIDependOn() const;

        /**
         * Indique si "this" depend du service d'indice donne
         */
        bool iDependOn(int idxService_p) const;

        unordered_set<int> getServicesIDependOn() const;

        void addProcess(ProcessBO* pProcess_p);
        int getNbProcesses() const;
        bool containsProcess(int idxProcess_p) const;
        unordered_set<int> getProcesses() const;

        bool operator==(const ServiceBO& service_p) const;
        bool operator!=(const ServiceBO& service_p) const;


    private:
        const int id_m;

        /**
         * Liste des indices de processes appartenant au service
         */
        unordered_set<int> sProcess_m;

        /**
         * Nombre minimum de locations sur lesquels les processes du services
         * doivent etre deployes
         */
        const int spreadMin_m;

        /**
         * Contient les indices des services dont "this" depend
         */
        const unordered_set<int> sIDependOnThem_m;
};


#endif
