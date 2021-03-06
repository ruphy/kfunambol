dnl Process this file with autoconf to produce a configure script.
AC_INIT(../../src/c++/common/base/base64.cpp)
AC_CANONICAL_SYSTEM
AM_INIT_AUTOMAKE(funambol, 2.0)
AM_CONFIG_HEADER(config.h)

dnl Checks for programs.
AC_PROG_CXX
AC_PROG_LIBTOOL
dnl AM_GNU_GETTEXT - not currently used

dnl we use libcurl on all posix but Mac
dnl use_mac_ta="no"
dnl use_libcurl="no"
case $target in
*apple-darwin*)  use_mac_ta="yes" ;;
*) use_libcurl="yes" ;;
esac

dnl check for libcurl now instead of during make
if test "x$use_libcurl" = "xyes"; then
    AC_MSG_CHECKING([for libcurl])
    if CURL_LDFLAGS=`sh -c 'curl-config --libs' 2>&AS_MESSAGE_LOG_FD` && \
       CURL_CFLAGS=`sh -c 'curl-config --cflags' 2>&AS_MESSAGE_LOG_FD`; then
            AC_MSG_RESULT([found])
            AC_SUBST(CURL_LDFLAGS)
            AC_SUBST(CURL_CFLAGS)
    else
            AC_MSG_RESULT([missing])
            AC_MSG_ERROR([libcurl is required, check that its development package is installed and curl-config is in your PATH])
    fi
fi

if test "x$use_mac_ta" = "xyes"; then
    CURL_LDFLAGS="-framework CoreServices"
    AC_SUBST(CURL_LDFLAGS)
fi


dnl Check for certain headers.
AC_CHECK_HEADERS(time.h)

AC_ARG_ENABLE(unit-tests,
              AS_HELP_STRING([--enable-unit-tests],
                             [enables tests embedded in the source code of the library (changes content of the library)]),
              enable_unit_tests="$enableval", enable_unit_tests="no")
AC_ARG_ENABLE(integration-tests,
              AS_HELP_STRING([--enable-integration-tests],
                             [enables tests outside of the library (can be used together with normal builds of the library)]),
              enable_integration_tests="$enableval", enable_integration_tests="no")
AC_ARG_ENABLE(assert,
              AS_HELP_STRING([--enable-assert],
                             [turn on assertions]),
              enable_assert="$enableval", enable_assert="no")

if test $enable_assert == "no"; then
        AC_DEFINE(NDEBUG, 1, [Define to 1 if assertions should be disabled.])
fi

# Optionally use wchar_t for unicode strings
AC_ARG_ENABLE(wchar,
              AS_HELP_STRING([--enable-wchar],
                             [enable Unicode wchar usage]),
              enable_wchar="$enableval", enable_wchar="no")

if test $enable_wchar == "yes"; then
        AC_DEFINE(USE_WCHAR, 1, [Define to 1 if unicode wchar_t should be used.])
        AC_CHECK_HEADERS(wchar.h)
fi

# cppunit needed?
if test $enable_unit_tests == "yes" || test $enable_integration_tests == yes; then
        CPPUNIT_CXXFLAGS=`cppunit-config --cflags` || AC_MSG_ERROR("cppunit-config --cflags failed - is it installed?")
        CPPUNIT_LDFLAGS=`cppunit-config --libs` || AC_MSG_ERROR("cppunit-config --libs failed - is it installed?")
        CPPUNIT_TESTS=client-test
        AC_CHECK_HEADERS(signal.h)
fi
AC_SUBST(CPPUNIT_CXXFLAGS)
AC_SUBST(CPPUNIT_LDFLAGS)
AC_SUBST(CPPUNIT_TESTS)

if test $enable_unit_tests == "yes"; then
        AC_DEFINE(ENABLE_UNIT_TESTS, 1, [enable unit tests inside the library's source code])
fi
if test $enable_integration_tests == "yes"; then
        AC_DEFINE(ENABLE_INTEGRATION_TESTS, 1, [enable unit tests outside of the library's source code])
fi


AC_OUTPUT(Makefile src/Makefile include/Makefile test/Makefile)
