AC_DEFUN([AC_BOOST], [
        LDFLAGS="$LDFLAGS -lboost_program_options"
        LDFLAGS="$LDFLAGS -lboost_regex"
        LDFLAGS="$LDFLAGS -lboost_thread"
        CPPFLAGS="$CPPFLAGS -I/usr/local/include"
        LDFLAGS="$LDFLAGS -L/usr/local/lib" 
])
