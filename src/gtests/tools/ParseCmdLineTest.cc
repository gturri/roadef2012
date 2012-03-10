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

#include "tools/ParseCmdLine.hh"
#include "gtests/tools/ParseCmdLineTestHelper.hh"
#include <gtest/gtest.h>


/* Test la reconnaissance de l'option -name, qui a un format exotique
 */
TEST(ParseCmdLine, name){
    ParseCmdLineTestHelper helper_l;
    helper_l.addCmdLineArg("-name");

    variables_map opt_l = ParseCmdLine::parse(helper_l.argc(), helper_l.argv());
    EXPECT_TRUE(opt_l.count("name"));
}

TEST(ParseCmdLine, usualOptions){
    ParseCmdLineTestHelper helper_l;
    helper_l.addCmdLineArg("-t");
    helper_l.addCmdLineArg("250");
    helper_l.addCmdLineArg("-p");
    helper_l.addCmdLineArg("instanceFile.txt");
    helper_l.addCmdLineArg("-i");
    helper_l.addCmdLineArg("solInitFile.txt");
    helper_l.addCmdLineArg("-o");
    helper_l.addCmdLineArg("outFile.txt");
    helper_l.addCmdLineArg("-s");
    helper_l.addCmdLineArg("42");

    variables_map opt_l = ParseCmdLine::parse(helper_l.argc(), helper_l.argv());

    EXPECT_EQ(opt_l["time"].as<int>(), 250);
    EXPECT_EQ(opt_l["param"].as<string>(), "instanceFile.txt");
    EXPECT_EQ(opt_l["init"].as<string>(), "solInitFile.txt");
    EXPECT_EQ(opt_l["out"].as<string>(), "outFile.txt");
    EXPECT_EQ(opt_l["seed"].as<int>(), 42);
    EXPECT_FALSE(opt_l.count("help"));
    EXPECT_FALSE(opt_l.count("name"));
}

TEST(ParseCmdLine, defaultOutFile){
    ParseCmdLineTestHelper helper_l;

    variables_map opt_l = ParseCmdLine::parse(helper_l.argc(), helper_l.argv());

    EXPECT_NE(opt_l["out"].as<string>(), "");


}
