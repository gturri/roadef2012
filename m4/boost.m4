AC_DEFUN([AC_BOOST], [
        LDFLAGS="$LDFLAGS -lboost_program_options"
        LDFLAGS="$LDFLAGS -lboost_serialization-mt "
        LDFLAGS="$LDFLAGS -lboost_serialization    "
        LDFLAGS="$LDFLAGS -lboost_wserialization-mt"
        LDFLAGS="$LDFLAGS -lboost_wserialization   "
])
