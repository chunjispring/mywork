.PHONY:all begin end clean

include $(WKPATH)/mak/platform.mk
include $(WKPATH)/mak/database.mk

# 文件接收的参数
# $PUBTYPE: complie type
# $OBJS   : c object files list
# $LIBS   : libs required for executable object
# $DEFS   : define flag list
# $TARGET : target objetc name
# $EXTINCP: ext include dir

PACK_DATE=`date +%y%m%d`

# 应用库路径
COMLIBP   = $(WKPATH)/lib
SYSLIBP   = /usr/lib64
ICONVLIBP = /usr/local/lib64

# 头文件路径
COMINCP   = $(WKPATH)/include
SYSINCP   = /usr/include
ICONVINCP = /usr/local/include
LINUXINCP = /usr/include/x86_64-linux-gnu

# 编译选项
INCPS = -I$(ICONVINCP) -I$(SYSINCP) -I$(COMINCP) -I$(LINUXINCP) 
LIBPS = -L$(ICONVLIBP) -L$(SYSLIBP) -L$(COMLIBP) 

CCFLGS  = $(CCFLG) $(DEFS) $(DBDEF) $(OSDEF) $(PROCDEF) $(BITDEF) $(INCPS)
CXXFLGS = $(CXXFLG) $(DEFS) $(DBDEF) $(OSDEF) $(PROCDEF) $(BITDEF) $(INCPS)
DLFLGS  = $(DLFLG) $(LIBPS)

#源代码
CSRC = $(shell find . -name "*.c" -exec ls {} \;)

#指定OBJS时，不使用默认的COBJS
ifneq ("$(OBJS)", "")
#$(warning $(OBJS))
COBJS=$(OBJS)
else
#$(warning $(COBJS))
COBJS=$(patsubst %.c,%.o,$(CSRC)) 
endif

# 常用安装路径
BINTARG = $(WKPATH)/bin
LIBTARG = $(WKPATH)/lib
INCTARG = $(WKPATH)/include
DLTARG  = $(LIBTARG)/lib$(TARGET)$(DLFIX)
SLTARG  = $(LIBTARG)/lib$(TARGET)$(SLFIX)
EXTARG  = $(BINTARG)/$(TARGET)

debugdynamic:   begin setdebug   $(DLTARG) clean end
releasedynamic: begin setrelease $(DLTARG) clean end
debugstatic:    begin setdebug   $(SLTARG) clean end
releasestatic:  begin setrelease $(SLTARG) clean end
debugexec:      begin setdebug   $(EXTARG) clean end
releaseexec :   begin setrelease $(EXTARG) clean end

setdebug:
	@$(ECHO) "setdebug" > /dev/null

setrelease:
	@$(ECHO) "setrelease" > /dev/null

#静态库编译
$(SLTARG): $(COBJS) 
	$(ECHO) $(CLINE1) 'Now Start to Rebuild ($@)' $(CLINE1)
	$(RM) $@
	$(SLINK) $(SLFLG) $@ $(COBJS)
	$(ECHO) $(CLINE1) 'Rebuild ($@) successfully' $(CLINE1)

#动态库编译
$(DLTARG): $(COBJS) 
	$(ECHO) $(CLINE1) 'Now Start to Rebuild ($@)' $(CLINE1)
	$(RM) $@
	@if [ $(OSTYPE) = aix ]; \
	then \
		$(RM) $(MKHOME)/mak/exp/lib$(TARGET).exp ; \
		perl -e ' @objs = split " ", "$(COBJS)"; foreach $$obj (@objs) { $$obj =~ s/\.o$$//; if (-e "$${obj}.c") { $$filename = "$${obj}.c"; } elsif (-e "$${obj}.cpp") { $$filename = "$${obj}.cpp"; } elsif (-e "$${obj}.sqc") { $$filename = "$${obj}.sqc"; } else { die "cant find source file for $${obj}.o\n"; } open HANDLE, "<$$filename" or die "cant open $$filename"; @lines = <HANDLE>; close HANDLE; $$lines = join "", @lines; @funcs = $$lines =~ /BAS_EXPORT(?:.*?)\b(\w+)\b\s*[\(\[\{;,=\/]/sg; print join("\n", @funcs), "\n"; } ' > $(MKHOME)/mak/exp/lib$(TARGET).exp ; \
		$(DLINK) -o $@ $(DLFLGS) $(COBJS) $(LIBS) $(UXLIBS); \
	else \
		$(DLINK) -o `basename $@` $(DLFLGS) $(COBJS) $(LIBS); \
		$(MV) `basename $@` `dirname $@`; \
	fi
	$(DLINK) -o $@ $(DLFLGS) $(COBJS) $(LIBS) $(UXLIBS)
	$(ECHO) $(CLINE1) 'Rebuild ($@) successfully' $(CLINE1)

