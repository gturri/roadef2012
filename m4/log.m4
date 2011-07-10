AC_DEFUN([AC_LOGLVL], [
	logLevel=3
	AC_ARG_WITH(log-level,
		AC_HELP_STRING([--with-log-level=LEVEL],[useless, debug, info, warning, erreur, wtf, silent]),
		[
			AS_IF([test "x$withval" == "xno"],[logLevel=6])
			AS_IF([test "x$withval" == "xuseless"],[logLevel=0])
			AS_IF([test "x$withval" == "xdebug"],[logLevel=1])
			AS_IF([test "x$withval" == "xinfo"],[logLevel=2])
			AS_IF([test "x$withval" == "xwarning"],[logLevel=3])
			AS_IF([test "x$withval" == "xerreur"],[logLevel=4])
			AS_IF([test "x$withval" == "xwtf"],[logLevel=5])
			AS_IF([test "x$withval" == "xsilent"],[logLevel=6])
		])

	CPPFLAGS="$CPPFLAGS -DMIN_LOG_LVL=$logLevel"
])
