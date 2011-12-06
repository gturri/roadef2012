#!/bin/sh -x
CXX="g++"
CXXFLAGS="-O2"

$CXX -c $CXXFLAGS solution_checker.cc
$CXX -c $CXXFLAGS solution_checker_run.cc
$CXX $CXXFLAGS solution_checker_run.o solution_checker.o -o solution_checker 
