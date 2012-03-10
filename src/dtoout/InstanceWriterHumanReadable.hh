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
