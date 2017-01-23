#include <header.h>

 char arr1[50]="";
 char arr2[50]="";
 char arr3[50]="";
 char arr4[50]="";
 char arr5[50]="";
 char arr6[50]="";
                                                                                                                             
 char ethtype[30]="eth0";
 char IPADR[30]="";

/*******************************************************************************************
                            Ethernet setup main menu
 *******************************************************************************************/
int ethernet()
{

	char  ipd[80]="";

	int opt;
    	char str[50]="";
    	MENU_T menu;
    	int selItem  = 0;
    	int acceptKbdEvents = TRUE;
    	int maxEntries = 0;


    
   	menu.start                      =       0;
    	menu.maxEntries                 =       2;
    	maxEntries                      =       menu.maxEntries;
    	strcpy(menu.title, "Ethernet Menu");
    	strcpy(menu.menu[0],"STATIC");
    	strcpy(menu.menu[1],"DHCP");
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
                                  		printf("\n STATIC IP SETTING\n");
                                  		ethernet_test();
                                  		break;
                           		case 2:
                              			printf("\nDHCP\n");
                              			lk_dispclr();
                              			lk_disptext(3,3,"RUNNING DHCP ...",0);
                              			sprintf(str,"/sbin/dhcpcd %s",ethtype);
                              			printf("\n%s\n",str);
                              			system(str);
                              			ip_config();
                              			break;

					case CANCEL:
						break;
					default :
						continue;
						}
			sprintf(ipd, "ifconfig %s down > /dev/null 2>&1",ethtype);
        		system(ipd);
        		return SUCCESS;
                  }   
              

                 
       }
}

/***********************************************************************************
                     Ethernet Setting  Test
************************************************************************************/
int ethernet_test()
{
	int opt=0;
     	MENU_T menu;
     	int selItem  = 0;
     	int acceptKbdEvents = TRUE;
     	int maxEntries = 0;
     	menu.start                      =       0;
     	menu.maxEntries                 =       8;
     	maxEntries                      =       menu.maxEntries;
     	strcpy(menu.title, "STATIC Menu");
     	strcpy(menu.menu[0],"Set IP Address");
     	strcpy(menu.menu[1],"Set Subnet Mask");
     	strcpy(menu.menu[2],"Set Gateway");
     	strcpy(menu.menu[3],"Set Primary DNS");
     	strcpy(menu.menu[4],"Set Secondry DNS");
     	strcpy(menu.menu[5],"Get MAC ID");
     	strcpy(menu.menu[6],"Settings View");
     	strcpy(menu.menu[7],"Ping Test");
  //   	strcpy(menu.menu[8],"Curl Test");
    	while(1){
      		opt = scroll_menu(&menu,&selItem,acceptKbdEvents);
      		switch(opt){
             		case CANCEL:
               			return -1;

             		case ENTER:
                	case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8:
                		switch (selItem+1){
                    			case 1:
                            			set_ip();
                            			break;

                    			case 2:
                            			set_subnet_mask();
                            			break;

                    			case 3:
                           			set_gateway();
                           			break;

                    			case 4:
                           			set_pri_dns();
                           			break;

                    			case 5:
                            			set_sec_dns();
                            			break;
                   			case 6:
                          			get_mac_id(1);
                          			break;

                   			case 7:
                          			ip_config();
                          			break;
                   			case 8:
                          			png_test();
                          			break;
                   	//		case 9:
                          //			curl_test();
                          //			break;
 
               			}

          	}

	}

   	return 0;
}

/****************************************************************************************
                             setting ip
*****************************************************************************************/
int set_ip (void)
{
	char ip_addr[60]="",dest[30]="192.168.1.55";
	int ret =0;

     	while(1){           // Validating given IP               
        	lk_dispclr();
        	lk_disptext(2,2,"Enter IP Address",0);
		memset(IPADR,0,30);
		strcpy(IPADR,dest);
		ret=lk_getalpha(4,0,IPADR,15,strlen(dest),0);
		if (ret < 0)
		return -1;
		printf("%d\n",ret);

        	if(ip_chk()==0)
         		break;
        	else{
          		lk_dispclr();
          		lk_disptext(3,2,"Not Valid IP",1);
          		printf("Enter Valid Address\n");
          		sleep(1);
         	}
      	}

      	sprintf(ip_addr,"ifconfig %s %s up",ethtype,IPADR);
      	printf("\n%s\n",ip_addr);
      	system(ip_addr);         // setting ip
      	return 0;
}

/** Tesing curl application ..  */

