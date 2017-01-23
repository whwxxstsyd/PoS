
#include<stdio.h>
#include<stdlib.h>
#include<header.h>
#include<X6x8.h>
/***********************************************************************************************
                        MAIN MENU FOR HHT SELF-DIAGNOSTICS 

***********************************************************************************************/               
char autobuf[80];
//unsigned char pos=0;
static int module=0;

struct pos_details
{
	char fuel_type[10];
	char du_no[10];
	char nozzel_no[10];
	char du_staff[10];
	char vehicle_type[20];
	char bill_type[20];
	char vehicle_no[15];
	char mobile_no[15];
	char quantity_lt[10];
	char amount[10];
};
struct pos_details pos;

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
			if(ret==1)
				strcpy(pos.fuel_type,"PETROL\0");
			else
				strcpy(pos.fuel_type,"DIESEL\0");
		printf("FUEL TYPE: %s\n",pos.fuel_type);
				
                memset(buff,0,150);
                sprintf(buff,"echo \"-----Continuous Auto Test Log -------\" >>  /mnt/tmp/%s",autobuf);
                system(buff);
//                lk_dispclr();
                //lk_disptext(1,2,"Entering Auto",1); 
                //lk_disptext(3,2, "Testing Mode",1);
                //sleep(1);
		
			 while(1){
		              //  ret=lk_getkey();
		                //if(ret==CANCEL)
		                //break;
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
						ret=lk_getalpha(4,1,cpuid,20,0,0);	
						printf("cpuid =%s%d\n",cpuid,ret);
						strcpy(pos.du_no,cpuid);
						printf("DU No :	%s\n",pos.du_no);
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
	
	char cpuid[20]="";
        ret=lk_getalpha(4,1,cpuid,20,0,0);
        printf("cpuid =%s%d\n",cpuid,ret);
	strcpy(pos.nozzel_no,cpuid);
	printf("Nozzel No : %s\n",pos.nozzel_no);
//	ret=lk_getkey();
        if(ret>=1)
        break;
        }
                             /*sleep(1);
                                                char cpuid[20]="";
                                                ret=lk_getalpha(4,0,cpuid,20,0,0);      
              printf("cpuid =%s%d\n",cpuid,ret);*/
	//du_staff();
	vehicle();

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
        ret=lk_getalpha(4,1,cpuid,20,0,0);
        //printf("cpuid =%s%d\n",cpuid,ret);
	strcpy(pos.du_staff,cpuid);
	printf("DU Staff ID : %s\n",cpuid);
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
                lk_disptext(3,2,"3.....OTHER",0);
//                lk_disptext(9,2,"Select Vehicle Type",0);
               // ret=lk_getkey();
                //if(ret==1||ret==2||ret==3||ret==4)
                //break;
                

        char cpuid[20]="";
        ret=lk_getalpha(4,1,cpuid,20,0,0);
        //printf("cpuid =%s%d\n",cpuid,ret);
	if(strcmp(cpuid,"1") ==0)
	strcpy(pos.vehicle_type,"BIKE\0");
	else if(strcmp(cpuid,"2") ==0)
	strcpy(pos.vehicle_type,"CAR\0");
	else
	strcpy(pos.vehicle_type,"OTHER\0");
	printf("Vehicle Type : %s\n",pos.vehicle_type);
	
		if(ret>=1)
			break;
		}
	/*switch(ret)
	{
		case 1: 
			break;
		case 2:
			break;
		case 3:
			break;
		default:
			break;
	}*/
	
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
        ret=lk_getalpha(4,1,cpuid,20,0,0);
        //printf("cpuid =%s%d\n",cpuid,ret);
	if(strcmp(cpuid,"1") ==0)
	strcpy(pos.bill_type,"CASH\0");
	else
	strcpy(pos.bill_type,"CREDIT\0");
	printf("Bill Type : %s\n",pos.bill_type);	
		if(ret>=1)
		break;
		}
		
		//Preview screen before print
		//preview();
		quantity_amount();
}

