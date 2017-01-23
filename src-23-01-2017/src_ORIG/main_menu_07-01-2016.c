
#include<stdio.h>
#include<stdlib.h>
#include<header.h>
#include<X6x8.h>
/***********************************************************************************************
                        MAIN MENU FOR HHT SELF-DIAGNOSTICS 

***********************************************************************************************/               
char autobuf[80];
unsigned char pos=0;
static int module=0;
//FILE *outfp ;


int main (void)
{
 struct tm intim;

        MENU_T menu;
        int opt=0,ret;
        int selItem  = 0;
        int acceptKbdEvents=0;
        int key=0,max_cnt=6,count=0;
        unsigned char data[10];
        unsigned int manualflag=2;
        unsigned int ramdisk_type;
        int event;

	char buff[80]="";

//	prn_open() ;	
	lk_open();
	mscr_open();
	lk_dispclr();
	lk_dispfont(&(X6x8_bits[0]),6) ;

	lk_lcdintensity(24);

//  if((outfp=freopen("OUT", "w" ,stdout))==NULL) {
//    printf("Cannot open file.\n");
//    exit(1);
//  }


	lk_disptext(0,0,"IOCL Petrol Bunk Demo",1);
	lk_disptext(2,0,"HiTec City,Hyd-81",0); 
	lk_disptext(3,0,"Powered By ValueLabs V1.0",0);  
	lk_disptext(4,0,"  F1   F2   F3   F4",0);   
	lk_dispbutton("Home","Up  ","Down","End ");
	lk_buzzer(2);

	sprintf(autobuf,"%s-%02d%02d%02d%02d%02d%04d.txt",buff,intim.tm_hour,intim.tm_min,intim.tm_sec,intim.tm_mday,intim.tm_mon+1,intim.tm_year+1900);

	while(1)
	{	
	int key1=lk_getkey();
		if(key1!=0xff)
			break;
	}

		
	lk_dispclr();

        menu.start                      = 0;
        menu.maxEntries                 = 21;
	                                                                              
	strcpy(menu.title,"MAIN MENU");       
        //strcpy(menu.menu[0],"LCD");
        strcpy(menu.menu[0],"IOCL Petrol Bunk Demo");
        strcpy(menu.menu[1],"Keypad");
        strcpy(menu.menu[2],"Printer");
        strcpy(menu.menu[3],"Date & Time");
        strcpy(menu.menu[4],"Battery");
        strcpy(menu.menu[5],"USB Host");
        strcpy(menu.menu[6],"Machine Id");
        strcpy(menu.menu[7],"JFFS2");
        strcpy(menu.menu[8],"Software Details");
        strcpy(menu.menu[9],"RFID");
	strcpy(menu.menu[10],"IFD");
        strcpy(menu.menu[11],"SAM");
        strcpy(menu.menu[12],"Magnetic Head" );
	strcpy(menu.menu[13],"Audio");
	strcpy(menu.menu[14],"Communication");
	strcpy(menu.menu[15],"MicroSD Card");
	strcpy(menu.menu[16],"Ir");
	strcpy(menu.menu[17],"Download");
	strcpy(menu.menu[18],"console");
	strcpy(menu.menu[19],"Shutdown");
	strcpy(menu.menu[20],"Bash");
	while(1){
          
        	lk_dispclr();
               	opt = scroll_menu(&menu,&selItem,acceptKbdEvents);
		switch(opt){
			case CANCEL:
				break;
                  
                   	case ENTER:

                		switch (selItem+1){
                    
                   		        //case 1: Display (manualflag);	         break;
                   		        case 1: Display_new (manualflag);	         break;
                        		case 2: Keypad_test (manualflag);	         break;
                        		case 3: Printer_test (manualflag);	         break;
                        		case 4:	Setup_menu (manualflag);         break;
                        		case 5: Battery (manualflag);	         break;
					case 6: usb_test(manualflag );		 break;
					case 7:Machineid (manualflag);	         break;
                        		case 8:	jffs2_test(manualflag);	         break;
                       	 		case 9:versioninfo(manualflag);          break;
                                        case 10:rfid_test (manualflag);          break;
					case 11: Ifd_test (manualflag);		 break;
					case 12: sam_test (manualflag);          break;
					case 13: MagHead_test(manualflag);       break;
					case 14: audio_test(manualflag);          break;

					case 15:Communication (manualflag);      break;
					case 16:sdcard (manualflag);	         break;
					case 17:Ir (manualflag);	         break;
					case 18: Download_menu ();		 break;
					case 19:Console_menu();	                 break;



				case 20:
                                 lk_dispclr();
                                 lk_disptext(1,4,"Do You Want         to Shutdown ?",1);
                                 lk_disptext(5,0,"ENTER->YES      X->NO",0);

                                while (1)
                                {
                                 ret=lk_getkey();

                                if(ret==ENTER)
                                {
                                 lk_dispclr();
                                 lk_disptext(3,1,"Please wait..",1);
  //                               prn_close();  // closing printer
                                 lk_close();   // closing pinpad
				 mscr_close();

                                 system("poweroff");
                                 }

                                else if (ret==CANCEL)
                                break;
                                }

                                break;
				 case 21:
                                	lk_dispclr();
                                	lk_disptext(2,1,"Bash Prompt",1);
    //                            	prn_close();  // closing printer
                                	lk_close();   // closing pinpad
                                	exit (0);
                                	return SUCCESS;
                                break;

                  		} 
          		default:
				
				   break;
          
         	}
	}
        return 0; 
}

