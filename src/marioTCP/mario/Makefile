#|----------------------------------------------------------------------------|
#| FILE NAME    : Makefile                                                    |
#| DESCRIPTIONS : Sample makefile                                             |
#|----------------------------------------------------------------------------|

#特别指定头文件
PRGINCP = -I$(WKPATH)/src/marioTCP/include

#特别指定编译目标
PRGTARG = mario

#特别指定链接库
PRGLIBS = 

#特别指定宏
PRGDEFS = -DLINUX32 -D__DEBUG__

#特别指定obj
PRGPATH = $(WKPATH)/src/marioTCP/mario
PRGOBJS = $(PRGPATH)/mario.o 

debug all: debugstatic
release: releasestatic

# DO NOT modify any code below!!!
releasedynamic debugdynamic releasestatic debugstatic releaseexec debugexec clean:
	@make -f $(WKPATH)/mak/mkstand.mk $@ PUBTYPE=$@ TARGET="$(PRGTARG)" OBJS="$(PRGOBJS)" LIBS="$(PRGLIBS)" DEFS="$(PRGDEFS)" EXTINCP="$(PRGINCP)"
