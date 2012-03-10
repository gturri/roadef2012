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

#ifndef STRATEGYOPTIM_HH
#define STRATEGYOPTIM_HH
#include "alg/ContextALG.hh"
#include <boost/program_options.hpp>
#include <ctime>
using namespace boost::program_options;


/**
 * Interface dont derive toutes les methodes d'optims,
 * afin de simplifier la manipulation de celles-ci
 *
 * Une implémentation de cette classe peut representer, conceptuellement :
 * - une strategie simple strategie d'optim (eg : pl, recherche locale, ...)
 * - une sequence d'optim enchaine strategies simples et/ou sous sequences
 */
class StrategyOptim {
    public:
        virtual ~StrategyOptim();

        /**
         * Effectue une optim en partant d'une solution initiale,
         * se charge d'ecrire la meilleure solution trouvee via le SolutionDtoout,
         * et renvoie la solution "finale" voulu
         * @param contextAlg_p La solution initiale
         * @param heureFinMaxPreconisee La date de fin a laquelle la strategie devrait retourner au plus tard. La strategie est toutefois libre de respecter ou non cette indication
         * @param opt_p Les options founies a la ligne de commande, afin de permettre aux Strategie de lire leurs propres arguments
         * @return Une solution "finale". Il peut s'agir de la meilleure solution trouvee,
         * de l'etat final, d'autre chose...
         */
        virtual ContextALG run(ContextALG contextAlg_p, time_t heureFinMaxPreconisee_p, const variables_map& opt_p) = 0;
};

#endif
