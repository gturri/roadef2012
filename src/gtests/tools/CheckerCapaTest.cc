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

#include "alg/ContextALG.hh"
#include "bo/ContextBO.hh"
#include "bo/RessourceBO.hh"
#include "bo/ServiceBO.hh"
#include "gtests/ContextBOBuilder.hh"
#include "tools/Checker.hh"
#include <vector>
#include <tr1/unordered_set>
#include <gtest/gtest.h>
using namespace std;
using namespace std::tr1;

TEST(Checker, checkCapaNotTransient){
    ContextBO contextBO_l;
    contextBO_l.addRessource(new RessourceBO(0, false, 0));

    ContextBOBuilder::buildMachine(0, 0, 0, vector<int>(1, 15), vector<int>(1, 10), &contextBO_l);
    ContextBOBuilder::buildMachine(1, 0, 0, vector<int>(1, 20), vector<int>(1, 10), &contextBO_l);

    ServiceBO* pService_l = ContextBOBuilder::buildService(0, 0, unordered_set<int>(), &contextBO_l);
    ContextBOBuilder::buildProcess(0, pService_l, vector<int>(1, 14), 0, 0, &contextBO_l);
    ContextBOBuilder::buildProcess(1, pService_l, vector<int>(1, 4), 0, 1, &contextBO_l);
    ContextBOBuilder::buildDefaultMMC(&contextBO_l);

    ContextALG contextALG_l(&contextBO_l);
    Checker checker_l(&contextALG_l);
    EXPECT_TRUE(checker_l.checkCapaIncludingTransient());

    contextALG_l.setCurrentSol(vector<int>(2, 0));
    EXPECT_FALSE(checker_l.checkCapaIncludingTransient());

    contextALG_l.setCurrentSol(vector<int>(2, 1));
    EXPECT_TRUE(checker_l.checkCapaIncludingTransient());

    vector<int> curSol_l(2, 0);
    curSol_l[0] = 1;
    contextALG_l.setCurrentSol(curSol_l);
    EXPECT_TRUE(checker_l.checkCapaIncludingTransient());
}

TEST(Checker, checkCapaTransient){
    ContextBO contextBO_l;
    contextBO_l.addRessource(new RessourceBO(0, true, 0));

    ContextBOBuilder::buildMachine(0, 0, 0, vector<int>(1, 15), vector<int>(1, 10), &contextBO_l);
    ContextBOBuilder::buildMachine(1, 0, 0, vector<int>(1, 20), vector<int>(1, 10), &contextBO_l);

    ServiceBO* pService_l = new ServiceBO(0, 0, unordered_set<int>());
    contextBO_l.addService(pService_l);
    ContextBOBuilder::ContextBOBuilder::buildProcess(0, pService_l, vector<int>(1, 14), 0, 0, &contextBO_l);
    ContextBOBuilder::buildProcess(1, pService_l, vector<int>(1, 4), 0, 1, &contextBO_l);
    ContextBOBuilder::buildDefaultMMC(&contextBO_l);

    ContextALG contextALG_l(&contextBO_l);
    Checker checker_l(&contextALG_l);
    EXPECT_TRUE(checker_l.checkCapaIncludingTransient());

    contextALG_l.setCurrentSol(vector<int>(2, 0));
    EXPECT_FALSE(checker_l.checkCapaIncludingTransient());

    contextALG_l.setCurrentSol(vector<int>(2, 1));
    EXPECT_TRUE(checker_l.checkCapaIncludingTransient());

    vector<int> curSol_l(2, 0);
    curSol_l[0] = 1;
    contextALG_l.setCurrentSol(curSol_l);
    EXPECT_FALSE(checker_l.checkCapaIncludingTransient());
}
