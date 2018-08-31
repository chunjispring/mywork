# environment variables must be define
#
# $MKHOME : home directory of makefile 
# $CCFLG  : compiler options for c source code
# $CXXFLG : compiler options for c++ source code
# $EXFLG  : link options for excecuteable object
# $DBFLG  : debug mode options
# $OPFLG  : optimize mode options
# $DLFLG  : link options for dynamic library
# $DLFIX  : suffix of dynamic library
# $SLFLG  : link options for static library
# $SLFIX  : suffix of static library

SHELL = /bin/bash

#平台相关编译选项
CC  = gcc
CXX = g++

DLINK = gcc
DLFLG = -shared
DLFIX = .so

SLINK = ar
SLFLG = cqs
#SLFLG = crs
SLFIX = .a

CCFLG = -fPIC -std=c99 -Wall -Wno-implicit-function-declaration -Wno-parentheses -Wno-missing-braces -pipe -Wpointer-arith -Wsign-compare -funsigned-char
OPFLG = -O -DNDEBUG -D__DEBUG__
DBFLG = -g
SOFLAG = -shared -fPIC
CLINE1 = "++++++++++++++++++++++++++++++++"
CLINE2 = "------------------------------------------------------------"
CLINE3 = "============================================================"

UXLIBS = -lm -lc
DLLIBS = -ldl
NETLIBS =
CURLIBS = -lcurses
CRYLIBS =
THREADLIBS = -lpthread
THREADDEFS = -pthread

#常用命令
PC    = proc
EC    = esql
DB2   = db2
JAVAC = javac
JAVAH = javah
RMIC  = rmic
YACC  = yacc
RM    = rm -f
CP    = cp
MV    = mv
CD    = cd
ECHO  = @echo

#平台相关
OSTYPE=Linux

#发布选项
debugdynamic_flag   = -g
releasedynamic_flag = -O
debugstatic_flag    = -g
releasestatic_flag  = -O
debugexec_flag      = -g
releaseexec_flag    = -O
