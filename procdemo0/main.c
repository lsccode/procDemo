#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

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

	close(fd);	
}
