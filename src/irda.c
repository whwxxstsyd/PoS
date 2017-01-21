#include<header.h>

int Ir(void)
{
	lk_dispclr();
	struct termios my_termios;
	int n,i,count=0;
	unsigned char send[25]={0x3a,0x30,0x30,0x34,0x32,0x33,0x41,0x43,0x35,0x0D,0x0A};
	unsigned char recv[1024];
	unsigned char resp[1024]={0x3a,0x30,0x30,0x34,0x32,0x33,0x41,0x43,0x35,0x0D,0x0A,0x3a,0x31,0x30,0x34,0x32,0x4c,0x57,0x2d,0x4d,0x50,0x50,0x4b,0x56,0x2d,				0x30,0x31,0x2d,0x30,0x38,0x31,0x30,0x35,0x37,0x41,0x38,0x0d,0x0a};
	static int fd;
	memset(&my_termios, 0, sizeof(struct termios));
	fd = open("/dev/ttymxc0",O_RDWR|O_NOCTTY|O_NONBLOCK);
	if( fd < 0 ) {  fprintf(stderr,"Unable to open port \n Please check the Arguments\n"); return -1; }

	tcflush(fd,TCIFLUSH);
	my_termios.c_cflag=CS8|CREAD|B2400|CLOCAL;//|PARENB;
	my_termios.c_cc[VMIN]=0;
	my_termios.c_cc[VTIME]=0;
	tcsetattr(fd,TCSANOW,&my_termios);
	
	for (i=0; i< 11; i++)
		printf ("SEND = %x\n",send[i]) ;
	
	n  = write(fd,send,11);
	if( n != 11)
		fprintf(stderr,"Write Error\n");
	
	n = 0 ;
	sleep(2) ;
	printf ("\n") ;
		memset(recv,0,sizeof(recv));
	while(1){
		sleep(1);
		n = read(fd,recv,255);
	//	printf("n=%d\n",n);
//		sleep(1);
	//	printf("recv=%s\n",recv);
//		sleep(1);
//		ret=memcmp(resp,recv,38);
	//	printf("recv=%s\n",recv);
	//	printf("ret=%d\n",ret);
	//	printf("resp=%s\n",resp);
	//	for(i=0;i<=n-1;i++)
	//	{
	//		printf("recv=%x resp=%x \n",recv[i],resp[i]);
	//		printf("n=%d\n",n);
	//	}
		if(n==38)
		{
			printf("recv=%s\n",recv);
			lk_disptext(1,5,"ir success",0);
			lk_disptext(3,0,recv+12,0);
			printf("ir received success\n");
			break;
		}
		else if(count==5)
		{
			lk_disptext(2,5,"ir is failed",0);
			printf("n=%d\n",n);
			break;
		}
		count++;
	}


	lk_disptext(5,0,"Press Any Key to Exit",0);
	lk_getkey();	
	close(fd) ;
	return 0;
}

