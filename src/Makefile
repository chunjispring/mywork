#编译所有子目录
#SUBDIRS=`ls -d */ | grep -v 'bin' | grep -v 'lib' | grep -v 'include'`

#编译指定子目录
SUBDIRS= lib_com lib_algorithm lib_bas\
         c_test mysql_tst opripc\
         encrypt decrypt

#函数定义
define make_subdir
	@for subdir in $(SUBDIRS) ; do \
  ($(MAKE) -C $$subdir $1) \
  done;
endef

.PHONY: all
all:
	$(call make_subdir, all)

.PHONY: install
install :
	$(call make_subdir, install)

.PHONY: debug
debug:
	$(call make_subdir , debug)

.PHONY: clean
clean:
	$(call make_subdir , clean)

