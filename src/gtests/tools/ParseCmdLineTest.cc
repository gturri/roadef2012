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
