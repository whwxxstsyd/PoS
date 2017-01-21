#include<header.h>

#define ERROR -1
#define SUCCESS 0

typedef struct {
                 char phnum[32];
                 char apnnum[32];
                 char username[32];
                 char password[32];
                 char timeout[8];
                 char command[32];
		 char command1[32];
               } GPRS_SET;


char gprsip[50]="";
 
char sim_status=0; // sim status flag


extern char str5[20],str6[20];
extern int tr;

int gsm_gprs() // Gsm-Gprs Main Menu
{	


	int opt=0,ret;
	static int gsm = 1;
	MENU_T menu;
	char event;
    
	int selItem  = 0;
	int acceptKbdEvents = TRUE;
	int maxEntries = 0;
	short scroll = 0;
	GPRS_SET gprs_settings;

	sim_status=sim_status_test();          // sim status checking
               

	menu.start                      =       0;
	menu.maxEntries                 =       7;
	maxEntries                      =       menu.maxEntries;

	strcpy(menu.title, "GSM/GPRS tests");
	strcpy(menu.menu[0],"GSM Test" );
	strcpy(menu.menu[1],"GPRS NW Register" );
	strcpy(menu.menu[2],"AT Commands" );
	strcpy(menu.menu[3],"APN" );
	strcpy(menu.menu[4],"GPRS Dial Number" );
	strcpy(menu.menu[5],"GPRS Timeout" );
	strcpy(menu.menu[6],"GPRS Test" );
	memset(&gprs_settings,0,sizeof(gprs_settings));


	while(1)
	{
		opt = scroll_menu(&menu,&selItem,acceptKbdEvents);

		switch(opt)
		{
			case CANCEL:
				return;
			case ENTER:
				case 1: case 2: case 3: case 4: case 5: case 6: case 7:
				switch (selItem+1)
				{
					case 1:
						gsm_test();
					        break;
					case 2:
					if(sim_status)
					{
						fprintf(stderr,"SIM IS NOT PRESENT\n");
						lk_dispclr();
						lk_disptext(2,3,"SIM NOT PRESENT",1);
						lk_getkey();  
					}
                                     	else
						gprs_registration();
						break;
				case 3:
					AT_commands(&gprs_settings);
					break;
				case 4:
					APN_enter(&gprs_settings);
					break;
				case 5:
					GPRS_dial(&gprs_settings);
					break;
				case 6:
					GPRS_timeout(&gprs_settings);
					break;
				case 7:
                                	if(sim_status)
					{
						fprintf(stderr,"SIM IS NOT PRESENT\n");
						lk_dispclr();
						lk_disptext(2,3,"SIM NOT PRESENT",1);
						lk_getkey(); 
					}
                            
					else
						GPRS_test(&gprs_settings);
						break;

				}
			default : break;

		}
	}
}




 int gsm_test (void)
  {
	int opt=0;
	MENU_T menu;
        char event;
        int selItem  = 0;
        int acceptKbdEvents = TRUE;
        int maxEntries = 0;
        short scroll = 0;

        menu.start                      =       0;
        menu.maxEntries                 =       5;
        maxEntries                      =       menu.maxEntries;

        strcpy(menu.title, "GSM test");

        strcpy(menu.menu[0],"GSM Model Identity" );
        strcpy(menu.menu[1],"IMEI Number");
        strcpy(menu.menu[2],"SIM Status Test" );
        strcpy(menu.menu[3],"NW Registration" );
        strcpy(menu.menu[4],"NW Signal Strength" );
//        strcpy(menu.menu[5],"Voice call");

        while(1)
        {
                opt = scroll_menu(&menu,&selItem,acceptKbdEvents);
                switch(opt)
                 {
                   case CANCEL:
                     return;
                  
                   case ENTER:
                     
                     case 1: case 2: case 3: case 4: case 5:
                         switch (selItem+1)
                            {

                              case 1:

                                     gsm_model_identification();
                                     break;

                              case 2:

                                     enter_IMEI_number();
                                     break;

                              case 3:

                                     lk_dispclr();
                                     if(sim_status)
                                     {
                                      fprintf(stderr,"SIM IS NOT PRESENT\n");
                                      lk_disptext(2,3,"SIM NOT PRESENT",1);
                                       
                                     }

                                     else
                                      {
                                      fprintf(stderr,"SIM IS PRESENT\n");
                                      lk_disptext(2,4,"SIM PRESENT",1);
                                      }
                                     
                                     lk_getkey();                                     
                             
                                     break;
     
                              case 4:

                                     
                                     if(sim_status)
                                     {
                                      fprintf(stderr,"SIM IS NOT PRESENT\n");
                                      lk_dispclr();
                                      lk_disptext(2,3,"SIM NOT PRESENT",1);
                                      lk_getkey();
                                     }

                                     else
                                       NW_registration();

                                     break;

                               case 5:
                                     if(sim_status)
                                     {
                                      fprintf(stderr,"SIM IS NOT PRESENT\n");
                                      lk_dispclr();
                                      lk_disptext(2,3,"SIM NOT PRESENT",1);
                                      lk_getkey();
                                     }

                                     else
                                       NW_signal_strength();
                                      break;
                              // case 6:
                                //      voice_test();
                                  //    break;









                        }
                 }
        }
return 0;

}

  int gsm_model_identification()
   {
        int res,i;
        char response[256];
        char *expect[32]={"OK","ERROR","READY",NULL};

        res=ModemOpen("/dev/ttymxc0");
         if(res<0)
         {
            fprintf(stderr,"Modem Open failed\n");
            return ERROR; 
         }
        setmodemparams(9600);
        memset(response,0,256);
        res=Test_modem_response_without_signal("AT+GMR\r\n",response,expect,10);
        fprintf(stderr,"The value of res=%d\n",res);

        printf("Response of GSM Check Model =%s\n",response);
        for(i=0;i<strlen(response);i++){
         if(response[i]<0x20)
           response[i]=0x20;
         else if(response[i]=='O'&&response[i+1]=='K'){
          response[i]='\0';break;
         }
        }
       
        Modemclose(); 
        lk_dispclr();
        lk_disptext(1,2,"GSM MODEL NUMBER",1);
        lk_disptext(3,0,response+6,0);
        lk_disptext(5,4,"Press Any Key To Continue",0);
        lk_getkey();

        return 0;
 }

  int enter_IMEI_number()
      {
        int res,i;
        char response[256],flag=0;
        char *expect[32]={"OK","ERROR","READY",NULL};
        char *tmp;

        res=ModemOpen("/dev/ttymxc0");
        if(res<0)
        {
               fprintf(stderr,"Modem Open failed\n");
               return ERROR;                
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
        lk_dispclr();
        lk_disptext(1,4,"IMEI NUMBER",1);
        lk_disptext(3,0,response+9,0);
        lk_disptext(5,4,"Press Any Key",0); 
        lk_getkey();

        return 0;
        
}



 int sim_status_test (void)
  {
        int res;
        char response[256];
        char *expect[32]={"READY","ERROR",NULL};

        res=ModemOpen("/dev/ttymxc0");
        if(res<0)
         {
                fprintf(stderr,"Modem Open failed\n");
                return ERROR;                
         }
        setmodemparams(9600);
        memset(response,0,256);
        res=Test_modem_response_without_signal("AT+CPIN?\r\n",response,expect,10);
        fprintf(stderr,"The value of res=%d\n",res);
        sleep(1); 

        printf("Response of GSM Sim = %s\n",response);

        Modemclose();

        if (res) return -1; // sim is not there
            
        else return 0;      // sim is present
         
       
    }

 int NW_registration()
  {
        int res,i;
        char response[256],flag=0;
        char *expect[32]={"OK","ERROR","READY",NULL};
        char *tmp;

        res=ModemOpen("/dev/ttymxc0");
        if(res<0)
        {
                fprintf(stderr,"Modem Open failed\n");
                return ERROR;
        }
       setmodemparams(9600);
       memset(response,0,256);
       res=Test_modem_response_without_signal("AT+CREG?\r\n",response,expect,10);
       fprintf(stderr,"The value of res=%d\n",res);
       sleep(1); 
       printf("Response = %s \n",response);

       Modemclose();

       if(strstr(response,"0,1"))
        {
          printf("\nNETWORK IS REGISTERED\n");
          lk_dispclr();
          lk_disptext(3,4,"NW REGISTERED",1);
        }

       else

        {
          printf("\nNETWORK NOT REGISTERED\n");
          lk_dispclr();
          lk_disptext(3,2,"NW NOT REGISTERED",1);
        }


       lk_disptext(5,4,"Press Any Key",0);
       lk_getkey();
       return 0;

    }


    int  NW_signal_strength()
    {
        int res,i,result;
        char response[256];
        char *expect[32]={"OK","ERROR","READY",NULL};
        char *c,num[7];


        res=ModemOpen("/dev/ttymxc0");
        if(res<0)
        {
                fprintf(stderr,"Modem Open failed\n");
                return ERROR;
        }
        setmodemparams(9600);
        memset(response,0,256);
        res=Test_modem_response_without_signal("AT+CSQ\r\n",response,expect,10);
        fprintf(stderr,"The value of res=%d\n",res);


        c=strstr(response,":");


        if(c!=NULL)
        {
                for(i=0;c[i]!=',';i++)
                {
                }


        num[0]=c[i-2];
        num[1]=c[i-1];
        num[2]='\0';
        result=atoi(num);
       if(result>=0 && result<=31)
        {
                lk_dispclr();
                lk_disptext(2,2,"NW SIGNAL STRENGTH",0);
                lk_disptext(3,6,num,1);
                lk_disptext(3,9,"db",1);
                lk_getkey();
        }
        else
        {
                lk_dispclr();
                lk_disptext(3,0,"BAD SIGNAL STRENGTH",1);
                lk_getkey();
        }
        }


        Modemclose();
        return 0;

   }



        int gprs_registration()
         {
           int res=0;
           char response[256],flag=0;
           char *expect[32]={"OK","ERROR","READY",NULL};


           res=ModemOpen("/dev/ttymxc0");
           if(res<0)
            {
             fprintf(stderr,"Modem Open failed\n");
              return ERROR;
            }
        
           setmodemparams(9600);
           memset(response,0,256);

           lk_dispclr();
           lk_disptext(2,5,"Checking...",1);

           res=Test_modem_response_without_signal("AT+CGATT=1\r\n",response,expect,10);

           res=Test_modem_response_without_signal("AT+CGDCONT=1\r\n",response,expect,10);

           res=Test_modem_response_without_signal("AT+CGREG?\r\n",response,expect,10);
 
           fprintf(stderr,"The value of res=%d\n",res);
           Modemclose();

           if(strstr(response,"0,1"))
            {
             printf("\nGPRS NETWORK IS REGISTERED\n");
             lk_dispclr();
             lk_disptext(2,3,"GPRS REGISTERED",1);
            }

          else
            {
             printf("\nGPRS NETWORK NOT REGISTERED\n");
             lk_dispclr();
             lk_disptext(3,1,"GPRS NOT REGISTERED",1);
            }


            lk_disptext(5,4,"Press Any Key",0);
            lk_getkey();
             return 0;
      }




        int AT_commands(GPRS_SET *settings)
         {
           int opt;
           int len=0;
	   char command[30] = "AT+CGDCONT=1";	
	 while(1)
	{
	  memset(settings->command1,0,30);

           strcpy(settings->command1,command);
           lk_dispclr();
           lk_disptext(2,2,"ENTER COMMAND",0);
           opt=lk_getalpha(4,0,settings->command1,30,strlen(command),0);


           if(opt<0)
           return -1;
           else
           return 0;
         }


	}
        int APN_enter(GPRS_SET *settings)
         {
           int opt;
           int len= 0 ;
           lk_dispclr();
           lk_disptext(2,2,"Press 1 For Airtel",0);
           lk_disptext(3,2,"Press 2 For Hutch",0);
           lk_disptext(4,2,"Press 3 For Idea",0); 
   
           while(1)
            {
              opt=lk_getkey();
                
              if(opt == 1) {  strcpy(settings->apnnum,"AIRTELGPRS.COM"); break;}
              else if ( opt == 2) {  strcpy(settings->apnnum,"www"); break;}
              else if ( opt == 3) {  strcpy(settings->apnnum,"internet"); break;}
              else if(opt == CANCEL )  break ; 
            }  
 
           lk_dispclr();
           lk_disptext(2,2,"Enter APN NO.",0);
//	   memset(settings->apnnum,0,30);

           opt=lk_getalpha(4,0,settings->apnnum,19,strlen(settings->apnnum),1);

           if(opt<0)
           return -1;

           else
           return 0;
      }


int GPRS_dial(GPRS_SET *settings)
{
        int opt;
        int len=0; 
        strcpy(settings->phnum,"*99***1#");
        lk_dispclr();
        lk_disptext(2,2,"Enter PHONE NO.",0);
        opt=lk_getalpha(4,0,settings->phnum,19,strlen(settings->phnum),1);
        if(opt<0)
        return -1;
        else
        return 0;
}



int GPRS_timeout(GPRS_SET *settings)
{
        int opt;
        int len=0; 
        strcpy(settings->timeout,"10");
        lk_dispclr();
        lk_disptext(2,2,"Enter TIMEOUT",0);
        opt=lk_getalpha(4,0,settings->timeout,19,strlen(settings->timeout),1);
        if(opt<0)
        return -1;
        else
        return 0;
}


     int GPRS_test(GPRS_SET *settings)
       {
        int conres,pppres;
        int res;

        ppp_options("1234","1234"); // username and passworrd
        conres=pppdial_gprs(settings->phnum);
  
        if(conres<0) return -1;
        conres=ppp_dial_update(settings->phnum,settings->apnnum);
        if(conres<0)
        {
          lk_dispclr();
          lk_disptext(2, 2, "GPRS not configred",0);
          lk_getkey();
          return -1;
        }


        pppres= gprs_ppp_test();


        if(pppres<0)
           return -1;
        else
          printf("success\n");
        return 0;
}

int gprs_ppp_test ( void )
 {
   lk_dispclr();
   lk_disptext(2,3,"Connecting PPP ",0);
   lk_disptext(3,3," Please Wait",1);
  
   if(ppp_open() < 0)
       {
         lk_dispclr();
         lk_disptext(2,0,"ISP Connection",0);
         lk_disptext(3,0,"Failed",0);
         lk_disptext(5,4,"Press Any Key",0);
         lk_getkey();
         return -1;
       }
                
        gett_ip();
       
        ppp_close();
        printf("\n PPP connected with IP %s\n",gprsip);
        lk_dispclr();
        lk_disptext(2,1,"GPRS CONN. SUCCESS",0);
        lk_disptext(3,1,"WITH ",0);
        lk_disptext(3,6,gprsip,0);
        lk_disptext(5,4,"Press Any Key",0);
        lk_getkey();
        return 0;
        }

   int gett_ip()
    {
      int fd;
      struct ifreq ifr;
      fd=socket(AF_INET,SOCK_DGRAM,0);
      ifr.ifr_addr.sa_family = AF_INET;
      strncpy(ifr.ifr_name,"ppp0",IFNAMSIZ-1);
      ioctl(fd,SIOCGIFADDR,&ifr);
      close(fd);
      sprintf(gprsip,"%d.%d.%d.%d",(unsigned char)ifr.ifr_addr.sa_data[2],
                                   (unsigned char)ifr.ifr_addr.sa_data[3],
                                   (unsigned char)ifr.ifr_addr.sa_data[4],
                                   (unsigned char)ifr.ifr_addr.sa_data[5],
                                   (unsigned char)ifr.ifr_addr.sa_data[6]);
     return 0;
   }



 int gsm_gprs_remote ()
  {
    int conres,pppres;
    int res;

    GPRS_SET gprs_settings;

    sim_status=sim_status_test();
                                                                                                                             
    if(sim_status)
     {
      
      fprintf(stderr,"SIM IS NOT PRESENT\n");
      lk_dispclr();
      lk_disptext(2,3,"SIM NOT PRESENT",1);
      lk_getkey();
      return -1;
    }


    APN_enter(&gprs_settings);
    GPRS_dial(&gprs_settings);
    GPRS_timeout(&gprs_settings);
 
                                                                                                                             
     ppp_options("1234","1234"); // username and passworrd
     conres=pppdial_gprs(gprs_settings.phnum);
                                                                                                                             
     if(conres<0) return -1;
     conres=ppp_dial_update(gprs_settings.phnum,gprs_settings.apnnum);
     if(conres<0)
       {
        lk_dispclr();
        lk_disptext(2, 2, "GPRS not configred",0);
        lk_getkey();
        return -1;
       }
                                                                                                                             
      if(ppp_open() < 0)
       {
         lk_dispclr();
         lk_disptext(2,0,"ISP Connection",0);
         lk_disptext(3,0,"Failed",0);
         lk_disptext(5,4,"Press Any Key",0);
         lk_getkey();
         return -1;
       }
   else
   ftpdown_ke_ra_ap();
   ppp_close();
   sleep(5);
                                                                                                                    
return 0;
 }

int curl_gprs_test(char *file_name)
{
        char http_url[]="http://209.85.153.104";        //www.google.com
        //char file_name[]="/mnt/jffs2/google.html";
        struct stat file_buf;
        unsigned char size[20];
        int ret=0;
                                                                                                    
                                                                                                    
        if (file_name==NULL)
                strcpy(file_name,"/mnt/jffs2/google.html");
        #ifdef  SERVER
                strcpy(http_url,SERVER);
        #endif
        lk_dispclr();
        lk_disptext(2,2,"Press Enter..To",0);
        lk_disptext(4,4,"Download ",1);
        ret=lk_getkey();
        if(ret==ENTER){
                printf("\n Downloading file from server\n");
                lk_dispclr();
                lk_disptext(2,2,"Downloading",1);
                lk_disptext(4,3,"Please wait....",0);
                sleep(2);
                GET_file_clear(http_url,file_name);
                lk_dispclr();
                lk_disptext(2,3,"Done",1);
                stat(file_name,&file_buf);
                sprintf(size,"filesize:%x",(unsigned int)file_buf.st_size);

   lk_disptext(5,2,size,0);
                sleep(2);
        }
        else{
                lk_dispclr();
                lk_disptext(2,2,"Download",1);
                lk_disptext(4,3,"quit....",0);
                sleep(2);
                return -1;
        }
        return 0;
                                                                                                    
}

