AC_DEFUN([AC_BOOST], [
        LDFLAGS="$LDFLAGS -lboost_program_options-mt"
        LDFLAGS="$LDFLAGS -lboost_regex-mt"
        LDFLAGS="$LDFLAGS -lboost_thread-mt"
        CPPFLAGS="$CPPFLAGS -I/usr/local/include"
        LDFLAGS="$LDFLAGS -L/usr/local/lib" 
])
