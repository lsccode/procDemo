obj-m   := procstatics.o
#KERNEL := /lib/modules/`uname -r`/build #for mint/ubuntu
#KERNEL := /lib/modules/`uname -r`/source #for redhat
KERNEL := /root/workSpace/kernel/Build/Kernel
CC  = $(CROSS_COMPILE)gcc

all:
	make -C $(KERNEL) M=`pwd` modules
	$(CC) main.c -o main.out
 
install:
	make -C $(KERNEL) M=`pwd` modules_install
	depmod -A
 
clean:
	make -C $(KERNEL) M=`pwd` clean	
