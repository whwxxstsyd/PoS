
#include<stdio.h>
#include<stdlib.h>
#include<header.h>
#include<X6x8.h>

/****************** SERVER CODE ****************/

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include<pthread.h>
#include <semaphore.h>
/***********************************************************************************************
                        MAIN MENU FOR HHT SELF-DIAGNOSTICS 

***********************************************************************************************/               
char autobuf[80];
//unsigned char pos=0;
static int module=0;
int newSocket;
int exitFun = 0;

struct pos_details
{
	char pump_id[10];
	char vehicle_no[15];
	char mobile_no[15];
	char fuel_type[10];
	char du_no[10];
	char nozzel_no[10];
	char vehicle_type[20];
	char bill_type[20];
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
                    
                   		        //case 1: Display_new (manualflag);	         break;
                   		        case 1: transactions (manualflag);	         break;
					//case 1: serverToNodeJS(manualflag);	 break;
                        		case 2: Keypad_test (manualflag);	 break;
                        		case 3: Printer_test (manualflag);	 break;
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
					case 14: audio_test(manualflag);         break;

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

void transactions(void)
{

struct tm intim;

                char buff[150]="";
                int cnt=1;
                int ret=0;
                 lk_getrtc(&intim);

        sprintf(autobuf,"%s-%02d%02d%02d%02d%02d%04d.txt",buff,intim.tm_hour,intim.tm_min,intim.tm_sec,intim.tm_mday,intim.tm_mon+1,intim.tm_year+1900);

	//Initiate the server connection
//	serverToNodeJS();

                while(1)
                {
//                        ret=lk_getkey();
  //                      if(ret==CANCEL)
    //                    main();
                lk_dispclr();
                lk_disptext(1,0,"Transactions based on :",0);
                lk_disptext(2,1,"1.PUMP ID",0);
                lk_disptext(3,1,"2.Customer's details",0);
                lk_disptext(5,2, "Press 1 or 2",0);
//                                                char cpuid[20]="";
  //                                              ret=lk_getalpha(3,0,cpuid,20,0,0);
    //                                            printf("cpuid =%s%d\n",cpuid,ret);
                	ret=lk_getkey();
                	if(ret==1||ret==2)
	                break;
                }

             //   if(ret==1 || ret==2)
               // {
                        if(ret==1)
				fetch_pump_details();
                        else
				fetch_customer_details();
		//}
			
		
}
int flag1=0;
void fetch_pump_details(void)
{
	struct tm intim;

                char buff[150]="";
                int cnt=1;
                int ret=0;
                 lk_getrtc(&intim);
	//For no of transactions
	flag1=1;
        
	sprintf(autobuf,"%s-%02d%02d%02d%02d%02d%04d.txt",buff,intim.tm_hour,intim.tm_min,intim.tm_sec,intim.tm_mday,intim.tm_mon+1,intim.tm_year+1900);

                while(1)
                {
                        ret=lk_getkey();
                        if(ret==CANCEL)
                        main();
                lk_dispclr();
                lk_disptext(1,2,"Enter PUMP ID :",0);
                        char cpuid[20]="";
                        ret=lk_getalpha(3,1,cpuid,20,0,0);
                        printf("cpuid =%s%d\n",cpuid,ret);
			strcpy(pos.pump_id,cpuid);
                        printf("PUMP id =%s\n",pos.pump_id);
		
//                ret=lk_getkey();
                if(ret >=1)
                break;
                }
	//Print
//	print_me();	

	print_transaction();
}

void fetch_customer_details(void)
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
                lk_disptext(1,0, "Customer's details :",0);
                lk_disptext(2,1, "Mobile no : ",0);
                                char cpuid[20]="";
                                ret=lk_getalpha(3,1,cpuid,20,0,0);
                                printf("cpuid =%s%d\n",cpuid,ret);
				strcpy(pos.mobile_no,cpuid);
                                printf("Mobile No =%s\n",pos.mobile_no);
				
                lk_dispclr();
                lk_disptext(1,0, "Customer's details :",0);
                lk_disptext(2,1, "Vehicle no : ",0);
                //                                char cpuid[20]="";
                                ret=lk_getalpha(3,1,cpuid,20,0,0);
                                printf("cpuid =%s%d\n",cpuid,ret);
				strcpy(pos.vehicle_no,cpuid);
                                printf("Vehicle No =%s\n",pos.vehicle_no);
//                ret=lk_getkey();
                if(ret>=1)
                break;
                }

	//Print
