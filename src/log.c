#include <header.h>

int ramdisk_type;short numofscroll=0;
char cpuid[20]="";


int copy_file (char *dest,char *src)
{
	unsigned char c[512];
	int in, out,n;
 
	in = open(src , O_RDONLY);
	out = open(dest, O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);

	if (in == -1 || out == -1)
	{
 	fprintf(stderr,"unable to oepn file %d %d\n" ,in,out);
 	return -1;
	}
		

	while(1)
 	{
		n=read(in,c,512);
 		if (n==0)
  		break;
 		write(out,c,n);
 	}

	close(in);
	close(out);

}

int Log_save()
{
	unsigned char buff[24]="";
	char posm[100]="";
	char unid[100]="";
	unsigned char hrwid[100]="";
	unsigned char machineid[100]="";	
	char touch[100]="";
	char echo[100]="";
	char cmd[100]="";
	char rmcmd[50]="";
	char macid[30]="";
	char machid[11]="";
	char mac[100]="";		
	int ret=0;
	extern char autobuf[];
	struct tm *itim;
	char tim[40]="";
	char dat[40]="";
	char imei[30]="";
	char imeicmd[100]="";
	unsigned char pos=2;
	unsigned char hid[8]="";
	static char chr[100]="";



	lk_dispclr();


   if(lk_gethwid(hid)<0)
	{
	lk_dispclr();
        lk_disptext(2,2,"Unable to get HWID",1);
        sleep(2);
        }

	
	printf("hwid =%s\n",hid);


	if(getmachid(machid)<0)
	{
		lk_dispclr();
       		 lk_disptext(2,2,"Unable to get Machine ID",1);
        	sleep(2);
	}


	fprintf(stderr,"machine id =%s\n",machid);
	get_macid(macid);
	fprintf(stderr,"macid id =%s\n",macid);
	get_IMEI_number(imei);	
	fprintf(stderr,"hardware id =%s\n",hid);
	fprintf(stderr,"imei =%s\n",imei);
        hid[8]=0x00;
	if(uid(buff)==-1)
	{
	lk_dispclr();	
	lk_disptext(2,2,"Unable to get UID",1);
	sleep(2);
	}
	else
	{
	fprintf(stderr,"UID IS  %s",buff);
        fprintf(stderr,"\n");
	sleep(2);
	}
	lk_dispclr();
	lk_disptext(1,2,"Enter Log Number",1);
	ret=lk_getalpha(4,0,cpuid,20,0,0);
	printf("cpuid =%s%d\n",cpuid,ret);
	if(ret >= 0)
	{
	sprintf(touch,"touch /mnt/tmp/%s.txt",cpuid);
	fprintf(stderr,"touch =%s\n",touch);
	system(touch);
	if(pos==1){
	sprintf(posm,"echo GL14POS AutoTest Log > /mnt/tmp/%s.txt",cpuid);
	system(posm);
	}
	if(pos==2){
	sprintf(posm,"echo GL14POS AutoTest Log > /mnt/tmp/%s.txt",cpuid);
	system(posm);
	}
	sprintf(echo,"echo Log Number %s >> /mnt/tmp/%s.txt",cpuid,cpuid);	
	system(echo);
	sprintf(unid,"echo uid of POS %s >>/mnt/tmp/%s.txt",buff,cpuid);
	system(unid);
	
	sprintf(machineid,"echo machine id of POS %s >>/mnt/tmp/%s.txt",machid,cpuid);
	system(machineid);
	sprintf(hrwid,"echo hrwid of POS %s >>/mnt/tmp/%s.txt",hid,cpuid);
        system(hrwid);
	sprintf(mac,"echo machid of POS %s  >>/mnt/tmp/%s.txt",macid,cpuid);
        system(mac);	
	sprintf(imeicmd,"echo imei no of POS %s >>/mnt/tmp/%s.txt",imei,cpuid);
	system(imeicmd);
	sprintf(cmd,"cat /mnt/tmp/%s >> /mnt/tmp/%s.txt",autobuf,cpuid);
	system(cmd);
//	sprintf(rmcmd,"rm -rf /mnt/tmp/%s.txt",cpuid);
	system(rmcmd);
	}

	else
	{
	lk_dispclr();
	lk_disptext(2,2,"Log upload Failed",1);
	sleep(2);	
	}
return 0;
}

int log_time(struct tm *intim,char * tim,char *dat)
{
        struct timeval tv;
        gettimeofday (&tv,NULL) ;
        intim = gmtime (&tv.tv_sec) ;
        sprintf(tim,"%02d:%02d:%02d",intim->tm_hour,intim->tm_min,intim->tm_sec);
        sprintf(dat,"%02d:%02d:%04d",intim->tm_wday,intim->tm_mday, intim->tm_year+1900);

}

int  get_macid( char* macid )
   {
    int fd,i;
    char arr2[50]="";
	
    struct ifreq ifr;
    fd=socket(AF_INET,SOCK_DGRAM,0);
    ifr.ifr_addr.sa_family = AF_INET;
    strncpy(ifr.ifr_name, "eth0",IFNAMSIZ-1);
    ioctl(fd,SIOCGIFHWADDR,&ifr);
    close(fd);
    sprintf(macid,"%02x:%02x:%02x:%02x:%02x:%02x",(unsigned char)ifr.ifr_hwaddr.sa_data[0],
                                            (unsigned char)ifr.ifr_hwaddr.sa_data[1],
                                            (unsigned char)ifr.ifr_hwaddr.sa_data[2],
                                            (unsigned char)ifr.ifr_hwaddr.sa_data[3],
                                            (unsigned char)ifr.ifr_hwaddr.sa_data[4],
                                            (unsigned char)ifr.ifr_hwaddr.sa_data[5]);
    for(i=0;i<(sizeof(macid));i++)
    if(macid[i]==' ')
    macid[i]='0';
    sprintf(arr2,"MAC:%s",macid);
     return 0;
    }

int get_IMEI_number( char* imei)
      {
        int res,i;
        char response[256],flag=0;
        char *expect[32]={"OK","ERROR","READY",NULL};
        char *tmp;

        res=ModemOpen("/dev/ttymxc0");
        if(res<0)
        {
               fprintf(stderr,"Modem Open failed\n");
               return -1;
        }
        setmodemparams(9600);
        memset(response,0,256);
        res=Test_modem_response_without_signal("AT+CGSN\r\n",response,expect,10);
        fprintf(stderr,"The value of res=%d\n",res);

        for(i=0;i<strlen(response);i++)
        {
                if(response[i]<0x20)
                response[i]=0x20;
        else
        if(response[i]=='O'&&response[i+1]=='K')
        {
                 response[i]='\0';break;
        }
        }


        Modemclose();
        printf("Response of IMEI = %s\n",response);
	strcpy(imei,response+9);

        return 0;

}

int getmachid(char machid[])
{
        int i;
        FILE *fp;
	char buff[50]="";
        system("fw_printenv machineid > /tmp/id");
        fp=fopen("/tmp/id","r");
        fgets(buff,30,fp);
        for (i=0;i<10;i++)
        machid[i]=buff[10+i];

        machid[11]=0x00;
        fclose(fp);

}

 
