AC_DEFUN([AC_GECODE], [
        withGecode=true
        AC_ARG_WITH(gecode-dir,
            AC_HELP_STRING([--with-gecode-dir=DIR],[where the root of gecode is installed]),
            [
            AS_IF([test "x$withval" != "xno"],
                [
                    withGecode=true
                    AS_IF([test "x$withval" != "xyes"],
                        [
                        GECODE_CPPFLAGS="-I$withval/include"
                        GECODE_LDFLAGS="-L$withval/lib"
                        ])
                ],
                [
                    withGecode=false
                ]
            )
        ])

        AS_IF([test "x$withGecode" == "xtrue"],
            [
                CPPFLAGS="$CPPFLAGS -DUSE_GECODE $GECODE_CPPFLAGS"
                LDFLAGS="$LDFLAGS $GECODE_LDFLAGS -pthread -lgecodesearch -lgecodeminimodel -lgecodeint -lgecodekernel -lgecodesupport -lgecodeset"
            ])
])