//	print_me();
	print_transaction();
}

void print_transaction(void)
{
	 struct tm intim;

                char buff[150]="";
                int cnt=1;
                int ret=0;
                 lk_getrtc(&intim);
	
	if(flag1==1){
		while(1)
                {
                lk_dispclr();
                lk_disptext(1,1, "PRINT",1);
                lk_disptext(3,1, "Last Transaction",0);
          	lk_disptext(5,2, "Press ENTER",0);
       
		ret=lk_getkey();
	
		if(ret>=1)
		break;
		}
	print_me();
//		fetchDataFromNodeJS();
	}		
	else
	{
                while(1)
                {
                lk_dispclr();
                lk_disptext(0,1, "PRINT",1);
                lk_disptext(2,0, "No of Transactions",0);
			char cpuid[20]="";
                        ret=lk_getalpha(3,1,cpuid,20,0,0);
                        printf("cpuid =%s%d\n",cpuid,ret);

		//TODO Fetch the transactions
		
                ret=lk_getkey();

                if(ret ==1 || ret ==2)
                break;
                }
	print_me();
//	fetchDataFromNodeJS();
	}	

}

void fetchDataFromNodeJS(void)
{
	char buffer[1024];
	/*---- Send message to the socket of the incoming connection ----*/
	strcpy(buffer,"Hello World\n");
	send(newSocket,buffer,1024,0);
	
	memset(buffer,'\0',1024);
	/*---- Receive message from the client connection ----*/
	printf("Client: Receiving Message...\n");
	recv(newSocket, buffer, 1024, 0);

	/*---- Print the received message ----*/
	printf("Data received: %s\n",buffer);
	
	//Print the received data	
	print_me();
}

void print_me(void)
{
//      printf("Inside Preview......\n");
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

//	serverToNodeJS();
		break;
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

/////////////////////////////////////////////////////////////////////////////
/*Creating a thread for server */

int serverToNodeJS(void)
{
	int welcomeSocket, *new_sock;
	char buffer[1024];
	struct sockaddr_in serverAddr;
	struct sockaddr_storage serverStorage;
	socklen_t addr_size;

	/*---- Create the socket. The three arguments are: ----*/
	/* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
	welcomeSocket = socket(PF_INET, SOCK_STREAM, 0);

	/*---- Configure settings of the server address struct ----*/
	/* Address family = Internet */
	serverAddr.sin_family = AF_INET;
	/* Set port number, using htons function to use proper byte order */
	serverAddr.sin_port = htons(8899);
	/* Set IP address to localhost */
	serverAddr.sin_addr.s_addr = inet_addr("192.168.43.69");
	/* Set all bits of the padding field to 0 */
	memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

	/*---- Bind the address struct to the socket ----*/
	bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

	/*---- Listen on the socket, with 5 max connection requests queued ----*/
	if(listen(welcomeSocket,5)==0)
		printf("Listening\n");
	else
		printf("Error\n");

	/*---- Accept call creates a new socket for the incoming connection ----*/
	addr_size = sizeof serverStorage;
	newSocket = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);

	/*---- Send message to the socket of the incoming connection ----*/
//	strcpy(buffer,"Hello World\n");
//	send(newSocket,buffer,13,0);
	           
	//Start the app 
		 int res=0, ret=0;
	if(newSocket != -1)
	{
	         while(1)
        	 {
	          lk_dispclr();
        	  lk_disptext(1,2,"Established Connection",0);
        	  lk_disptext(2,2,"Starting APP...",0);
//        	  lk_disptext(3,2, "Press 1 or 2",0);

	        ret=lk_getkey();
                	if(ret>=1)
                	{
				break;
			}
		}
		transactions();
       	}
	else
	{
	         while(1)
        	 {
	          lk_dispclr();
        	  lk_disptext(1,2,"CANNOT Established Connection",0);
//        	  lk_disptext(3,2, "Press 1 or 2",0);

	        ret=lk_getkey();
                	if(ret>=1)
                	{
				break;
			}
		}
		transactions();
	}

	while (!exitFun);
	close(newSocket);

	//Return to main function
	main();

	return 0;


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




