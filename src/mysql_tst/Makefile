#|----------------------------------------------------------------------------|
#| FILE NAME    : Makefile                                                    |
#| DESCRIPTIONS : Sample makefile                                             |
#|----------------------------------------------------------------------------|

include $(WKPATH)/mak/database.mk

#特别指定头文件
PRGINCP = $(MYSQLINCP)

#特别指定编译目标
PRGTARG = mysql_tst.bin

#特别指定链接库
PRGLIBS = $(MYSQLLIBP)

#特别指定宏
PRGDEFS = 

#特别指定obj
#PRGPATH = $(WKPATH)/src/c_test
#PRGOBJS = $(PRGPATH)/main.o 

debug all: debugexec
release: releaseexec

# DO NOT modify any code below!!!
releasedynamic debugdynamic releasestatic debugstatic releaseexec debugexec clean:
	@make -f $(WKPATH)/mak/mkstand.mk $@ PUBTYPE=$@ TARGET="$(PRGTARG)" OBJS="$(PRGOBJS)" LIBS="$(PRGLIBS)" DEFS="$(PRGDEFS)" EXTINCP="$(PRGINCP)"
