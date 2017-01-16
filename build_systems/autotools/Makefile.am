#this is the main Makefile.am for my_cool_project

# # # # # # # # # # # # # # # # # # # # # # # # # # # #
# this project uses non-recursive make.
#
# # # # # # # # # # # # # # # # # # # # # # # # # # # #

AM_YFLAGS = -d -p `basename $* | sed 's,y$$,,'`
AM_LFLAGS = -s -P`basename $* | sed 's,l$$,,'` -olex.yy.c

AM_CPPFLAGS = -I$(top_srcdir)/include

ACLOCAL_AMFLAGS = -I m4

####################################
###  set up the empty variables.  these are added onto by the below included files,
###  and are deliberately blank here.
#################################
bin_PROGRAMS =
BUILT_SOURCES =
CLEANFILES =

EXTRA_PROGRAMS =
EXTRA_LTLIBRARIES =

include_HEADERS =

lib_LTLIBRARIES =
lib_LIBRARIES =

noinst_LIBRARIES =
noinst_LTLIBRARIES =

TESTS =

######  end deliberately blank items

#see https://www.gnu.org/software/automake/manual/html_node/Suffixes.html
SUFFIXES = .cpp .hpp

rootincludedir = $(includedir)/my_cool_library
rootinclude_HEADERS = include/config.h

#initialize to empty and add to it in the Makemodule.am files below


############################
###  now include the Makemodule files from the subdirectories.  they will add on to the variables which are set above
##################################


include src/my_cool_library/Makemodule.am
include src/my_cool_program/Makemodule.am


include test/Makemodule.am
