#include <header.h>

static unsigned char intensity=23,bkl_intensity=3;	//default value
unsigned int autoflag=0;

unsigned  char logo []={
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0xf0,0xff,0x1f,0x0,0x0,0x0,0x0,0x0,0x80,0xff,0xff,0xff,0xff,0xff,0xff,0x0,
0xf0,0xff,0x1f,0x0,0x0,0x0,0x0,0x0,0x80,0xff,0xff,0xff,0xff,0xff,0xff,0x0,
0xf0,0xff,0x1f,0x0,0x0,0x0,0x0,0x0,0x80,0xff,0xff,0xff,0xff,0xff,0xff,0x0,
0xf0,0xff,0x1f,0x0,0x0,0x0,0x0,0x0,0x80,0xff,0xff,0xff,0xff,0xff,0xff,0x0,
0xf0,0xff,0x1f,0x0,0x0,0x0,0x0,0x0,0x80,0xff,0xff,0xff,0xff,0xff,0xff,0x0,
0xf0,0xff,0x1f,0x0,0x0,0x0,0x0,0x0,0x80,0xff,0xff,0xff,0xff,0xff,0xff,0x0,
0xf0,0xff,0x1f,0x0,0x0,0x0,0x0,0x0,0x80,0xff,0xff,0xff,0xff,0xff,0xff,0x0,
0xf0,0xff,0x1f,0x0,0x0,0x0,0x0,0x0,0x80,0xff,0xff,0xff,0xff,0xff,0xff,0x0,
0xf0,0xff,0x1f,0x0,0x0,0x0,0x0,0x0,0x80,0xff,0xff,0xff,0xff,0xff,0xff,0x0,
0xf0,0xff,0x1f,0x0,0x0,0x0,0x0,0x0,0x80,0xff,0xff,0xff,0xff,0xff,0xff,0x0,
0xf0,0xff,0x1f,0x0,0x0,0x0,0xf8,0x0,0x80,0xff,0xff,0xff,0xff,0xff,0xff,0x0,
0xf0,0xff,0x1f,0x0,0x0,0x0,0xf8,0x0,0x80,0xff,0xff,0xff,0xff,0xff,0xff,0x0,
0xf0,0xff,0x1f,0x0,0x30,0x0,0xf8,0x0,0x80,0xf,0xff,0xff,0xff,0xc1,0xff,0x0,
0xf0,0xff,0x1f,0x0,0xf8,0x0,0xf8,0x0,0x80,0xf,0xff,0xff,0xff,0xc1,0xff,0x0,
0xf0,0xff,0x1f,0x0,0xf8,0x0,0xf8,0x0,0x80,0xf,0xff,0xff,0xff,0xc1,0xff,0x0,
0xf0,0xff,0x1f,0x0,0xfe,0x0,0xf8,0x0,0x80,0xf,0xff,0xff,0xff,0xc1,0xff,0x0,
0xf0,0xff,0x1f,0x0,0xfe,0x1,0x0,0x0,0x80,0xf,0xff,0xff,0xff,0xc1,0xff,0x0,
0xf0,0xff,0x1f,0x0,0xee,0x1,0x0,0x0,0x80,0xf,0xff,0xff,0xff,0xc1,0xff,0x0,
0xf0,0xff,0x1f,0x0,0xef,0x3,0x0,0x0,0x80,0xf,0xff,0xff,0xff,0xc1,0xff,0x0,
0xf0,0xff,0x1f,0x0,0xef,0x3,0x70,0x78,0x38,0x2,0xf2,0x3,0xff,0xc1,0xff,0x0,
0xf0,0xff,0x1f,0x0,0xc7,0x3,0xf8,0x78,0x3e,0x0,0xf0,0x1,0xfe,0xc1,0xff,0x0,
0xf0,0xff,0x1f,0x80,0xc7,0x7,0xf8,0xf8,0x3f,0x0,0x70,0x0,0xf8,0xc1,0xff,0x0,
0xf0,0xff,0x1f,0x80,0xc7,0x7,0xf8,0xf8,0x3f,0xe,0x3e,0xf8,0xf0,0xc1,0xff,0x0,
0xf0,0xff,0x1f,0xc0,0x1,0xf,0xf8,0xf8,0x81,0xf,0x1f,0xfc,0xe1,0xc1,0xff,0x0,
0xf0,0xff,0x1f,0xc0,0x1,0xf,0xf8,0xf8,0x80,0xf,0x1f,0xfc,0xe1,0xc1,0xff,0x0,
0xf0,0xff,0x1f,0xc0,0x1,0xf,0xf8,0xf8,0x80,0xf,0x1f,0xfe,0xe1,0xc1,0xff,0x0,
0xf0,0xff,0x1f,0xc0,0x0,0xe,0xf8,0xf8,0x80,0xf,0xf,0xfe,0xc1,0xc1,0xff,0x0,
0xf0,0xff,0x1f,0xe0,0x0,0xe,0xf8,0xf8,0x80,0xf,0xf,0xfe,0xc1,0xc1,0xff,0x0,
0xf0,0xff,0x1f,0xe0,0x0,0x1e,0xf8,0xf8,0x80,0xf,0xf,0x0,0xc0,0xc1,0xff,0x0,
0xf0,0xff,0x1f,0xf0,0xff,0x1f,0xf8,0xf8,0x80,0xf,0xf,0x0,0xc0,0xc1,0xff,0x0,
0xf0,0xff,0x1f,0xf0,0xff,0x3f,0xf8,0xf8,0x80,0xf,0xf,0x0,0xc0,0xc1,0xff,0x0,
0xf0,0xff,0x1f,0xf0,0xff,0x3f,0xf8,0xf8,0x80,0xf,0xf,0xfe,0xff,0xc1,0xff,0x0,
0xf0,0xff,0x1f,0x78,0x0,0x38,0xf8,0xf8,0x80,0xf,0xf,0xfe,0xff,0xc1,0xff,0x0,
0xf0,0xff,0x1f,0x38,0x0,0xf0,0xf8,0xf8,0x80,0xf,0xf,0xfe,0xff,0xc1,0xff,0x0,
0xf0,0xff,0x1f,0x3c,0x0,0xf0,0xf8,0xf8,0x80,0xf,0x1f,0xfc,0xff,0xc1,0xff,0x0,
0xf0,0xff,0x1f,0x1c,0x0,0xf0,0xf9,0xf8,0x80,0xf,0x1f,0xfc,0xff,0xc1,0xff,0x0,
0xf0,0xff,0x1f,0x1c,0x0,0xf0,0xf9,0xf8,0x80,0xf,0x3f,0xf8,0xe1,0xc1,0xff,0x0,
0xf0,0xff,0x1f,0x1e,0x0,0xf0,0xfb,0xf8,0x80,0xf,0x7f,0x0,0xf0,0xc1,0xff,0x0,
0xf0,0xff,0x1f,0x1e,0x0,0xe0,0xfb,0xf8,0x80,0xf,0x7f,0x0,0xf8,0xc1,0xff,0x0,
0xf0,0xff,0x1f,0x1e,0x0,0xc0,0xfb,0xf8,0x80,0xff,0xff,0x3,0xfe,0xff,0xff,0x0,
0xf0,0xff,0x1f,0x0,0x0,0x0,0x0,0x0,0x80,0xff,0xff,0xff,0xff,0xff,0xff,0x0,
0xf0,0xff,0x1f,0x0,0x0,0x0,0x0,0x0,0x80,0xff,0xff,0xff,0xff,0xff,0xff,0x0,
0xf0,0xff,0x1f,0x0,0x0,0x0,0x0,0x0,0x80,0xff,0xff,0xff,0xff,0xff,0xff,0x0,
0xf0,0xff,0x1f,0x0,0x0,0x0,0x0,0x0,0x80,0xff,0xff,0xff,0xff,0xff,0xff,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
};



