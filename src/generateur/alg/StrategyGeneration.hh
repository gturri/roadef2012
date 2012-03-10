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

#ifndef STRATEGYGENERATION_HH
#define STRATEGYGENERATION_HH
#include <list>
#include <boost/program_options.hpp>
#include <boost/shared_ptr.hpp>
using namespace std;
using namespace boost;
using namespace boost::program_options;

class ContextBO;

class StrategyGeneration {
    public:
        virtual ~StrategyGeneration() = 0;

        /**
         * Methode de generation d'instance.
         * @param arg_p Les arguments fournis au binaire (via la ligne de commande)
         *  afin de permettre a chaque classe concrete de solliciter ces propres arguments
         * @return la liste des instances generees, sous forme d'une liste de ContextBO
         * Il suffit ensuite de fournir ces ContextBO a un writer pour generer les fichiers souhaites
         * (Les perfs n'etant pas cruciales sur ce binaire, on en se prive pas d'utiliser des smart pointers)
         */
        virtual list<shared_ptr<ContextBO> > generate(const variables_map& arg_p) = 0;
};

#endif
