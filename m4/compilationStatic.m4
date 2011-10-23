AC_DEFUN([AC_COMPILATION_STATIC], [
        AC_ARG_WITH(static,
            AC_HELP_STRING([--with-static],[Compile les binaires en static]),
            [LDFLAGS="-Wc,-static $LDFLAGS"])
])