int Display (unsigned int flag)
{            
	MENU_T menu;
	int opt=0;
	int selItem  = 0;
	int acceptKbdEvents = TRUE;
	int maxEntries = 0;

	autoflag=flag;
	 if(flag==2)
		{
		menu.start                      =       0;
		menu.maxEntries                =        6;
		maxEntries                      =       menu.maxEntries;                                                       
        	strcpy(menu.title, "Display Menu "); 
        	strcpy(menu.menu[0], "LCD Test");
		strcpy(menu.menu[1], "Backlight Time");
		strcpy(menu.menu[2], "LCD Contrast"); 
		strcpy(menu.menu[3], "Display BMP"); 
		strcpy(menu.menu[4], "Buzzer test");
		strcpy(menu.menu[5], "Backlight intensity");

                                                                     
		
       	 while(1){	
		opt = scroll_menu(&menu,&selItem,acceptKbdEvents);
		switch(opt){
			case CANCEL:
	 			return 0;                 
			case ENTER:
				case 1: case 2: case 3: 
				switch (selItem+1){



					case 1:
						lk_dispfill();
                                                sleep(5);
						break;
					case 2: 
						backlight_Time();
						lk_dispclr();
						break;                                                            
					case 3:
						contrast();
						break; 
					case 4:
        					lk_dispbmp(0,0,127,63,logo);
						lk_displineclr(4);
						lk_displineclr(4);
						lk_disptext(4,0," 1234567890ABCDEFGH ",0);
						lk_disptext(5,0," IJKLMNOPQRSTUVWXYZ ",0);
						lk_getkey();	
						break;
                                       
					case 5: 
                                        {
                                        lk_buzzer(5);
                                        }
                                             break;
                                  
					case 6:
					{
						backlight_Intensity();
						break;
					}     
	                            
				}
			default : break;
		}//switch
	}
	//	return 0;
		//while 
	}//if 


	else if(flag==1)
	{
						lk_dispfill();
                                                sleep(5);
						backlight_Time();
						lk_dispclr();
						contrast();
        					lk_dispbmp(0,0,127,63,logo);
						lk_displineclr(4);
						lk_displineclr(4);
						lk_disptext(4,0," 1234567890ABCDEFGH ",0);
						lk_disptext(5,0," IJKLMNOPQRSTUVWXYZ ",0);
                                                sleep(3);




	} 

	return 0 ;     
}

