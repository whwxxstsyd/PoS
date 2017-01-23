#include<stdio.h>
#include<header.h>

char IPADDR[30]="";
static int n=10;
int ip_chk();

wifi()
{
	char buff1[250]="",str[250]="";
	lk_dispclr();
	char buff[250]="";
	int fd ,n,ret,opt=0;
printf("Inside wifi function.....\n");	                      
        MENU_T menu;                    
        int selItem  = 0;               
        int acceptKbdEvents = TRUE;     
        int maxEntries = 0;             
                                        
        menu.start                      =       0;
        menu.maxEntries                 =       3;
        maxEntries                      =       menu.maxEntries;
        strcpy(menu.title, "WI-FI MENU");
        strcpy(menu.menu[0],"module_test" );
        strcpy(menu.menu[1],"connect" );
        strcpy(menu.menu[2],"ping" );  
        while(1){                       
                opt = scroll_menu(&menu,&selItem,acceptKbdEvents);               
                switch(opt){
                        case CANCEL:
			        wifi_close();
				return 0;
                        case ENTER:
                        case 1: case 2: case 3:
                        switch (selItem+1){
			case 1: module_test();
				break;
			case 2 : connect_test();
	//Calling Main 
	printf("Calling main function to return to main menu...\n");
	main();	
				 break; 



			case 3:ping_test();
				break;
				

		}
	}
	}
	//Calling Main 
	printf("Calling main function to return to main menu...\n");
	main();	
}

int wifi_close()
{
	char str3[250]="";
	int fd,ret;
        fd = open("/sys/class/net/ra0/operstate",O_RDONLY);
        if(fd<0)
		return -1;
	read(fd,str3,25);
        ret=memcmp(str3,"down",4);
	if (ret==0)
		return 0;
	else
		wifi_disconnect();	
	return 0;		
}


int module_test()
	{	
	int fd,n;
	char buff[250]="";
	fd = open("/sys/class/net/ra0/address",O_RDONLY);
	if(fd<0){
		lk_dispclr();
		lk_disptext(2,3,"WI-FI NETWORK DEVICE IS NOT DETECTED ",0);
		lk_disptext(5,0,"Enter any Key TO EXIT ",0);
		lk_getkey();
		return -1;
	}else
	{
		lk_dispclr();
		lk_disptext(2,3,"WI-FI NETWORK DEVICE is up ",0);
	}
	n=read(fd,buff,50);
	printf("WLAN MAC ADDRESS=%s",buff);
	if(n<0)
	{
		lk_dispclr();
		lk_disptext(1,0,(unsigned char *)"WLAN NOT MAC ADDRESS:",0);
	}

	else
	{
		lk_dispclr();
		lk_disptext(1,0,"WIFI DEVICE DETECTED",0);
		lk_disptext(2,0,(unsigned char *)"WLAN MAC ADDRESS:",0);
		lk_disptext(3,0,(unsigned char *)buff,0);
	}	
        lk_disptext(5,0,"Enter any Key TO EXIT ",0);
        lk_getkey();	
	return 0;
	
	}
	
	
void wakeup(int sig_num)
{
	if(n==10)
	{
 		wifi_disconnect();
	//	return -1;
	}
//	return 0;
}





int connect_test()
{
	int opt,fp;
	char buff1[250]="",str[250]="",str1[2550]="";
	struct stat buf;
	char *ptr=NULL;
	char file[]="/mnt/jffs2/ra0.txt";
	system("iwlist ra0 scan");

	lk_dispclr();

	lk_disptext(1,3,"1.for VISIONTEKR&D",0);
	lk_disptext(2,3,"2.for Wireless",0);

	while(1)
	{
		opt=lk_getkey();
		if(opt == 1) {  strcpy(buff1,"VISIONTEKR&D"); break;}
		else if ( opt == 2) {  strcpy(buff1,"Linksys01877"); break;}
		else if(opt == CANCEL )  break ;
	}

	lk_dispclr();
	lk_disptext(2,2,"Enter your class name ",0);

	opt=lk_getalpha(4,0,buff1,19,strlen(buff1),1);

	sprintf(str,"iwconfig ra0 essid \"%s\"",buff1);
	printf("str=%s\n",str);
	system(str);
	n=10;
	lk_dispclr();
	lk_disptext(2,0,"trying to get ip...",0);
//	system("udhcpc --interface=wlan0");
                signal(SIGALRM,wakeup);
		alarm(10);
            	n=system("udhcpc --interface=ra0 > /mnt/jffs2/interface.txt");
		alarm(0);

               // strcpy(file,"/mnt/jffs2/interface.txt");
		memset(str1,0,250);
                fp=open("/mnt/jffs2/interface.txt",O_RDONLY);
                if(fp<0)
		{
			printf("file is not opend");
                        return -1;
		}
              // str1=(char*)malloc(buf.st_size*sizeof(char));
                read(fp,str1,250);

		printf("srt1=--------------------%s\n",str1);
                ptr=strstr(str1,"obtained");
                if(ptr!=NULL)
                {
                        lk_dispclr();
                        lk_disptext(2,3,(unsigned char*)"N/W Established",1);
                        lk_disptext(5,0,"Enter Any key to EXit",0);
			lk_getkey();
	printf("Done n/w established...\n");
                        
                }
                else
                {
                        lk_dispclr();
                        lk_disptext(2,0,(unsigned char*)"Problem while",0);
                        lk_disptext(3,3,(unsigned char*)"Getting Ip",0);
                        lk_disptext(5,3,"Enter Any key to EXit",0);
                        lk_getkey();
                  //      wifi_disconnect();
                        return ERROR;
                }
	
	
	return 0;
}

