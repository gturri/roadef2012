AC_DEFUN([AC_BOOST], [
        LDFLAGS="$LDFLAGS -lboost_program_options"
        LDFLAGS="$LDFLAGS -lboost_regex"
        CPPFLAGS="$CPPFLAGS -I/usr/local/include"
])
