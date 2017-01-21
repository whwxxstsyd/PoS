#include <header.h>


int Communication()
{
        int opt=0;
        MENU_T menu;
        int selItem  = 0;
        int acceptKbdEvents = TRUE;
        int maxEntries = 0;
	int ret;
        menu.start                      =       0;
        menu.maxEntries                 =       3;
        maxEntries                      =       menu.maxEntries;
        strcpy(menu.title, "Communation ");
        strcpy(menu.menu[0],"Ethernet" );
        strcpy(menu.menu[1],"Gsm/Gprs" );
	strcpy(menu.menu[2],"WI-FI" );
        while(1){
                opt = scroll_menu(&menu,&selItem,acceptKbdEvents);
                switch(opt){
                	case CANCEL:
                       		return 0;
                  	case ENTER:
                  	case 1: case 2: case 3:
                        switch (selItem+1){
                        	case 1:
                               		lk_dispclr();
                                   	ethernet();
                                 	break;
				case 3:
					lk_dispclr();
					lk_disptext(2,1,"Waiting for",0);
					lk_disptext(3,3,"enabling...",0);
					ret=wifi_enable();
					if(ret!=0){
						printf("wi_fi enable not success\n");
						lk_disptext(2,1,"wi_fi enable",0);
						lk_disptext(3,5,"not success",0);
						break;
					}
					wifi();
					ret=wifi_disable();
					if(ret!=0){
						printf("wi_fi disable not success\n");
						lk_disptext(2,1,"wi_fi disable",0);
						lk_disptext(3,5,"not success",0);
						break;
					}
					break;
                        	case 2:
					menu.start 	= 0;
					menu.maxEntries = 2;
					maxEntries      = menu.maxEntries;
					strcpy(menu.title,"SIM Selection");
					strcpy(menu.menu[0],"SIM1(Lower)");
					strcpy(menu.menu[1],"SIM2(Upper)");
					while(1){
					opt = scroll_menu(&menu,&selItem,acceptKbdEvents);
                			switch(opt){
                        		case CANCEL:    
                                		return 0;
                       			 case ENTER:     
                        			case 1: case 2: 
                        		switch (selItem+1){
                                		case 1:
                                        	lk_dispclr();
					system("sim1_enable");	
                                		gsm_gprs();
                                        	break;
					 	case 2:
						lk_dispclr();
					system("sim2_enable");

						gsm_gprs();
						break;

	
				}
				}
				}		

			}
                  default : break;
                }
        }
	  
}




/*
int  wifiping(void)

{
lk_dispclr();
char buff[250]="";
int fd ,n,ret ;


fd = open("/sys/class/net/wlan0/address",O_RDONLY);
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
	
		

close(fd);
	
return 0 ;
}*/

