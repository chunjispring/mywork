#|----------------------------------------------------------------------------|
#| FILE NAME    : Makefile                                                    |
#| DESCRIPTIONS : Sample makefile                                             |
#|----------------------------------------------------------------------------|

#特别指定头文件
#PRGINCP = -I$(GFS_DIR)/include

#特别指定编译目标
PRGTARG = decrypt.bin

#特别指定链接库
PRGLIBS = -lcom -lmyalgorithm

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
