SUBDIRS=
ACLOCAL_AMFLAGS = -I m4

bin_PROGRAMS = machineReassignment

if WANT_GTEST
bin_PROGRAMS += testU
TESTS = testU
endif

if WANT_GENERATEUR
bin_PROGRAMS += generateurInstance
endif


EXTRA_PROGRAMS = testU generateurInstance

machineReassignment_FILES = \
	$(top_srcdir)/src/alg/ContextALG.cc \
	$(top_srcdir)/src/alg/SequenceStrategyOptim.cc \
	$(top_srcdir)/src/alg/StrategyOptim.cc \
	$(top_srcdir)/src/dtoin/BalanceCostDtoin.cc \
	$(top_srcdir)/src/dtoin/InstanceReaderDtoin.cc \
	$(top_srcdir)/src/dtoin/InstanceReaderInterface.cc \
	$(top_srcdir)/src/dtoin/InstanceReaderHumanReadable.cc \
	$(top_srcdir)/src/dtoin/MachineDtoin.cc \
	$(top_srcdir)/src/dtoin/ProcessDtoin.cc \
	$(top_srcdir)/src/dtoin/PoidsDtoin.cc \
	$(top_srcdir)/src/dtoin/RessourceDtoin.cc \
	$(top_srcdir)/src/dtoin/ServiceDtoin.cc \
	$(top_srcdir)/src/dtoin/SolutionDtoin.cc \
	$(top_srcdir)/src/dtoout/InstanceWriterDtoout.cc \
	$(top_srcdir)/src/dtoout/InstanceWriterInterface.cc \
	$(top_srcdir)/src/dtoout/InstanceWriterHumanReadable.cc \
	$(top_srcdir)/src/dtoout/SolutionDtoout.cc \
	$(top_srcdir)/src/bo/BalanceCostBO.cc \
	$(top_srcdir)/src/bo/ContextBO.cc \
	$(top_srcdir)/src/bo/LocationBO.cc \
	$(top_srcdir)/src/bo/MMCBO.cc \
	$(top_srcdir)/src/bo/MachineBO.cc \
	$(top_srcdir)/src/bo/NeighborhoodBO.cc \
	$(top_srcdir)/src/bo/ProcessBO.cc \
	$(top_srcdir)/src/bo/RessourceBO.cc \
	$(top_srcdir)/src/bo/ServiceBO.cc \
    $(top_srcdir)/src/tools/Checker.cc \
	$(top_srcdir)/src/tools/Log.cc 


fichiersCommunsTestsEtGenerateur = \
	$(top_srcdir)/src/generateur/alg/DummyStrategyGeneration.cc \
	$(top_srcdir)/src/generateur/alg/StrategyGeneration.cc

machineReassignment_SOURCES = \
	$(top_srcdir)/src/main.cc \
	$(machineReassignment_FILES)

machineReassignment_CPPFLAGS = \
	-I $(top_srcdir)/src

generateurInstance_SOURCES = \
	$(machineReassignment_FILES) \
    $(fichiersCommunsTestsEtGenerateur) \
	$(top_srcdir)/src/generateur/alg/GenerateFromExisting.cc \
	$(top_srcdir)/src/generateur/ParseCmdLine.cc \
	$(top_srcdir)/src/generateur/StrategyGenerationSelecter.cc \
	$(top_srcdir)/src/generateur/WriterSelecter.cc \
	$(top_srcdir)/src/generateur/generateur_main.cc

generateurInstance_CPPFLAGS = \
	-I $(top_srcdir)/src

testU_SOURCES = \
    $(top_srcdir)/src/gtests/ContextBOBuilder.cc \
	$(top_srcdir)/src/gtests/bo/ContextBOTest.cc \
	$(top_srcdir)/src/gtests/bo/operatorEgaliteTest.cc \
	$(top_srcdir)/src/gtests/dtoin/BalanceCostDtoinTest.cc \
	$(top_srcdir)/src/gtests/dtoin/InstanceReaderHumanReadableTest.cc \
	$(top_srcdir)/src/gtests/dtoin/MachineDtoinTest.cc \
	$(top_srcdir)/src/gtests/dtoin/ProcessDtoinTest.cc \
	$(top_srcdir)/src/gtests/dtoin/PoidsDtoinTest.cc \
	$(top_srcdir)/src/gtests/dtoin/RessourceDtoinTest.cc \
	$(top_srcdir)/src/gtests/dtoin/ServiceDtoinTest.cc \
	$(top_srcdir)/src/gtests/dtoin/SolutionDtoinTest.cc \
	$(top_srcdir)/src/gtests/dtoin/TestDtoinHelper.cc \
	$(top_srcdir)/src/gtests/tools/CheckerBalanceCostTest.cc \
	$(top_srcdir)/src/gtests/tools/CheckerCapaTest.cc \
	$(top_srcdir)/src/gtests/tools/CheckerConflictTest.cc \
	$(top_srcdir)/src/gtests/tools/CheckerDependancesTest.cc \
	$(top_srcdir)/src/gtests/tools/CheckerLoadCostTest.cc \
	$(top_srcdir)/src/gtests/tools/CheckerMMCTest.cc \
	$(top_srcdir)/src/gtests/tools/CheckerPMCTest.cc \
	$(top_srcdir)/src/gtests/tools/CheckerSMCTest.cc \
	$(top_srcdir)/src/gtests/tools/CheckerSpreadTest.cc \
    $(fichiersCommunsTestsEtGenerateur) \
	$(machineReassignment_FILES)

testU_CPPFLAGS = \
	$(GTEST_INCLUDE) \
	$(GMOCK_INCLUDE) \
	-I $(top_srcdir)/src

testU_LDADD = \
	$(GMOCK_LIBS) \
	-lpthread

