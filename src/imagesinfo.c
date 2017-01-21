#include <header.h>

int kernel_details(char *data);
int rootfs_details(char *data );
int bootloader_details(char *data);


int kernel_details (char *data)
{
        int fp,i;
        char buff[65]="";
        fp=open("/dev/mtd1",O_RDONLY);
	
        if ( 64 != read(fp,buff,64))
        return -1;

        for (i=0;i<32;i++)
        {
                 buff[i]=buff[32+i];
                 if(buff[32+i]==0x00)
                 break;
        }
        close(fp);

	strcpy(data,buff);

	

	/*
        lk_dispclr();
        lk_disptext(2,2,"KERNEL DETAILS",0);
        lk_disptext(4,0,buff,0); */
        return 0;
}

int rootfs_details(char *data)
{
	FILE *fp;
	int i,j;
	char buff[80]="";
	char buf[80]="";
	
	fp=fopen("/etc/rc.d/rc.local","r");

        while((fgets(buff,80,fp)!=NULL))
        {
        if( strstr(buff,"GL14-RD")!= NULL)
                break;
        }
        for (i=0;i<strlen(buff);i++)
                if(buff[i]==0x22)
                break;
        i++;
        for (j=0;j<strlen(buff);j++,i++)
        {
          if(buff[i]==0x22)
                {
                        buf[i]=0x00;
                        break;
                }
          else
                buf[j]=buff[i];
        }
        fclose(fp);

	strcpy(data,buf);

	/*
	lk_dispclr();
        lk_disptext(2,0,"Rootfs Details",0);
        if (strlen(buf)!=0x00)
        lk_disptext(4,0,buf,0);
        else
        lk_disptext(2,2,"Unknown Ramdisk",0);
        */

	return 0;
}

int bootloader_details( char *data)
{
	FILE *fp;
	char buff[80]="";
	int i;

	system("fw_printenv ver > /tmp/ver");

	fp=fopen("/tmp/ver","r");

	fgets(buff,80,fp);

	if (fp==NULL || strlen(buff)==0 )
	return -1;

	fclose(fp);
	remove ("/tmp/ver");

	for (i=0;i<strlen(buff)-5;i++)
	data[i]=buff[i+4];
	return 0;

	
}