void vehicle_number(void)
{
int ret=0;
        while(1)
        {
                lk_dispclr();
                lk_disptext(2,2,"Vehicle No :",1);
        //lk_dispfill();

        char cpuid[20]="";
        ret=lk_getalpha(4,1,cpuid,20,0,0);
        //printf("cpuid =%s%d\n",cpuid,ret);
        strcpy(pos.du_staff,cpuid);
        printf("Vehicle No : %s\n",cpuid);
//              ret=lk_getkey();
        if(ret>=1)
        break;
        }
                mobile_number();

}
void mobile_number(void)
{
int ret=0;
        while(1)
        {
                lk_dispclr();
                lk_disptext(2,2,"Mobile No :",1);
        //lk_dispfill();

        char cpuid[20]="";
        ret=lk_getalpha(4,1,cpuid,20,0,0);
        //printf("cpuid =%s%d\n",cpuid,ret);
        strcpy(pos.du_staff,cpuid);
        printf("Mobile No : %s\n",cpuid);
//              ret=lk_getkey();
        if(ret>=1)
        break;
        }
                preview();

//TO DO
}
void quantity_amount(void)
{
int ret=0;
	while(1)
        {
                lk_dispclr();
                lk_disptext(1,2,"1.....Quantity",0);
                lk_disptext(2,2,"2.....Amount",0);
		lk_disptext(3,2, "Press 1 or 2",0);
		
		ret=lk_getkey();
                if(ret==1||ret==2)
			break;
	}
		if(ret==1){
                        quantity();
                }
                else if(ret==2){
                        amount();
                }

//TO DO
}

void quantity(void)
{
	int ret=0;
        while(1)
        {
                lk_dispclr();
                lk_disptext(2,2,"Quantity(Lt) :",1);
        //lk_dispfill();

        char cpuid[20]="";
        ret=lk_getalpha(4,1,cpuid,20,0,0);
        //printf("cpuid =%s%d\n",cpuid,ret);
        strcpy(pos.du_staff,cpuid);
        printf("Quantity(Lt) : %s\n",cpuid);
//              ret=lk_getkey();
        	if(ret>=1)
        	break;
        }
                vehicle_number();

//TO DO
}
void amount(void)
{
int ret=0;
        while(1)
        {
                lk_dispclr();
                lk_disptext(2,2,"Amount :",1);
        //lk_dispfill();

        char cpuid[20]="";
        ret=lk_getalpha(4,1,cpuid,20,0,0);
        //printf("cpuid =%s%d\n",cpuid,ret);
        strcpy(pos.du_staff,cpuid);
        printf("Amount : %s\n",cpuid);
//              ret=lk_getkey();
        if(ret>=1)
        break;
        }

	vehicle_number();
//TO DO
}

void preview(void)
{
//	printf("Inside Preview......\n");
	int res=0, ret=0;
	 while(1)
         {
          lk_dispclr();
          lk_disptext(1,2,"1.....PRINT",0);
          lk_disptext(2,2, "2.....CANCEL",0);
          lk_disptext(3,2, "Press 1 or 2",0);
	
    	ret=lk_getkey();
    	    	if(ret==1)
       	    	{
					
		res=printBill();
		strcpy(pos.mobile_no,"888888888");
		if(res==SUCCESS){
			printf("Bill Printed successfully...\n");
			printf("Customer Details Saved Successfully as %s.txt\n", pos.mobile_no);
		}
		else{
			printf("Error : Not able to Print...\n");
   			lk_dispclr();
			lk_disptext(3,5,"PRINT CANCELLED...",1);
		}
		break;
		}
		else if(ret==2){
   			lk_dispclr();
			lk_disptext(3,5,"PRINT CANCELLED...",1);
                break;
		}		
	}

		main();
}

