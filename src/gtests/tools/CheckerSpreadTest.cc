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
#include "gtests/ContextBOBuilder.hh"
#include "tools/Checker.hh"
#include <gtest/gtest.h>

TEST(Checker, checkSpread){
    ContextBO contextBO_l;

    ContextBOBuilder::buildMachine(0, 0, 0, vector<int>(), vector<int>(), &contextBO_l);
    ContextBOBuilder::buildMachine(1, 1, 0, vector<int>(), vector<int>(), &contextBO_l);
    ContextBOBuilder::buildMachine(2, 1, 0, vector<int>(), vector<int>(), &contextBO_l);
    ContextBOBuilder::buildMachine(3, 1, 0, vector<int>(), vector<int>(), &contextBO_l);

    ServiceBO* pService0_l = ContextBOBuilder::buildService(0, 2, unordered_set<int>(), &contextBO_l);
    ServiceBO* pService1_l = ContextBOBuilder::buildService(1, 1, unordered_set<int>(), &contextBO_l);
    ContextBOBuilder::buildProcess(0, pService0_l, vector<int>(), 0, 0, &contextBO_l);
    ContextBOBuilder::buildProcess(1, pService0_l, vector<int>(), 0, 1, &contextBO_l);
    ContextBOBuilder::buildProcess(2, pService0_l, vector<int>(), 0, 2, &contextBO_l);
    ContextBOBuilder::buildProcess(3, pService1_l, vector<int>(), 0, 0, &contextBO_l);
    ContextBOBuilder::buildDefaultMMC(&contextBO_l);

    ContextALG contextALG_l(&contextBO_l);
    Checker checker_l(&contextALG_l);
    EXPECT_TRUE(checker_l.checkSpread());

    vector<int> curSol_l = contextALG_l.getCurrentSol();
    curSol_l[0]=1 ; curSol_l[1]=2 ; curSol_l[2]=3 ; curSol_l[3]=0;
    contextALG_l.setCurrentSol(curSol_l);
    EXPECT_FALSE(checker_l.checkSpread());
}
