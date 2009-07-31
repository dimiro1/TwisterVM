AC_INIT(TwisterVM, 0.6.4, dimiro1@gmail.com)
AM_INIT_AUTOMAKE(TwisterVM, 0.6.4)
AM_MAINTAINER_MODE
AC_CONFIG_HEADER(config.h)

AC_LANG(C++)
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_RANLIB

dnl------------------------
dnl Checks for COCO/R
dnl------------------------

if test "x${MANTAINER_MODE}" = "x"; then
  AC_PATH_PROG(COCOCPP_BIN, cococpp)

  if test "x${COCOCPP}" = "x"; then
	  AC_PATH_PROG(COCOCPP_BIN, cococpp)
  fi

  if test "x${COCOCPP_BIN}" = "x"; then
    AC_MSG_ERROR(
	 [
	    O programa "COCO/R" (ou cococpp) não foi encontrado
	    em seu sistema (PATH).
	    TwisterVM precisa do COCO/R instalado.
	 ])
  fi

  AC_SUBST(COCOCPP_BIN)
fi

AC_OUTPUT(Makefile
			 src/Makefile
			 src/assembler/Makefile
			 src/lib/Makefile
			 src/lib/io/Makefile)

