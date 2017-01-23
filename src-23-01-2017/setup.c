#include <header.h>

int Setup_menu (void)
 {
        int opt=0,ret;
        MENU_T menu;
        char event;

        
        int selItem  = 0;
        int acceptKbdEvents = TRUE;
        int maxEntries = 0;
        short scroll = 0;
	struct tm curt;
	
        memset(&curt,0,sizeof(struct tm));                                                                                                                    
        menu.start                      =       0;
        menu.maxEntries                 =       3;
        maxEntries                      =       menu.maxEntries;
                                                                                                                            
        strcpy(menu.title, "Setup");
                                                                                                                            
        strcpy(menu.menu[0],"Set Date");
        strcpy(menu.menu[1],"Set Time");
	strcpy(menu.menu[2],"Display RTC");
      
	
	 while(1)
        {
            opt = scroll_menu(&menu,&selItem,acceptKbdEvents);
                                                                                                                            
                switch(opt)
                {
                  case CANCEL:
                  return;
                  case ENTER:
                         switch (selItem+1)
                          {
                                                                                                                            
                       case 1:
			 	lk_getrtc(&curt);
				 Date_setting(&curt);
                              	lk_setrtc(&curt);
                               break;

                      case 2:  lk_getrtc(&curt);
			       time_setting(&curt);	
                               lk_setrtc(&curt);
                               break;
                     
                              
		     case 3:
				display_rtc(&curt);
				break;
										

                     }
                default : break;
                }
                                                                                                                            
        }
}



int Date_setting(struct tm *curt)
{
        char str[10];
        int rval;

        while(1)
         {
           memset(str,0,10);
           lk_dispclr();
           lk_disptext(2,0,"Enter Date (DDMMYYYY)",0);
        rval = lk_getnumeric (4, 1,str, 8,0);
           if(rval<0)

           return 0;  

           if(chk_date(str) == 0  && rval == 8 )
	   break;

	   else 	
             {
              lk_dispclr();
              lk_disptext(3,4,"TRY AGAIN",1);
              printf("ENTER CORRECT DATA\n");
              if (CANCEL==lk_getkey())
              return 0;
             }
      }
         curt->tm_mday = ( str[0]-0x30)*10+(str[1]-0x30);
	 curt->tm_mon  = ( str[2]-0x30)*10+(str[3]-0x30) -1; 
	 curt->tm_year = (( str[4]-0x30)*1000 + (str[5]-0x30)*100 + (str[6]-0x30)*10 + (str[7]-0x30)) -1900 ;
         return 0;
 }

int time_setting(struct tm *curt)
{
	char str[10];
	int rval;
	while(1)
         {
		memset(str,0x00,10 );
                lk_dispclr(); 
        	lk_disptext(2,0,"Enter Time (HHMMSS) ",0);
                lk_disptext(5,0,"Enter in 24HRS Format",0); 
                rval=lk_getnumeric(4,1,str,6,0);
        	if(rval < 0)
                return 0;
	
        	if(chk_time(str)==0 && rval==6 )                                                            
               	break;

                else 
                {
                 lk_dispclr();
                 lk_disptext(3,4,"TRY AGAIN",1);
                 printf("ENTER CORRECT DATA\n");  
	         if (CANCEL==lk_getkey())
	         return -1;
                }
   
         }
        curt->tm_hour=(str[0]-0x30)*10+(str[1]-0x30);
        curt->tm_min=(str[2]-0x30)*10+(str[3]-0x30);
        curt->tm_sec=(str[4]-0x30)*10+(str[5]-0x30);

	
	return 0;
}
                                                                                                                            
#if 0                                                                                                                            
int TimeFormat(const struct tm *curt)
{
	int value;
        struct tm settime;
        memcpy(&settime,curt,sizeof(struct tm));
        lk_dispclr();
        lk_disptext(2,4,"DISPLAY FORMAT",0);
        lk_disptext(3,5,"1. 12 Hours",0);
        lk_disptext(4,5,"2. 24 Hours",0);
        value=lk_getkey();
#if 0
	if (value==1)
		lk_timeformat(1);
	else  if (value==2)
		lk_timeformat(0);

#endif	
	return 0;                                           
	           
                                                                     
}

#endif 


                                                                                                 
int chk_time (char *str)
{
	int HH,MM,SS;
	HH=(str[0]-0x30)*10+(str[1]-0x30);
        MM=(str[2]-0x30)*10+(str[3]-0x30);
        SS=(str[4]-0x30)*10+(str[5]-0x30);

	if ( HH < 0 || HH > 23 || MM < 0 || MM > 59 || SS < 0 || SS > 59 )
	return ERROR;

	return 0;
}
                                                                                                 
int chk_date (char *str)
{
	int epos_date=0,epos_month=0,epos_year=0; 

         epos_date  = ( str[0]-0x30)*10+(str[1]-0x30);
         epos_month = ( str[2]-0x30)*10+(str[3]-0x30);
         epos_year  = ( str[4]-0x30)*1000+ (str[5]-0x30)*100 + (str[6]-0x30)*10 + (str[7]-0x30);


	if ( epos_month < 1 || epos_date < 1 || epos_date > 31 || epos_month > 12  ||  epos_year < 2008 ) return ERROR ;

	else if(epos_month == 1 || epos_month == 3 || epos_month == 5 || epos_month == 7 || 										epos_month == 8 || epos_month ==10 ||epos_month == 12)
		{

			if (epos_date > 31)
			return ERROR;
		}	

	 else  if (epos_month == 4 || epos_month == 6 || epos_month == 9 || epos_month == 11)
		{

		if (epos_date > 30)
			return ERROR;
		}

	else if  (epos_month == 2 )

		{
		 if ( !(epos_year%400) || (epos_year%100 != 0 && epos_year%4==0 ) )
			 { if (epos_date > 29 ) return ERROR;}

			else  if( epos_date > 28 ) return ERROR;				
		}	
				
			
	return 0;
}




int display_rtc(struct tm *intim)
{
        char str[100]="";
        char day[7][10] ={ "Sunday" ,"Monday","Tuesday","Wednesday","Thursday","Friday","Saturday" } ;
        char mon[12 ][12]={"January","February","March","April"," May","June",
                           "July","August","September","October","November","December"} ;
        int sec=0;
        struct timeval tv;
        unsigned int count=50;

                while (count)
                {
                gettimeofday (&tv,NULL) ;
                intim = gmtime (&tv.tv_sec) ;
                if (intim->tm_sec !=sec)
                {
                sprintf(str,"%s %02d:%02d:%02d",day[intim->tm_wday], intim->tm_hour,intim->tm_min,intim->tm_sec);
                lk_dispclr();
                lk_disptext(3,2,str,1);
                sprintf(str,"%s %02d, %04d",mon[intim->tm_mon], intim->tm_mday, intim->tm_year+1900);
                lk_disptext(1,2,str,1);
                }

                usleep(100000);
                sec=intim->tm_sec;

                count--;
                }
}