int curl_test()
{
	char http_url[]="http://192.168.1.174";
	char filename[]="/mnt/jffs2/download";

	lk_dispclr();
	lk_disptext(2,3,"Downloading from",0);
	lk_disptext(4,0,"http://192.168.1.174",1);
	sleep(2);
	GET_file_clear(http_url,filename);
	lk_dispclr();
	lk_disptext(3,3,"Downloaded...",1);
	lk_disptext(5,4,"press any key",0);
	lk_getkey();
	lk_dispclr();

	return 0;
} 



/***********************************************************************************
                      setting Subnet Mask
****************************************************************************************/
  
int set_subnet_mask (void)
{
	char subnet_mask[60]="",dest[30]="255.255.255.0";
     
     	get_subnet(1);     // reading subnet mask
     	strcpy(dest,arr3); 
	memset(IPADR,0,30);
	strcpy(IPADR,dest);
      	while(1){          // checking given address 
        	lk_dispclr();
        	lk_disptext(2,2,"Enter Subnet Mask",0);
        	if( lk_getalpha(4,0,IPADR,15,strlen(dest),0)< 0)
		return -1;
        	if(ip_chk()==0)
        		break;
        	else{
           		lk_dispclr();
           		lk_disptext(3,2,(unsigned char*)"Not Valid IP",0);
           		printf("Enter Valid Address\n");
           		sleep(2);
         	}
       	}
        
      	sprintf(subnet_mask,"ifconfig %s netmask %s up",ethtype,IPADR);
      	printf("\n%s\n",subnet_mask);
      	system(subnet_mask);

      	return 0;
}


/******************************************************************************************
                           Setting Default Gateway
******************************************************************************************/
int set_gateway()
{
	char gateway[60]="",dest[30]="192.168.1.8";
      	int result=0;
	

		for(;;)
		{
		memset(IPADR,0,30);
		strcpy(IPADR,dest);
      		lk_dispclr();
      		lk_disptext(2,0,(unsigned char*)"Enter Default Gateway",0);

		if (lk_getalpha(4,0,IPADR,15,strlen(dest),0) < 0)
		return -1;
      		if(!ip_chk())
      			break;
      		else
		{
        		lk_dispclr();
        		lk_disptext(3,2,(unsigned char*)"Not Valid IP",0);
        		printf("Enter Valid Address\n");

			if(lk_getkey()<0)
			return -1;
       		}
      	}
      	sprintf(gateway,"route add default gw %s",IPADR);
      	printf("\n%s\n",gateway);
      	system(gateway);
      	return 0;
}
      
/********************************************************************************************
                           Setting Primary DNS
 *******************************************************************************************/
int set_pri_dns()
{
	FILE *fp;
     	char pri_dns[60]="",dest[30]="192.168.1.8";
     	char str[50]="#search localdomain\n";

    	while(1){
		memset(IPADR,0,30);
		strcpy(IPADR,dest);
      		lk_dispclr();
      		lk_disptext(2,2,(unsigned char*)"Enter Primary DNS",0);

		if ( lk_getalpha(4,0,IPADR,15,strlen(dest),0) < 0)
		return -1;
      		if(ip_chk()==0)
      			break;
      		else{
        		lk_dispclr();
        		lk_disptext(3,2,(unsigned char*)"Not Valid IP",0);
        		printf("Enter Valid Address\n");
        		sleep(2);
       		}
     	}
      	sprintf(pri_dns,"nameserver %s ",IPADR);
      	printf("\n%s\n",pri_dns);
      	fp = fopen("/etc/resolv.conf","w+");
     	fputs(str,fp);
     	fputs(pri_dns,fp);
     	fclose(fp);
     	return 0;
}
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
/****************************************************************************************
                 Setting Secondary DNS
***************************************************************************************/
int set_sec_dns()
{
	FILE *fp;
     	char sec_dns[60]="",dest[30]="192.168.1.3";
    	while(1){
		memset(IPADR,0,30);
		strcpy(IPADR,dest);
       		lk_dispclr();
       		lk_disptext(2,1,(unsigned char*)"Enter Secondary DNS",0);

		if ( lk_getalpha(4,1,IPADR,15,strlen(dest),0) < 0)
		return -1;
       		if(ip_chk()==0)
       			break;
       		else{
         		lk_dispclr();
         		lk_disptext(3,2,(unsigned char*)"Not Valid IP",0);
         		printf("Enter Valid Address\n");
         		sleep(2);
        	}
      	}
     	printf("\n%s\n",sec_dns);
     	sprintf(sec_dns,"nameserver %s",IPADR);
     	fp = fopen("/etc/resolv.conf","a");
     	fputs(sec_dns,fp);
     	fclose(fp);
     	return 0;
}