int printBill (void)
 {
	prn_open();
//	printf("Inside Print Bill......\n");

   char buff[300],buff1[100],buff2[300],buff3[100],buff4[200];
	char str1[15];
	 int ret;
   memset(buff,0,300);
   memset(buff1,0,100);
   memset(buff2,0,300);
   memset(buff3,0,100);
   memset(buff4,0,200);

   if(prn_paperstatus()!=0)
     {
       lk_dispclr();
       lk_disptext(3,5,"No Paper !",1);
       lk_getkey();
       return ERROR;
     }


   strcat(buff,"         IOCL Transaction Receipt\n");
   strcat(buff,"        Hitec City,HYD-PH:888888888\n");
   strcat(buff,"        G.S.T.NO. PJR/02/1/2146\n");
   //strcat(buff1,"     CASH BILL\n");
   strcat(buff,"     ---------------ORIGINAL-------------");
   //strcat(buff,"      ------------------------------------\n");
   //strcat(buff2,"     Bill No. : 90000001\n");
   strcat(buff2,"     DATE     : 09-01-2017\n");
  // strcat(buff2,"     TIME     : 10:00:00\n");
   strcat(buff2,"     MOP NAME : ");strcat(buff2,pos.bill_type);strcat(buff2,"\n");
  // sprintf(str1, "%d", pos.du_no);
   strcat(buff2,"     PUMP     : ");strcat(buff2,pos.du_no);strcat(buff2,"\n");
  // sprintf(str1, "%d", pos.nozzel_no);
   strcat(buff2,"     NOZZEL   : ");strcat(buff2,pos.nozzel_no);strcat(buff2,"\n");
//   strcat(buff2,"   DU STAFF : 10-01-2017\n");
   strcat(buff2,"     FUEL TYPE: ");strcat(buff2,pos.fuel_type);strcat(buff2,"\n");
   strcat(buff2,"     ------------------------------------");
   strcat(buff4,"     TOTAL SALE   : 100.00\n");
   strcat(buff4,"     VEHICLE No   : AP16AL1234\n");
   strcat(buff4,"     MOBILE No    : 8888888888\n");
   //strcat(buff4,"     VEHICLE TYPE : ");strcat(buff2,pos.vehicle_type);strcat(buff2,"\n");
   
   /*strcat(buff2,"  0 11.82      @ 42.31\n");
   strcat(buff2,"                          500.10\n");
   strcat(buff2,"     SUB..TOT             500.10\n");
   strcat(buff2,"     ---------------------------\n");
   strcat(buff3,"  CASH    500.10\n");
   strcat(buff4,"      ITM=1            Q=11.82\n");*/
   
   strcat(buff4,"\n           THANK YOU VISIT AGAIN\n");
   strcat(buff4,"           Save Fuel, Save Money\n");
//   strcat(buff4,"     \n     END OF BILL 1\n");

   lk_dispclr();
   lk_disptext(2,3,"PRINTING BILL...",1);



   prn_paper_feed(1);
   ret=prn_write_text(buff,strlen(buff),1);
   returncheck(ret);
   //prn_paper_feed(1);
   //ret=prn_write_text(buff1,strlen(buff1),2);
   //returncheck(ret);
   ret=prn_write_text(buff2,strlen(buff2),1);
   returncheck(ret);
 //  ret=prn_write_text(buff3,strlen(buff3),2);
   //returncheck(ret);
   ret=prn_write_text(buff4,strlen(buff4),1);
   returncheck(ret);
   ret=prn_write_text("\n\n\n",3,1);
   returncheck(ret);

   ret=prn_paper_feed(2);
   if(ret==-3)
   {

                printf("out of the paper");
        }
        else
        {
        return SUCCESS;
        }
	
	prn_close();  // closing printer
   return SUCCESS;
}




void preview_screen(void)
{
	MENU_T menu;
	int opt=0,ret;
	//char* fuel ="Fuel Type : ";
	//strcat(fuel,pos.fuel_type);
	/*char du[15] = "DU No : ";
	char nozzel[15] ="Nozzel No : ";
	char staff[15] ="DU Staff : ";
	char vehicleType[15] ="Vehicle Type : ";
	char billType[15] ="Bill Type : ";
	char vehicleNo[25] ="Vehicle No : ";
	char mob_no[25] ="Mobile No : ";
	char lt[15] ="Lt : ";
	char amt[15] ="Amount : ";
	strcat(fuel,pos.fuel_type);
	strcat(du,pos.du_no);
	strcat(nozzel,pos.nozzel_no);
	strcat(staff,pos.du_staff);
	strcat(vehicleType,pos.vehicle_type);
	strcat(billType,pos.bill_type);*/

	lk_dispclr();
	//lk_disptext(0,0,fuel,0);
//	lk_disptext(1,0,du,0); 
//	lk_disptext(2,0,nozzel,0);  
//	lk_disptext(3,0,staff,0);  
//	lk_disptext(4,0,"  PRINT    CANCEL",0);   

/*	menu.start                      =       0;
	menu.maxEntries                 =       10;
	strcpy(menu.title,"Preview");
	strcpy(menu.menu[0],"Fuel Type : PETROL");*/

	/*strcpy(menu.menu[8],"Auto download");
	strcpy(menu.menu[9],"Manual Selfdiag");*/

/*	lk_dispclr();
        lk_disptext(1,2, "FUEL TYPE : ", pos.fuel_type,0);
        lk_disptext(2,2, "DU No : ", pos.du_no,0);
        lk_disptext(3,2, pos.nozzel_no,0);	
        lk_disptext(3,2, "Press 1 or 2",0);	
        lk_disptext(3,2, "Press 1 or 2",0);	
        lk_disptext(3,2, "Press 1 or 2",0);	
        lk_disptext(3,2, "Press 1 or 2",0);	
		*/
        lk_disptext(4,0, "Press ENTER to Print",0);
	while(1)
	{	
                ret=lk_getkey();
                if(ret==CANCEL)
                break;
		else if(ret==ENTER)
		printf("Customer Details Saved Successfully as %d.txt\n", pos.mobile_no);
	}
		
		//Loop Back to Main Menu
		Display_new();

}
