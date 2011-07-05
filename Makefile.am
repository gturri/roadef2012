SUBDIRS=
ACLOCAL_AMFLAGS = -I m4

bin_PROGRAMS = machineReassignment
if WANT_GTEST
bin_PROGRAMS += testU
endif
EXTRA_PROGRAMS = testU

machineReassignment_FILES = \
	$(top_srcdir)/src/tools/random/RandomCoreImpl.cc \
	$(top_srcdir)/src/tools/random/RandomCoreMT.cc \
	$(top_srcdir)/src/tools/random/RandomGenerateur.cc

machineReassignment_SOURCES = \
	$(top_srcdir)/src/main.cc \
	$(machineReassignment_FILES)

machineReassignment_CPPFLAGS = \
	-I $(top_srcdir)/src

testU_SOURCES = \
	$(top_srcdir)/src/gtests/tools/random/RandomGenerateurTest.cc \
	$(machineReassignment_FILES)

testU_CPPFLAGS = \
	$(GTEST_INCLUDE) \
	$(GMOCK_INCLUDE) \
	-I $(top_srcdir)/src

testU_LDADD = \
	$(GMOCK_LIBS) \
	-lpthread

