obj-m	:= proc_test01.o
KERNEL	:= /lib/modules/`uname -r`/build #for mint/ubuntu
#KERNEL := /lib/modules/`uname -r`/source #for redhat
 
all:
	make -C $(KERNEL) M=`pwd` modules
 
install:
	make -C $(KERNEL) M=`pwd` modules_install
	depmod -A
 
clean:
	make -C $(KERNEL) M=`pwd` clean