#可执行文件编译
$(EXTARG): $(COBJS)
	$(ECHO) $(CLINE1) 'Now Start to Rebuild ($@)' $(CLINE1)
	$(RM) $@
	$(CC) -o $@ $($(PUBTYPE)_flag) $(LIBPS) $(EXFLGS) $(COBJS) $(LIBS) $(UXLIBS)
	$(ECHO) $(CLINE1) 'Rebuild ($@) successfully' $(CLINE1)

#伪目标
begin:
	@$(ECHO) $(CLINE2) "Begin" $(CLINE2)

end:
	@$(ECHO) $(CLINE3) "Done!" $(CLINE3)
	@$(ECHO) ""

clean:
	$(RM) $(COBJS)

#隐式推导
.SUFFIXES:
.SUFFIXES: .y .java .class .CFG .cfg .sql .xc .ec .pc .sqC .sqc .cp .cpp .c .o

.xc.o:
	@$(RM) $*$(DBFIX)
	@$(CP) $*.xc $*$(DBFIX)
	@if [ $(DBTYPE) = ora ]; \
	then \
		$(PC) lines=yes define=$(DBD) include=$(TUXINCP) include=$(INCP) include=$(JINCP) include=$(JMDINCP) include=`dirname $@` code=ANSI_C iname=$*$(DBFIX); \
		$(CC) -o $@ $($(PUBTYPE)_flag) $(CCFLGS) $(EXTINCP) -c $*.c; \
		$(RM) $*.lis; \
	else \
		$(EC) -e -ED$(DBD) $(INCPS) $*$(DBFIX); \
		$(CC) -o $@ $($(PUBTYPE)_flag) $(CCFLGS) $(EXTINCP) -c `basename $*`.c; \
		$(RM) `basename $*`.c; \
	fi
	@$(RM) $*$(DBFIX) $*.c

.pc.o:
	@$(PC) lines=yes define=$(DBD) include=$(TUXINCP) include=$(INCP) include=$(JINCP) include=$(JMDINCP) include=`dirname $@` code=ANSI_C iname=$*$(DBFIX)
	@$(CD) `dirname $@` ; \
	$(CC) -o $@ $($(PUBTYPE)_flag) $(CCFLGS) $(EXTINCP) -c $*.c
	@$(RM) $*.lis $*.c

.ec.o:
	@$(EC) -e -ED$(DBD) $(INCPS) $*$(DBFIX)
	@$(CD) `dirname $@` ; \
	$(CC) -o $@ $($(PUBTYPE)_flag) $(CCFLGS) $(EXTINCP) -c `basename $*`.c; \
	$(RM) `basename $*`.c

