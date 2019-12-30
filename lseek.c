//##################################################################
// File Name: lseek.c
// File Effect: 
// Author: tttt
// mail: tttt@xiyoulinux.org
// Created Time: 2019年12月29日 星期日 22时27分45秒
//=============================================================
//!/usr/bin/python

#include <sys/socket.h>
#include <netinet/in.h>
#include <assert.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <libgen.h>
#include <sys/uio.h>
#include <sys/stat.h>
#include <sys/sendfile.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/mman.h>

int main()
{
	int read_count = 0;
	char read_buf[1024];

	memset(read_buf,0,sizeof(read_buf));
	int fd = open("1.txt",O_RDONLY);
	
	while((read_count = read(fd,read_buf,1024)) && read_count > 0)
	{
		printf("cnt = %d\n",read_count);
		
/*		for(int i = 0;i < read_count;i++)
		{
			printf("%d ",read_buf[i]);
		}
*/
	//	printf("\n");
		printf("%s",read_buf);

	//	lseek(fd,-4,SEEK_CUR);



		memset(read_buf,0,sizeof(read_buf));
	}




	return 0;
}

