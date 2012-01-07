#!/bin/bash
scons \
  -j3 \
  --gtest \
  --generateur \
  --loglvl=debug \
  GTEST_PATH=/home/guillaume/Documents/sources/gmock \
  CXX="g++" \
  CXXFLAGS="-O2"
