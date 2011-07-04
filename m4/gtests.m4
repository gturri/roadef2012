AC_DEFUN([AC_PATH_GTEST], [
	compileTest=false
	AC_ARG_WITH(libgmock-dir,
		AC_HELP_STRING([--with-libgmock-dir=DIR],[where the root of gmock is installed]),
		[
			AS_IF([test "x$withval" != "xno"],
				[
				compileTest=true
				GMOCK_INCLUDE=-I$withval/include
				GTEST_INCLUDE=-I$withval/gtest/include
				GMOCK_LIBS="$withval/make/gmock_main.a"

				ac_save_CFLAGS="$CFLAGS"
				ac_save_CPPFLAGS="$CPPFLAGS"
				CFLAGS="$GMOCK_INCLUDE $GTEST_INCLUDE $CFLAGS"
				CPPFLAGS="$GMOCK_INCLUDE $GTEST_INCLUDE $CPPFLAGS"
				AC_CHECK_HEADER(gmock/gmock.h,,[ AC_MSG_ERROR([gmock.h introuvable. Utiliser --without-libgmock pour ne pas compiler les tests unitaires]) ])
				AC_CHECK_HEADER(gtest/gtest.h,,[ AC_MSG_ERROR([gtest.h introuvable. Utiliser --without-libgmock pour ne pas compiler les tests unitaires]) ])
				AC_CHECK_FILE($GMOCK_LIBS,,[AC_MSG_ERROR(Impossible de trouver gmock_main.a. Utiliser --without-libgmock pour ne pas compiler les tests unitaires)])
				CFLAGS="$ac_save_CFLAGS"
				CPPFLAGS="$ac_save_CPPFLAGS"
				])
		])
	
	AM_CONDITIONAL([WANT_GTEST], [test x$compileTest = xtrue])
	AC_SUBST(GMOCK_INCLUDE)
	AC_SUBST(GTEST_INCLUDE)
	AC_SUBST(GMOCK_LIBS)
])
