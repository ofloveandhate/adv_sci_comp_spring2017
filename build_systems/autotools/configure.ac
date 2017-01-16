




#we're building my_cool_project, version 0.0.1, and the corresponding email is yours
AC_INIT([my_cool_project], [0.0.1], [danielthebrake@gmail.com],[nups], [])


# Force autoconf to be at least this version number:
AC_PREREQ([2.68])


#
AC_CONFIG_AUX_DIR([config])

# turn on the keeping of produced objects in their folders.  this is for non-recursive make
# and autotools
# see Recursive Make Considered Harmful, and any number of demos.
AM_INIT_AUTOMAKE([1.13 subdir-objects])

#the language for nups is C++
AC_LANG([C++])

#another directive to use the m4 folder
AC_CONFIG_MACRO_DIR([m4])

#the only produced file will be a single Makefile.
AC_CONFIG_FILES([Makefile])


#enable the creation of shared libraries
AC_ENABLE_SHARED

#enable the creation of static libraries
AC_ENABLE_STATIC


#find the linker
AC_PROG_LN_S

#find the command for making directories with their parents
AC_PROG_MKDIR_P

#fire up libtool
LT_INIT

AX_CXX_COMPILE_STDCXX_11

# the form of the following commands --
# AC_SEARCH_LIBS(function, libraries-list, action-if-found, action-if-not-found, extra-libraries)


#find the math library
AC_SEARCH_LIBS([cos], [m], [], [AC_MSG_ERROR([unable to find the cos() function])])




AX_BOOST_BASE([1.53], [AX_BOOST_UNIT_TEST_FRAMEWORK], [AC_MSG_WARN([the my_cool_project test suite needs Boost at least 1.53, but it was not found in your system.  you cannot correctly build it, linking will fail.])])


AM_CONFIG_HEADER(include/config.h)

#wrap it up.
AC_OUTPUT
