obj-m	:= procstatics.o
KERNEL	:= /lib/modules/`uname -r`/build #for mint/ubuntu
#KERNEL	:= /lib/modules/`uname -r`/source #for redhat
 
all:
	make -C $(KERNEL) M=`pwd` modules
	gcc main.c -o main.out
 
install:
	make -C $(KERNEL) M=`pwd` modules_install
	depmod -A
 
clean:
	make -C $(KERNEL) M=`pwd` clean	
