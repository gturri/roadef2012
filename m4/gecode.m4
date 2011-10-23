AC_DEFUN([AC_GECODE], [
        AC_ARG_WITH(gecode-dir,
            AC_HELP_STRING([--with-gecode-dir=DIR],[where the root of gecode is installed]),
            [
            AS_IF([test "x$withval" != "xno"],
                [
                    CPPFLAGS="$CPPFLAGS -I$withval/include"
                    LDFLAGS="$LDFLAGS -L$withval/lib -lgecodeint -lgecodesearch -lgecodeminimodel -pthread"
                ]
            )
        ])
])