extern char autobuf[];
void Display_new(void)
{
                 struct tm intim;

                char buff[150]="";
                int cnt=1;
                int ret=0;
                 lk_getrtc(&intim);

        sprintf(autobuf,"%s-%02d%02d%02d%02d%02d%04d.txt",buff,intim.tm_hour,intim.tm_min,intim.tm_sec,intim.tm_mday,intim.tm_mon+1,intim.tm_year+1900);

                while(1)
                {
			ret=lk_getkey();
	        	if(ret==CANCEL)
	        	main();
                lk_dispclr();
                lk_disptext(1,2,"1.....PETROL",0);
                lk_disptext(2,2, "2.....DIESEL",0);
                lk_disptext(5,2, "Press 1 or 2",0);
						char cpuid[20]="";
						ret=lk_getalpha(3,0,cpuid,20,0,0);	
						printf("cpuid =%s%d\n",cpuid,ret);
//                ret=lk_getkey();
                if(ret==1||ret==2)
                break;
		}

                if(ret==1 || ret==2)
                {
                memset(buff,0,150);
                sprintf(buff,"echo \"-----Continuous Auto Test Log -------\" >>  /mnt/tmp/%s",autobuf);
                system(buff);
//                lk_dispclr();
                //lk_disptext(1,2,"Entering Auto",1); 
                //lk_disptext(3,2, "Testing Mode",1);
                //sleep(1);
		
			 while(1){
		                ret=lk_getkey();
		                if(ret==CANCEL)
		                break;
		                switch(ret){

		                        case 1:	//auto_lcd_new();
		                        case 2:	//auto_lcd_new();
		                                //auto_update("Lcd",0);
					while(1)
					{	
						lk_dispclr();
						lk_disptext(2,2,"DU No :",1);
						//lk_dispfill();
						char cpuid[20]="";
						ret=lk_getalpha(4,0,cpuid,20,0,0);	
						printf("cpuid =%s%d\n",cpuid,ret);
						
//						ret=lk_getkey();
                				if(ret>=1)
						{				                			
							nozzle(ret);	
						//sleep(1);
						}
		                         }
					       break;
					default: break;
					
		                  }

		        }//while        
		}
}

void nozzle(int a)
{
	int ret=0;
	while(1)
	{
	lk_dispclr();
        lk_disptext(2,2,"Nozzle No :",1);
        //lk_dispfill();
	
	char cpuid[20]="";
        ret=lk_getalpha(4,0,cpuid,20,0,0);
        printf("cpuid =%s%d\n",cpuid,ret);
//	ret=lk_getkey();
        if(ret>=1)
        break;
        }
                             /*sleep(1);
                                                char cpuid[20]="";
                                                ret=lk_getalpha(4,0,cpuid,20,0,0);      
              printf("cpuid =%s%d\n",cpuid,ret);*/
           //sleep(1);
	du_staff();
        
	

	//sleep(1);	
}

void du_staff(void)
{
	int ret=0;
	while(1)
        {
		lk_dispclr();
        	lk_disptext(2,2,"DU Staff :",1);
        //lk_dispfill();

        char cpuid[20]="";
        ret=lk_getalpha(4,0,cpuid,20,0,0);
        printf("cpuid =%s%d\n",cpuid,ret);
//		ret=lk_getkey();
        if(ret>=1)
        break;	
	}
		vehicle();
		
}

void vehicle(void)
{
struct tm intim;

                char buff[150]="";
                int cnt=1;
                int ret=0;
                 lk_getrtc(&intim);

        sprintf(autobuf,"%s-%02d%02d%02d%02d%02d%04d.txt",buff,intim.tm_hour,intim.tm_min,intim.tm_sec,intim.tm_mday,intim.tm_mon+1,intim.tm_year+1900);

                while(1)
                {
                lk_dispclr();
                lk_disptext(1,2,"1.....BIKE",0);
                lk_disptext(2,2,"2.....CAR",0);
                lk_disptext(3,2,"3.....AUTO",0);
                lk_disptext(9,2,"Select Vehicle Type",0);
               // ret=lk_getkey();
                //if(ret==1||ret==2||ret==3||ret==4)
                //break;
                

        char cpuid[20]="";
        ret=lk_getalpha(4,0,cpuid,20,0,0);
        printf("cpuid =%s%d\n",cpuid,ret);
	//sleep(2);	
		if(ret>=1)
			break;
		}
	switch(ret)
	{
		case 1: 
			break;
		case 2:
			break;
		case 3:
			break;
		default:
			break;
	}
	
	bill_type();	
}

void bill_type(void)
{
	struct tm intim;
	char buff[150]="";
                int cnt=1;
                int ret=0;
                 lk_getrtc(&intim);

        sprintf(autobuf,"%s-%02d%02d%02d%02d%02d%04d.txt",buff,intim.tm_hour,intim.tm_min,intim.tm_sec,intim.tm_mday,intim.tm_mon+1,intim.tm_year+1900);

                while(1)
                {
                lk_dispclr();
                lk_disptext(1,2,"1.....CASH",0);
                lk_disptext(2,2, "2.....CREDIT",0);
                lk_disptext(3,2, "Press 1 or 2",0);
               // ret=lk_getkey();
                /*if(ret==1||ret==2)
                break;*/
                
	char cpuid[20]="";
        ret=lk_getalpha(4,0,cpuid,20,0,0);
        printf("cpuid =%s%d\n",cpuid,ret);
        //sleep(2);
		
		if(ret==1 || ret==2)
		break;
		}
			Display_new();
		
	
}


