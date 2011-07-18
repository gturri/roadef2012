AC_DEFUN([AC_GENERATEUR_INSTANCES], [
        compileGenerateur=true
        AC_ARG_WITH(
            [generateur],
            AC_HELP_STRING([--with-generateur],[activer pour compiler le generateur d'instances]),
            [
                AS_IF([test "x$withval" == "xno"],
                [
                    compileGenerateur=false
                ])
            ])
        AM_CONDITIONAL([WANT_GENERATEUR], [test x$compileGenerateur = xtrue])
])
