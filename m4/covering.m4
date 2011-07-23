AC_DEFUN([AC_COVERING], [
        AC_ARG_ENABLE(
            covering,
            AC_HELP_STRING([--enable-covering],[Produire un binaire utilisable avec un outil de couverture de code tel que gcov]),
            [ CXXFLAGS="$CXXFLAGS -fprofile-arcs -ftest-coverage"]
        )
])
