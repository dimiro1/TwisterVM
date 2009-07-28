AC_INIT(TwisterVM, 0.6.1, dimiro1@gmail.com)
AM_INIT_AUTOMAKE(TwisterVM, 0.6.1)
AM_MAINTAINER_MODE
AC_CONFIG_HEADER(config.h)

AC_LANG(C++)
AC_PROG_CXX
AC_PROG_INSTALL

dnl------------------------
dnl Checks for COCO/R
dnl------------------------

dnl if test "x${MANTAINER_MODE}" = "x"; then
dnl   AC_PATH_PROG(COCOCPP_BIN, cococpp)

dnl   if test "x${COCOCPP}" = "x"; then
dnl 	  AC_PATH_PROG(COCOCPP_BIN, cococpp)
dnl   fi

dnl   if test "x${COCOCPP_BIN}" = "x"; then
dnl     AC_MSG_ERROR(
dnl 	 [
dnl 	    O programa "COCO/R" (ou cococpp) não foi encontrado
dnl 	    em seu sistema (PATH).
dnl 	    TwisterVM precisa do COCO/R instalado.
dnl 	 ])
dnl   fi

dnl   AC_SUBST(COCOCPP_BIN)
dnl fi

AC_OUTPUT(Makefile
			 src/Makefile
			 src/assembler/Makefile
			)

