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

#ifndef CONTEXTALG_HH
#define CONTEXTALG_HH
#include <vector>
#include <tr1/unordered_set>
#include <stdint.h>
using namespace std;
using namespace std::tr1;

class ContextBO;
class ServiceBO;

class ContextALG {
    public:
        /**
         * @param Le ContextBO qui decrit l'instance traitee par ce ContextALG
         * @param Doit-on ecrire une sol des qu'une meilleure sol est trouvee ?
         * (si ce ContextALG decrit un sous pb, cette variable doit etre FALSE !)
         * @param Doit-on checker la sol init fournie par le ContextBO ?
         */
        ContextALG(ContextBO const * pContextBO_p, bool mustWriteBestSol_p=true, bool solInitToCheck_p=false);
        ContextBO const * getContextBO() const;

        /* TODO : ecrire des tests pour ces methodes
         * TODO : ajouter un cache pour ces methodes (et gestion de son invalidation lors de la modif de la sol) (ou pas, si c'est au detriment des perfs et qu'il vaut mieux que les classes clientes le gere...)
         */
        unordered_set<int> getNeighsUsedByService(int idxService_p) const;
        unordered_set<int> getNeighsUsedByService(ServiceBO const * pService_p) const;

        /* TODO : tester cette methode */
        /* TODO : ameliorer les perfs de cette methode par exemple en calculant
         * tous les resultats, et en gerant un cache...
         */
        /**
         * Retourne la quantite de ressource consomme par les process d'une machine donnee
         */
        int getRessUsedOnMachine(int idxRess_p, int idxMachine_p) const;

        void setMustWriteBestSol(bool mustWriteBestSol_p);

        const vector<int>& getCurrentSol() const;
        void setCurrentSol(const vector<int>& curSol_p);

        /**
         * Evalue "from scratch" la solution soumise, et la memorise s'il s'agit de la meilleure
         * Attention : methode lente a cause de l'evaluation
         * @param La solution a evaluer
         * @param FALSE si on peut supposer que la validite est ok, TRUE s'il faut la verifier
         * @return TRUE si une maj a ete effectuee
         */
        bool checkCompletAndMajBestSol(const vector<int>& candidatBestSol_p, bool checkValidite_p);

        const vector<int>& getBestSol() const;
        uint64_t getScoreBestSol() const;

    private:
        /**
         * Represente l'instance en cours.
         * Plusieurs ContextALG peuvent partager le meme ContextBO,
         * donc il va appartenir aux classes clients de gerer le delete du ContextBO
         * De meme, cet attribut ne justifie ni un operator= ni un cpy ctr customise
         */
        ContextBO const * pContextBO_m;

        /**
         * vecteur de taille nbProcesses representant la solution actuelle
         * currentSol_m[idxProcess] = idxMachine sur laquelle il est affecte
         */
        vector<int> currentSol_m;

        /**
         * Quand une meilleure sol est trouvee, celle-ci est aussitot ecrite.
         * Ce comportement n'est pas souhaitable lorsque l'on travaille sur un sous-contexte
         * Cette attribut permet de piloter ce comportement
         */
        bool mustWriteBestSol_m;
};

#endif