.sqc.o:
	@$(RM) $(MKHOME)/bnd/`basename $*`.bnd $*.c $*.o
	$(ECHO) "Before Connecting to db $(DBNM) $(DBNAME) ..."
	$(ECHO) "$(DB2) prep $< version VER$(PACK_DATE) bindfile DYNAMICRULES bind QUALIFIER $(DBSCHEMA);"
	@if [ $(DBNM) = $(DBNAME) ]; \
	then \
		$(CONNECT_TXNDB); \
		$(DB2) prep $< version VER$(PACK_DATE) bindfile DYNAMICRULES bind QUALIFIER $(DBSCHEMA); \
		$(DB2) bind $*.bnd DYNAMICRULES bind QUALIFIER $(DBSCHEMA); \
	elif [ $(DBNM) = $(SDBNAME) ]; \
	then \
		$(CONNECT_SVCDB); \
		$(DB2) prep $< version VER$(PACK_DATE) bindfile DYNAMICRULES bind QUALIFIER $(SDBSCHEMA); \
		$(DB2) bind $*.bnd DYNAMICRULES bind QUALIFIER $(SDBSCHEMA); \
	fi
	$(ECHO) "$(CC) -o $@ $($(PUBTYPE)_flag) $(CCFLGS) $(EXTINCP) -c `basename $*`.c"
	@$(CD) `dirname $@` ; \
	$(CC) -o $@ $($(PUBTYPE)_flag) $(CCFLGS) $(EXTINCP) -c `basename $*`.c
	@$(RM) $*.c
	@$(MV) $*.bnd $(MKHOME)/bnd/`basename $*`.bnd

.cfg.o:
	@$(RM) $(MKHOME)/bnd/`basename $*`.bnd $*.sqc $*.c $*.o
	@$(CD) `dirname $@` 

	@if [ $(DBNM) = $(DBNAME) ]; \
	then \
		$(GENSQLTXN) `basename $*`; \
		$(CONNECT_TXNDB); \
		$(DB2) prep $*.sqc version VER$(PACK_DATE) bindfile DYNAMICRULES bind QUALIFIER $(DBSCHEMA); \
		$(DB2) bind $*.bnd DYNAMICRULES bind QUALIFIER $(DBSCHEMA); \
	elif [ $(DBNM) = $(SDBNAME) ]; \
	then \
		$(GENSQLSVC) `basename $*`; \
		$(CONNECT_SVCDB); \
		$(DB2) prep $*.sqc version VER$(PACK_DATE) bindfile DYNAMICRULES bind QUALIFIER $(SDBSCHEMA); \
		$(DB2) bind $*.bnd DYNAMICRULES bind QUALIFIER $(SDBSCHEMA); \
	fi
	@$(CD) `dirname $@` ; \
	$(CC) -o $@ $($(PUBTYPE)_flag) $(CCFLGS) $(EXTINCP) -c `basename $*`.c
	@$(RM) $*.c
	@$(MV) $*.bnd $(MKHOME)/bnd/`basename $*`.bnd

.sqC.o:
	@$(RM) $*.bnd
#	@$(DB2) connect to $(DBNM)
	$(DB2) prep $< bindfile 
	@$(DB2) bind $*.bnd
#	@$(DB2) connect reset
#	@$(DB2) terminate
	@$(CD) `dirname $@` ; \
	$(CXX) -o $@ $($(PUBTYPE)_flag) $(CCFLGS) $(EXTINCP) -c `basename $*`.C
	@$(RM) $*.bnd $*.C

.cp.o:
	$(CPRE) -y $(INCPS) -O $*.c $*.cp
	@$(CD) `dirname $@` ; \
	$(CC) -o $@ $($(PUBTYPE)_flag) $(CCFLGS) $(EXTINCP) -c `basename $*`.c
	@$(RM) $*.c

.cpp.o:
	@$(CD) `dirname $@` ; \
	$(CXX) -o $@ $($(PUBTYPE)_flag) $(CXXFLGS) $(EXTINCP) -c `basename $<`

.c.o:
	@$(RM) $*.o
	@$(CD) `dirname $@`; 
#	$(CC) -o $@ $($(PUBTYPE)_flag) $(CCFLGS) $(EXTINCP) -c `basename $*`.c
	$(CC) -o $@ $($(PUBTYPE)_flag) $(CCFLGS) $(EXTINCP) -c $*.c

.java.class:
	$(ECHO) "Compiling [$@] ..."
	@$(CD) `dirname $@`; \
	$(JAVAC) `basename $<`

.y.o:
	@$(CD) `dirname $@` ; \
	$(RM) y.output $*.c $*.h ; \
	$(YACC) -d -t -v `basename $*`.y ; \
	$(MV) y.tab.c $*.c ; \
	$(MV) y.tab.h $*.h ; \
	$(CC) -o $@ $($(PUBTYPE)_flag) $(CCFLGS) $(EXTINCP) -c `basename $*`.c

