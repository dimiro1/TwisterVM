AC_INIT(TwisterVM, 0.5, dimiro1@gmail.com)
AM_INIT_AUTOMAKE(TwisterVM, 0.5)
AM_MAINTAINER_MODE
AC_CONFIG_HEADER(config.h)

AC_LANG(C++)
AC_PROG_CXX
AC_PROG_INSTALL

dnl------------------------
dnl Checks for COCO/R
dnl------------------------

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

AC_OUTPUT(Makefile
			 src/Makefile
			 src/assembler/Makefile
			)

AC_MSG_NOTICE([
Sumario:
	  cococpp	 : $COCOCPP_BIN
])
