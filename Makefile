obj-m := fuck_net.o

ifeq (,$(BUILD_KERNEL))
 BUILD_KERNEL=$(shell uname -r)
endif

PWD := $(shell pwd)
EXTRA_CFLAGS += -I${PWD}

HERE=${PWD}

# set the install path
INSTDIR := $(DESTDIR)/lib/modules/$(BUILD_KERNEL)/kernel/net/fuck_net
TARGETDIR := $(DESTDIR)/usr/src/$(BUILD_KERNEL)/include/linux/

all: userland Makefile fuck_net.c linux/fuck_net.h
#	@if test "$(USER)" = "root"; then \
#		echo "********** WARNING WARNING WARNING **********"; \
#		echo "*"; \
#		echo "* Compiling FUCK_NET as root might lead you to compile errors"; \
#		echo "* Please compile FUCK_NET as unpriviliged user"; \
#		echo "*"; \
#		echo "*********************************************"; \
#	fi
	make -C /lib/modules/$(BUILD_KERNEL)/build SUBDIRS=${HERE} EXTRA_CFLAGS='${EXTRA_CFLAGS}' modules
#	cd plugins; make

clean:
	make -C test clean
	make -C /lib/modules/$(BUILD_KERNEL)/build SUBDIRS=$(HERE) clean
	\rm -f *~ Module.symvers  Module.markers  modules.order *#

install:
	mkdir -p $(INSTDIR)
	cp *.ko $(INSTDIR)
	mkdir -p $(DESTDIR)/usr/include/linux
	cp linux/fuck_net.h $(DESTDIR)/usr/include/linux
	@if test -d ${TARGETDIR}; then \
		cp linux/fuck_net.h ${TARGETDIR}; \
	fi
ifeq (,$(DESTDIR))
	/sbin/depmod $(BUILD_KERNEL)
else
	@echo "*****NOTE:";
	@echo "fuck_net,ko kernel module installed in ${DESTDIR}";
	@echo "/sbin/depmod not run.  modprobe fuck_net won't work " ;
	@echo "You can load the kernel module directly using" ;
	@echo "insmod <path>/fuck_net.ko" ;
	@echo "*****";
endif

userland:
	make -C test
