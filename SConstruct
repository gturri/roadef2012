import os

CacheDir(os.environ["HOME"] + '/cache')
print "Caching files in " + os.environ["HOME"] + '/cache'

AddOption("--generateur", action="store_true", default=False)
AddOption("--gtests", action="store_true", default=False)
AddOption("--gecode", action="store_true", default=False)
AddOption("--loglvl", dest="loglvl", type="string", nargs=1, action="store")
Help("--generateur : Compile the instance generator\n")
Help("--gtests : Compile the unit tests. The path to gmock and gtest may be specified in the variable GTEST_PATH\n")
Help("--gecode : Compile with gecode. The path to the library may be specified in the variable GECODE_PATH\n")
levels = ["useless", "debug", "info", "warning", "erreur", "wtf", "silent"]
Help("--loglvl wantedLevel : set the log level. The level should be in " + str(levels) + "\n")

#Dealing with the log level
logLvlStr = GetOption("loglvl")
logLvl = 3
idx=0
while idx < len(levels):
  if levels[idx] == logLvlStr:
    logLvl = idx
  idx += 1
print "logLvl : ", levels[logLvl]

#Dealing with the generator
buildGenerateur = False
if GetOption("generateur"):
  buildGenerateur = True

#Dealing with unit tests: everything should be rebuilt since we pass an additional flag (-DUTEST)
buildTest = False
if GetOption("gtests"):
  buildTest = True


#If needed, build unit tests
if buildTest:
  SConscript("src/SConscript", variant_dir="buildUTests", exports="buildTest buildGenerateur logLvl")

#Now, build the rest
buildTest = False
SConscript("src/SConscript", variant_dir="build", exports="buildTest buildGenerateur logLvl")