int wifi_disconnect()
{
        char p_id[8];
        char str[50]="";
        int fd9;

        printf("\n Closing Wifi \n");

        lk_dispclr();
        lk_disptext(2,0,(unsigned char*)"Disconnecting .....",1);
        sleep(1);

        system("ifconfig ra0 down");

        system("pidof udhcpc > /mnt/jffs2/kill.txt");
        fd9 = open ("/mnt/jffs2/kill.txt", O_RDONLY);
        if (fd9 >= 0)
        {
                read (fd9, p_id, 4);
                p_id[4] = '\0';
                sprintf (str, "kill -9 %s", p_id);
                printf ("\n%s\n", str);
                system (str);
                close (fd9);
        }
        usleep(20);
        lk_dispclr();
        lk_disptext(2,0,(unsigned char*)"Disconnected",1);
	system("rm /mnt/jffs2/interface.txt");
	system("rm /mnt/jffs2/kill.txt");
	
        sleep(1);

return SUCCESS;
}




int ping_test()
     {
       FILE *fp;
       char a,b,c;
       int i,ret=0;
       char ipaddr[80]="",dest1[30]="10.10.1.1";
       while(1)
        {


                memset(IPADDR,0,30);
                strcpy(IPADDR,dest1);
                lk_dispclr();
                lk_disptext(2,2,(unsigned char*)"Enter IP to Png",0);
                ret =  lk_getalpha(4,0,IPADDR,15,strlen(dest1),0);
                if (ret < 0)
                return;




          if(!ip_chk_t())
          break;

          else
           {
             lk_dispclr();
             lk_disptext(3,2,"TRY AGAIN",1);
             printf("Enter Valid Address\n");
             if(lk_getkey()==CANCEL)
             return -1;
          }
      }
      lk_dispclr();
      lk_disptext(2,4,"Pnging Status",0);
      sprintf(ipaddr,"ping -c 2 %s | grep loss > /tmp/png_file",IPADDR);
      system(ipaddr);


      fp = fopen("/tmp/png_file","r");
      for(i=0;i<60;i++)
        {
          b=a;
          a=c;
          c=fgetc(fp);
             if(c=='%')
              {
               lk_dispclr();
                if((a=='0') && (b==' '))
                 {
                  lk_disptext(3,3,"System is Alive",0);
                  printf("System is Alive\n");
                 }
               else
                {
                  lk_disptext(3,3,"System is Dead",0);
                  printf("\nSystem is Dead\n");
                }
               break;

            }
        }
         fclose(fp);
         remove("/tmp/png_file");
         lk_getkey();
                         	
        return 0;
 }



int ip_chk_t()
{
        char k=0,flag=0,len=0,cnt=0;
        char str[30]="";
        int chk[10],val=0,l=0,i,j=0;
        chk[0]=-1;
                memset(str,0,30);
                strcpy(str,IPADDR);
                len=strlen(str);
                if( (len < 7) || (len > 15) || (str [0]=='.') ){
                        flag=1;
                        printf("1.notvalid\n");
                }
                else{
                        for(i=0,j=0,flag=0;i<len;i++){
                                if( ((str[i]<'0') || (str[i]>'9')) && (str[i]!='.') ){
                                        flag=1;
                                        printf("2.Not valid\n");
                                        break;
                                }
                                else if(str[i]=='.'){
                                        j++;
                                        chk[j]=i;
                                }
                        }
                }
                if(flag==0 && j==3){
                        chk[4]=len;
                        for(i=0,val=0,l=0;i<4;i++){
                                cnt = chk[i+1]-chk[i];
                                k=chk[i+1];
                                if( cnt < 2  || cnt > 4 ){
                                        flag=1;
                                        break;
                                }
                                switch(cnt){
                                        case 2:
                                                val = (str[k-1]-48);
                                                if(i==0 && val==0)
                                                        flag=1;
                                                break;
                                        case 3:
                                                l = 10*(str[k-2]-48);
                                                if(l==0)
                                                        flag=1;
                                                else
                                                        val=l+ (str[k-1]-48);
                                                break;
                                        case 4:
                                                l= 100*(str[k-3]-48);
                                                if(l==0)
                                                        flag=1;
                                                else
                                                        val=l+10*(str[k-2]-48)+(str[k-1]-48);
                                }     
                           if(val<0 || val >255)
                                flag=1;
                        }
                }
                if(flag==0 && j==3)
                        return 0;
                else
                        return -1;
}

