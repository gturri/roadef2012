SUBDIRS=
ACLOCAL_AMFLAGS = -I m4

bin_PROGRAMS = machineReassignment

machineReassignment_FILES = \
	$(top_srcdir)/src/tools/random/RandomCoreImpl.cc \
	$(top_srcdir)/src/tools/random/RandomCoreMT.cc \
	$(top_srcdir)/src/tools/random/RandomGenerateur.cc

machineReassignment_SOURCES = \
	$(top_srcdir)/src/main.cc \
	$(machineReassignment_FILES)

machineReassignment_CPPFLAGS = \
	-I $(top_srcdir)/src