/*****************************************************************************************
                    Reading MAC Address
*****************************************************************************************/
int get_mac_id(int var )
{
	int fd,i=0;
    	char macid[30];
    	struct ifreq ifr;

    	fd=socket(AF_INET,SOCK_DGRAM,0);
    	ifr.ifr_addr.sa_family = AF_INET;
    	strncpy(ifr.ifr_name, ethtype,IFNAMSIZ-1);
    	ioctl(fd,SIOCGIFHWADDR,&ifr);
    	close(fd);
    	sprintf(macid,"%2x:%2x:%2x:%2x:%2x:%2x",(unsigned char)ifr.ifr_hwaddr.sa_data[0],
                                            (unsigned char)ifr.ifr_hwaddr.sa_data[1],
                                            (unsigned char)ifr.ifr_hwaddr.sa_data[2],
                                            (unsigned char)ifr.ifr_hwaddr.sa_data[3],
                                            (unsigned char)ifr.ifr_hwaddr.sa_data[4],
                                            (unsigned char)ifr.ifr_hwaddr.sa_data[5]);
    	for(i=0;i<(strlen(macid));i++)
    		if(macid[i]==' ')
    			macid[i]='0';
 	macid[i]='\0';
    	sprintf(arr2,"MAC:%s",macid);
    	if(var==1){
      		lk_dispclr();
      		lk_disptext(2,4,"MAC ADDRESS",0);
      		lk_disptext(4,2,macid,0);
      		lk_disptext(5,4,"press any key",0);
        	lk_getkey();
       	}
  	
}

/*****************************************************************************************                                                             IP Setting View
*******************************************************************************************/
int ip_config(void)
{
	int opt=0;
        int k;///////
   	MENU_T menu;
   	int selItem  = 0;
   	int acceptKbdEvents = TRUE;
   	int maxEntries = 0;
   	menu.start                      =       0;
   	menu.maxEntries                 =       6;
   	maxEntries                      =       menu.maxEntries;
   	strcpy(menu.title, "IP SETTINGS");
   	get_ip();






   	get_mac_id(2);
   	get_subnet(2);
   	get_gateway();
   	get_pri_dns();
   	get_sec_dns();


   	strcpy(menu.menu[0],arr2); //printf(" %s--arr2\n",arr2);
   	strcpy(menu.menu[1],arr1); //printf(" %s--arr1\n",arr1);
   	strcpy(menu.menu[2],arr3); //printf(" %s--arr3\n",arr3);
   	strcpy(menu.menu[3],arr4); //printf(" %s--arr4\n",arr4);
   	strcpy(menu.menu[4],arr5); //printf(" %s--arr5\n",arr5);
   	strcpy(menu.menu[5],arr6); //printf(" %s--arr6\n",arr6);

   	while(1){
     		opt = scroll_menu(&menu,&selItem,acceptKbdEvents);
     		switch(opt){
        		case CANCEL:
         			return	0;
       		}
    	}
}

/*****************************************************************************************
                       Reading IP Addr
*****************************************************************************************/
int get_ip()
{
	int fd;
      	char str[40]="";
      	struct ifreq ifr;

      	fd=socket(AF_INET,SOCK_DGRAM,0);
      	ifr.ifr_addr.sa_family = AF_INET;
      	strncpy(ifr.ifr_name, ethtype,IFNAMSIZ-1);
      	ioctl(fd,SIOCGIFADDR,&ifr);
      	close(fd);
      	sprintf(str,"%d.%d.%d.%d",(unsigned char)ifr.ifr_addr.sa_data[2],
                                (unsigned char)ifr.ifr_addr.sa_data[3],
                                (unsigned char)ifr.ifr_addr.sa_data[4],
                                (unsigned char)ifr.ifr_addr.sa_data[5]);
                                                                                                    
     	sprintf(arr1,"IP  :%s",str);
     	printf("\nIP Address : %s\n",str);
                                                                                                    
}


/*********************************************************************************
                 Reading Default Gateway
*********************************************************************************/


int   get_gateway(void)
      {
        FILE *fp;
        int i;
        char str[50],str1[50]="Not found";
        system ("route | grep default > /tmp/dfgw");
        fp=fopen("/tmp/dfgw","r");
        if(fp==NULL)
        fclose(fp);
        else
         {
           for(i=0;i<10;i++)
            {
              fscanf(fp,"%s",str);
              if(fp==NULL)
              break;
              else if(!(strcmp(str,"default")))
               {
                fscanf(fp,"%s",str1);
                break;
               }
             }
        fclose(fp);
        remove("/tmp/dfgw");
      }
                                                                                                                             
    sprintf(arr4,"GW  :%s",str1);
    printf("\nGATEWAY : %s\n",str1);
	return 0;
                                                                                                                             
   }