int backlight_Time ( void )           // backlight testing
{

	int  bklight_time=4,ret; 		//default 
	unsigned char btime[3]="04";
	if(autoflag==2)
	{
	        lk_dispclr();
        	lk_disptext(2,0,"Enter Backlight Time",0);
		ret=lk_getnumeric(4,0,btime,2,strlen(btime));
		fprintf(stderr,"ret val %d\n",ret);
		if(btime!=NULL)
		bklight_time=atoi(btime);
	
	}
	else  if(autoflag==1)
	{
	        lk_dispclr();
        	lk_disptext(2,0,"Auto backlight Time Test secs is 4",0);
	}
   	lk_bkl_timeout(bklight_time);
	sleep(3);
	return 0;

}

int backlight_Intensity(void)
{

        int opt=0;
        MENU_T menu;
        int selItem  = 0;
        int acceptKbdEvents = TRUE;
        int maxEntries = 0;
       
	lk_dispclr();
	menu.start	= 0;
        menu.maxEntries = 2;
        maxEntries      = menu.maxEntries;
                                                                                                                            
        strcpy(menu.title, "Backlight Menu");
        strcpy(menu.menu[0], "Increase intensity");
        strcpy(menu.menu[1], "Decrease intensity");
	if(autoflag==1)
	{
        	lk_disptext(2,0,"Auto backlight Intensity Test",0);
	        while(1){
				
				if(bkl_intensity <=9)
				{
					increase_intensity();
					sleep(1);
				}
				else break;
			}
		while(1)	
			{
				if(bkl_intensity >=4)
				{
					decrease_intensity();
					sleep(1);
				}
				else break;
        	        }

	}
	else if(autoflag==2)
	{

	        while(1){
			opt = scroll_menu(&menu,&selItem,acceptKbdEvents);
             		switch(opt){
                		case CANCEL:
					lk_dispbklight(3);
                        		return 0;
	                	case ENTER:
        	        		case 1: case 2: 
                	         	switch (selItem+1){
                        			case 1:
                                			lk_dispclr();
                                			increase_intensity();
                                			break;
	                        		case 2:
        	                        		lk_dispclr();
                	                		decrease_intensity();
                        	        		break;
                        		}
	                        default : break;
        	        }
		}

	}
	
}

int increase_intensity(void)
{
	printf("intensity=%d\n",bkl_intensity);	
	if(bkl_intensity > 3)
		bkl_intensity=3;
	
	printf("intensity=%d\n",bkl_intensity);	
	lk_dispbklight(bkl_intensity++);
        if(bkl_intensity==4)
                bkl_intensity=3;
       	return 0;
}

int decrease_intensity(void)
{
	printf("intensity=%d\n",bkl_intensity);	
	if(bkl_intensity < 1)
		bkl_intensity=0;
	printf("intensity=%d\n",bkl_intensity);
	
		
	lk_dispbklight(bkl_intensity--);
	if(bkl_intensity==255)
		bkl_intensity=0;
       	return 0;
}
/*************************************************************************************
                                                                                                                             
 Menu    :   CONTRAST
                                                                                                                             
 Submenu :    1. Increment Contrast
              2. Decrement Contrast
              3. Exit 

******************************************************************************************/
int contrast(void)   // Other options
{
        int opt=0;
        MENU_T menu;
        int selItem  = 0;
        int acceptKbdEvents = TRUE;
        int maxEntries = 0;

        menu.start      = 0;
        menu.maxEntries = 2;
        maxEntries      = menu.maxEntries;

        strcpy(menu.title, "Contrast Menu");
        strcpy(menu.menu[0], "Increment contrast");
        strcpy(menu.menu[1], "Decrement contrast");
        while(1){
                opt = scroll_menu(&menu,&selItem,acceptKbdEvents);
                switch(opt){
                        case CANCEL:
	
				lk_lcdintensity(24);
                                return 0;
                        case ENTER:
                                case 1: case 2:

                                switch (selItem+1){
                                        case 1:
                                                lk_dispclr();
                                                increment_contrast();
                                                break;
                                        case 2:
                                                lk_dispclr();
                                                decrement_contrast();
					
                                                break;
                                }
                        default : break;
                }
        }
}

int increment_contrast(void)
{
        if(intensity >63)
                intensity=24;

        lk_lcdintensity(intensity++);
        return 0;
}

int decrement_contrast(void)
{
        if(intensity <= 10)
                intensity=24;

        lk_lcdintensity(intensity--);
        return 0;
}
                                                                                                              



int logoload()                  
                        
{                               
     lk_dispclr();      
     lk_disptext (3,4,"Send Logo From",0);
     lk_disptext (4,7,"PC Side",0);
                                 
     lk_disptext (1,3,"Logo Download",1);
     system ("/home/devkermit -ira /mnt/sysuser/logo.h");
                                
                                
                                
     lk_dispclr() ;             
     lk_disptext (2,1,"Logo downloaded",1) ;
     lk_getkey();               
     return 0 ;         
                                 

}
 
