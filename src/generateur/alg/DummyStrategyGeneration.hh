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

#ifndef DUMMYSTRATEGYGENERATION_HH
#define DUMMYSTRATEGYGENERATION_HH
#include "generateur/alg/StrategyGeneration.hh"

/**
 * Genere une instance ultra minimaliste, dans le seul but de voir si le generateur tourne
 */

class DummyStrategyGeneration : public StrategyGeneration {
    public:
        virtual list<shared_ptr<ContextBO> > generate(const variables_map& arg_p);

        void buildRessources(shared_ptr<ContextBO> pContextBO_p);
        void buildMachines(shared_ptr<ContextBO> pContextBO_p);
        void buildMMC(shared_ptr<ContextBO> pContextBO_p);
        void buildServices(shared_ptr<ContextBO> pContextBO_p);
        void buildProcesses(shared_ptr<ContextBO> pContextBO_p);
        void buildBalanceCosts(shared_ptr<ContextBO> pContextBO_p);
        void buildPoids(shared_ptr<ContextBO> pContextBO_p);
};

#endif