/**************************************************************************************
                   Reading Subnet Mask
************************************************************************************/
                                                                                                                                                                                                        
int get_subnet(int var)
{
	char str[40]="";
      	int fd;
      	struct ifreq ifr;

	memset(str,0,40);	
     	fd=socket(AF_INET,SOCK_DGRAM,0);
     	ifr.ifr_addr.sa_family = AF_INET;
     	strncpy(ifr.ifr_name, ethtype,IFNAMSIZ-1);
     	ioctl(fd,SIOCGIFNETMASK,&ifr);
     	close(fd);
     	sprintf(str,"%d.%d.%d.%d",(unsigned char)ifr.ifr_netmask.sa_data[2],
                               (unsigned char)ifr.ifr_netmask.sa_data[3],
                               (unsigned char)ifr.ifr_netmask.sa_data[4],
                               (unsigned char)ifr.ifr_netmask.sa_data[5]);
                                                                                                                                                                                                        
      	if(var==1)
      		strcpy(arr3,str);
      	else
      		sprintf(arr3,"NET:%s",str);
      	printf("\nSUBNET MASK : %s\n",str);
}



/************************************************************************************
                        Reading Primary DNS
*************************************************************************************/
int  get_pri_dns()
{
	FILE *fp;
      	int j;
      	char str[80]="",str1[50]="Not Found";
      	fp = fopen("/etc/resolv.conf","r");
      	if(fp==NULL)
       		fclose(fp);
      	else
       		for(j=0;j<20;j++){
           		fscanf(fp,"%s",str);
           		if(!strcmp(str,"nameserver")){
              			fscanf(fp,"%s",str1);
              			fclose(fp);
              			break;
             		}
         	}
   	sprintf(arr5,"DNS1:%s",str1);
   	printf("\nPRIMARY DNS : %s\n",str1);
    
}


/*************************************************************************************
                    Reading Secondary DNS
*************************************************************************************/
int  get_sec_dns()
{
	FILE *fp;
        char str[80]="",str1[50]="Not Found";
        int flag=0,j;
        fp = fopen("/etc/resolv.conf","r");
        if(fp==NULL)
        	fclose(fp);
        else
        	for(j=0;j<50;j++){
             		fscanf(fp,"%s",str);
             		if(!(strcmp(str,"nameserver"))){
                		if(flag==1){
                     			fscanf(fp,"%s",str1);
                     			fclose(fp);
                     			break;
                   		}
               			else
               				flag =1;
              		}
           	}
                                                                                                                             
       	sprintf(arr6,"DNS2:%s",str1);
       	printf("\nSECONDARY DNS : %s\n",str1);
}

/***********************************************************************************
                               PING Test
***********************************************************************************/





int  png_test(void)
     {
       FILE *fp;
       char a,b,c;
       int i,ret=0;
       char ipaddr[80]="",dest1[30]="192.168.1.1";
       while(1)
        {
       
       
                memset(IPADR,0,30);
                strcpy(IPADR,dest1);
                lk_dispclr();
                lk_disptext(2,2,(unsigned char*)"Enter IP to Png",0);
                ret =  lk_getalpha(4,0,IPADR,15,strlen(dest1),0);
                if (ret < 0)
                return;




          if(!ip_chk())
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
      sprintf(ipaddr,"ping -c 2 %s | grep loss > /tmp/png_file",IPADR);
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



int ip_chk()
{
	char k=0,flag=0,len=0,cnt=0;
      	char str[30]="";
      	int chk[10],val=0,l=0,i,j=0;
      	chk[0]=-1;
  
	//memset(str,0,30);
      	//while(1){
		memset(str,0,30);
        	strcpy(str,IPADR);
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
        		//   printf("%s  %d %d %d %d %d \n",str,chk[0],chk[1],chk[2],chk[3],chk[4]);
           		for(i=0,val=0,l=0;i<4;i++){
              			cnt = chk[i+1]-chk[i];
              			k=chk[i+1];
              			if( cnt < 2  || cnt > 4 ){
                 			flag=1;
         				//        printf("error at %d\n",i+1);
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
          			//  printf("value is %d\n",val );
             			if(val<0 || val >255)
              			flag=1;
             		}
		}
        	if(flag==0 && j==3)
        		return 0;
        	else
        		return -1;
}


