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

#ifndef CHECKER_HH
#define CHECKER_HH
#include <vector>
#include <stdint.h>
using namespace std;


class ContextALG;
class ContextBO;
class MachineBO;
class RessourceBO;

/**
 * Fonctions s'appuyant sur la classe #Checker, permettant de s'evitant la creation d'instances temporaires
 */
bool check(ContextALG const * pContextALG_p);
bool check(ContextBO const * pContextBO_p);

class Checker {
    public:
        Checker(ContextALG const * pContextALG_p);

        Checker(ContextBO const * pContextBO_p, const vector<int>& sol_p);

        /**
         * /!\ Ne pas utiliser /!\
         * Defini uniquement afin d'eviter d'en avoir une implantation par defaut.
         * (afin d'eviter d'avoir a perdre du cpu a gerer a vouloir eviter les
         * double delete et/ou fuites, alors qu'on n'a de toute facon pas besoin de ce ctr
         */
        Checker(const Checker& checker_p);

        ~Checker();

        void setContextALG(ContextALG const * pContextALG_p);

        bool isValid();

        /**
         * Calcule le score en supposant que l'instance est valide.
         * Dans le cas contrainte, le comportement est indetermine
         */
        uint64_t computeScore();

        /**
         * Methodes permettant de ne checker que quelques contraintes
         */
        bool checkCapaIncludingTransient();
        bool checkConflict();
        bool checkSpread();
        bool checkDependances();
        
        /**
         * Methodes permettant de ne calculer que certains couts
         */
        uint64_t computeLoadCost();
        uint64_t computeLoadCost(int idxRess_p);
        uint64_t computeLoadCost(int idxRess_p, int idxMachine_p);

        uint64_t computeBalanceCost();
        uint64_t computeBalanceCost(int idxMachine_p);
        uint64_t computeBalanceCost(int idxMachine_p, int idxBalanceCost_p);

        uint64_t computePMC();
        uint64_t computeSMC();
        uint64_t computeMMC();

    private:
        bool checkCapaIncludingTransient(RessourceBO const * pRess_p);

        /**
         * Permet de construire un ContextALG customise, et const
         */
        ContextALG const * buildMyContextALG(ContextBO const * pContextBO, const vector<int> sol_p);

        /**
         * Le const permet surtout a la classe cliente de s'assurer qu'on ne pourri
         * pas son contexte. Ceci dit, si le client peut eventuellement la modifier
         * donc attention : il n'est pas possible de cacher quoique se soit !
         */
        ContextALG const * pContextALG_m;

        /**
         * Si le context a ete cree sur mesure par le checker, il faut le deleter nous meme
         */
        bool contextToDelete_m;

};

#endif
