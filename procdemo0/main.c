#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#include "procstatics.h"

int main()
{
	int fd = open("/proc/jif", O_RDWR);
	char buf[128] = {0};
	
	int size = read(fd,buf,sizeof(buf));
	
	printf("bus is (%s)\n",buf);
	strcpy(buf,"hello world");
	
	size = write(fd,buf,strlen(buf));
	
	memset(buf,0,sizeof(buf));
	
	fsync(fd);
	
	lseek(fd,0,SEEK_SET);
	
	size = read(fd,buf,sizeof(buf));

	printf("bus is (%s)\n",buf);
	
	{
		int cmd;
		int arg = 0;
		
		cmd = MEMDEV_IOCPRINT;
		arg = 0;
		
		if(ioctl(fd,cmd,&arg) < 0)
		{
			printf("call cmd MEMDEV_IOCPRINT fail\n");
			return -1;
		}
		
		cmd = MEMDEV_IOCGETDATA;
		arg=0;
		
		if(ioctl(fd,cmd,&arg) < 0)
		{
			printf("call cmd MEMDEV_IOCGETDATA fail\n");
			return -1;
		}
		printf("in user space MEMDEV_IOCGETDATA get data is %d\n\n",arg);
		
		arg = 1102;
		cmd = MEMDEV_IOCSETDATA;		
		
		if(ioctl(fd,cmd,&arg) < 0)
		{
			printf("call cmd MEMDEV_IOCGETDATA fail\n");
			return -1;
		}
		
		cmd = MEMDEV_IOCGETDATA;		
		arg = 0;
		
		if(ioctl(fd,cmd,&arg) < 0)
		{
			printf("call cmd MEMDEV_IOCGETDATA fail\n");
			return -1;
		}
		printf("in user space MEMDEV_IOCGETDATA get data is %d\n\n",arg);
		
		
	}

	close(fd);	
}
