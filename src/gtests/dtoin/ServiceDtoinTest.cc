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

#include "bo/ContextBO.hh"
#include "bo/ServiceBO.hh"
#include "gtests/dtoin/TestDtoinHelper.hh"
#include <gtest/gtest.h>

TEST(dtoin, ServiceDtoin){
    ContextBO context_l;
    TestDtoinHelper::loadTestDataService(&context_l);

    ASSERT_EQ(context_l.getNbServices(), 2);

    EXPECT_EQ(context_l.getService(0)->getId(), 0);
    EXPECT_EQ(context_l.getService(0)->getSpreadMin(), 2);
    EXPECT_EQ(context_l.getService(0)->getNbServicesIDependOn(), 0);
    EXPECT_FALSE(context_l.getService(0)->iDependOn(0));
    EXPECT_FALSE(context_l.getService(0)->iDependOn(1));

    EXPECT_EQ(context_l.getService(1)->getId(), 1);
    EXPECT_EQ(context_l.getService(1)->getSpreadMin(), 1);
    EXPECT_EQ(context_l.getService(1)->getNbServicesIDependOn(), 1);
    EXPECT_TRUE(context_l.getService(1)->iDependOn(0));
    EXPECT_FALSE(context_l.getService(1)->iDependOn(1));



}
