#include <header.h>
 
 enum comm_type{ETHERNET=1,GPRS}ctype; 
 int  Remote_test()
 {
	int opt=0,ret=0;
        MENU_T menu;
        int selItem  = 0;
        int acceptKbdEvents = TRUE;
        int maxEntries = 0;
                                                                                                                             
        menu.start                      =       0;
        menu.maxEntries                 =       2;
        maxEntries                      =       menu.maxEntries;
                                                                                                                             
                                                                                                                             
        strcpy(menu.title, "Remote download Menu");
        strcpy(menu.menu[0],"1.Ethernet" );
        strcpy(menu.menu[1],"2.GSM-GPRS");
                                                                                                                             
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
						ctype=ETHERNET;
                    				ethernet_remote();
                    				break;
              				case 2:
                     				lk_dispclr();
						ctype=GPRS;
                     				ret=gsm_gprs_remote();
						if(ret == -1)
							continue;
                     				break;
                 		}
			default: 
				break;
		}
	
	}  
                                 
	return 0;
} 

int ethernet_remote(void)
{
	set_ip();   
   	set_gateway();
 //  	ftpdown_ke_ra_ap(); 

	return 0; 
} 

int ftpdown_ke_ra_ap()
{
        int opt=0;
        MENU_T menu;
        int selItem  = 0;
        int acceptKbdEvents = TRUE;
        int maxEntries = 0;

        menu.start                      =       0;
        menu.maxEntries                 =       3;
        maxEntries                      =       menu.maxEntries;
                                                                                                                                                                                                                                                          
        lk_dispclr();
	strcpy(menu.title, "Remote Download");
        strcpy(menu.menu[0],"Linux Kernel");
        strcpy(menu.menu[1],"Ramdisk");
        strcpy(menu.menu[2],"Application");
                                                                                                                                                                                                                                                          
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
						if(ctype==1)
                                			Dwnd_ke_ra_ap(1);
						else if(ctype==2){
							chdir("/mnt/tmp");
		     					if(curl_gprs_test("kernel.img") < 0)
								return -1;
							system("/home/downloadkernel");
							lk_dispclr();
                                                        lk_disptext (3,2,"Reboot to Update",1);
                                                        lk_getkey();
						}
                               			break;
                        		case 2:
                                		lk_dispclr();
						if(ctype==1)
                                			Dwnd_ke_ra_ap(2);
						else if(ctype==2){
							chdir("/mnt/tmp");
		     					if(curl_gprs_test("ramdisk.img") <0 )
								return -1;
							system("/home/downloadramdisk");
							lk_dispclr();
                                                        lk_disptext (3,2,"Reboot to Update",1);
                                                        lk_getkey();
						}
                                		break;
                        		case 3:
                                		lk_dispclr();
						if(ctype==1)
                                			Dwnd_ke_ra_ap(3);
						else if(ctype==2){
							chdir("/mnt/tmp");
		     					if(curl_gprs_test("app.img")< 0)
								return -1;
							system("/home/downloadapplication");
							lk_dispclr();
							lk_disptext (3,2,"Reboot to Update",1);
					                lk_getkey();
						}
                                		break;
                        	}
                	default : break;
                }
        }
}

int Dwnd_ke_ra_ap(int arg)
{
	char load[100]="",str1[20]="",str2[20]="", str3[20]="", str4[20]="";
        char ip[20]="61.95.204.198",usrname[20]="sriram",passwd[20]="!@#$%^",fname[20]="app.img";
        struct stat file_buf;
        unsigned char size[20];

	lk_dispclr() ;
        lk_disptext (2,2,"Enter user name",0) ;
        lk_getalpha(4,0,usrname,13,strlen(usrname),1) ;
        strncpy(str1,usrname,13) ;
        lk_dispclr() ;
        lk_disptext (2,2,"Enter password",0) ;
        lk_getalpha(4,0,passwd,10,strlen(passwd),1) ;
        strncpy (str2,passwd,13) ;
        lk_dispclr() ;
        lk_disptext(2,2,"Enter Ftp IP",0);
        lk_getnumeric (4,0,ip,15,strlen(ip)) ;
        strncpy (str3,ip,15);

        system("rm -f /mnt/tmp/app.img");
        system("rm -f /mnt/tmp/ramdisk.img");
        system("rm -f /mnt/tmp/kernel.img");

        lk_dispclr ();
        if(arg==1){
        	lk_disptext (1,7,"KERNEL",1);  
           	lk_disptext (3,2,"Enter file name",0) ;
           	lk_getalpha (4,1,fname,20,strlen(fname),1) ;
           	strncpy (str4,fname,20);
           	sprintf (load,"ftpget -u %s -p %s %s /mnt/tmp/kernel.img %s",str1,str2,str3,str4);
           	printf("\n%s\n",load);
           	lk_dispclr() ;
           	lk_disptext (2,0,"Downloading ...",0);
           	system(load) ;
		stat("/mnt/tmp/kernel.img",&file_buf);
		sprintf(size,"file size:%x",(unsigned int)file_buf.st_size);
		lk_disptext(4,2,size,1);
		sleep(2);
           	lk_dispclr() ;
		if(file_buf.st_size >0 ){			
           		system ("/home/downloadkernel");
           		lk_disptext (0,1,"Download Completed",0) ;
           		lk_disptext (2,2,"Reboot to Update",0);
		}
		lk_disptext(4,3,"press any key",0);	
           	lk_getkey();

        }
        else if(arg==2){
        	lk_disptext (1,7,"RAMDISK",1);
           	lk_disptext (3,2,"Enter file name",0) ;
           	lk_getalpha (4,1,fname,13,0,1);
           	strncpy (str4,fname,13);
           	sprintf (load,"ftpget -u %s -p %s %s /mnt/tmp/ramdisk.img %s",str1,str2,str3,str4) ;
           	printf("\n%s\n",load);
           	lk_dispclr() ;
           	lk_disptext (2,0,"Downloading ...",0);
           	system(load) ;
		stat("/mnt/tmp/ramdisk.img",&file_buf);
		sprintf(size,"file size:%x",(unsigned int)file_buf.st_size);
		lk_disptext(4,2,size,1);
		sleep(2);
           	lk_dispclr() ;
		if(file_buf.st_size >0 ){
           		system ("/home/downloadramdisk");
           		lk_disptext (0,1,"Download Completed",0) ;
           		lk_disptext (2,2,"Reboot to Update",0);
		}
		lk_disptext(4,3,"press any key",0);
           	lk_getkey();
        }
        else if(arg==3)
        {
        	lk_disptext (1,5,"APPLICATION",1);
           	lk_disptext (3,2,"Enter file name",0) ;
           	lk_getalpha (4,1,fname,13,0,1);
           	strncpy (str4,fname,13);
           	sprintf (load,"ftpget -u %s -p %s %s /mnt/tmp/app.img %s",str1,str2,str3,str4);
           	printf("\n%s\n",load);
           	lk_dispclr() ;
           	lk_disptext (2,0,"Downloading...",0);
           	system(load) ;
		stat("/mnt/tmp/app.img",&file_buf);
		sprintf(size,"file size:%x",(unsigned int)file_buf.st_size);
		lk_disptext(4,2,size,1);
		sleep(2);
           	lk_dispclr() ;
		if(file_buf.st_size >0 ){
           		system ("/home/downloadapplication");
           		lk_disptext (0,1,"Download Completed",0) ;
           		lk_disptext (2,2,"Reboot to Update",0);
		}
		lk_disptext(4,3,"press any key",0);
           	lk_getkey();
        } 
        return 0 ;
}

