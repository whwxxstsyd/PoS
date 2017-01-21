#include <header.h>

int audio_test (void)
{
         MENU_T menu;

        int opt=0;
        int selItem  = 0;
        int acceptKbdEvents = TRUE;
        int maxEntries = 0;
        char text[256];
	int i,key,kee;
	static int count=192;	
	char buff[80]="";	

	int fd9;
	

	char str[48]="",p_id[8]="";
	char ss[24];

        menu.start                      =       0;
        menu.maxEntries                 =       3;
        maxEntries                      =       menu.maxEntries;
        strcpy(menu.title, "Display Menu");
        strcpy(menu.menu[0], "Play Music");
        strcpy(menu.menu[1], "Play Song");
	strcpy(menu.menu[2], "Sine Wave");
		
	
        while(1)
        {
                opt = scroll_menu(&menu,&selItem,acceptKbdEvents);
                switch(opt)
                {
                        case CANCEL:
                        return 0;

                        case ENTER:

                        switch (selItem+1)
                        {
                                case 1:
                                        lk_dispclr();
					lk_disptext(2,1,"WAIT...",1); 	                                        
				 	lk_disptext(4,1,"F2 and F3 for Volume",1);
                                       	system("aplay /usr/share/sounds/alsa/* &"); 
	

					for (i=0;i<150;i++)
					{
						usleep(100000);
						key=lk_getkey_wait();
						if ( key == 0xff)
						continue;

						if ( key == F2 )
						{
							count+=5;
							if (count > 192 )
							count =192;
						}

				
						else  if ( key ==F3 )
						{
							count-=5;
							if (count < 130)
							count=130;
						}	

						if (key ==F3 || key == F2 )
						{
						sprintf(buff,"amixer cset numid=4 %d",count);
						system (buff);			
						}
					}			 
					
					
                                        break;
                                case 2:
					system("mp3play -m /mnt/jffs2/track.mp3 &");                                       
					sleep(2);
					system("pidof mp3play > /tmp/mpplay ");
                                        fd9 = open("/tmp/mpplay",O_RDONLY);
                                             {
                                                          kee = read(fd9,p_id,6);
                                                          p_id[kee] = '\0';		
							  close(fd9);
                                             }
					remove("/tmp/mpplay");
					if (kee<2)
					return -1;
					lk_dispclr();
                                        lk_disptext(1,1,"WAIT...",1);
                                        lk_disptext(3,1,"F2 and F3 For Volume",0);
					lk_disptext(4,1,"F1 Pause",0);
					lk_disptext(5,1,"F4 Play",0);
	
					while(1)
			
		                         {
						if (system("pidof mp3play >/dev/null 2>&1 ")==256)
					        break;
                                                usleep(100000);
                                                key=lk_getkey_wait();
                                                if ( key == 0xff)
                                                continue;

                                                if (key==CANCEL)
						{
							  sprintf(str,"kill -18 %s",p_id);
							  sprintf(ss,"kill -1 %s",p_id);	
        						  system(str);
							  system(ss);
							break;
						}
                                                if ( key == F2 )
                                                {
                                                        count+=5;
                                                        if (count > 192 )
                                                        count =192;
                                                }


                                                else  if ( key ==F3 )
                                                {
                                                        count-=5;
                                                        if (count < 100)
                                                        count=100;
                                                }

                                                if (key ==F3 || key == F2 )
                                                {
                                                sprintf(buff,"amixer cset numid=4 %d",count);
                                                system (buff);
                                                }

						if (key== F1 || key == F4 )
						{
							  if(key==F4) 	
                                                          sprintf(str, "kill -18 %s", p_id);
							  else if (key==F1) 
							  sprintf(str, "kill -19 %s", p_id);  		
                                                          system(str);
                                                 }

							
			
						}

                                        break;

				case 3:
                                        lk_dispclr();
                                        lk_disptext(2,1,"WAIT...",1);
                                        lk_disptext(4,1,"F2 and F3 for Volume",1);
                                        system("aplay /usr/share/sounds/Test.wav  &");


                                        for (i=0;i<70;i++)
                                        {
                                                usleep(100000);
                                                key=lk_getkey_wait();
                                                if ( key == 0xff)
                                                continue;

                                                if ( key == F2 )
                                                {
                                                        count+=5;
                                                        if (count > 192 )
                                                        count =192;
                                                }


                                                else  if ( key ==F3 )
                                                {
                                                        count-=5;
                                                        if (count < 130)
                                                        count=130;
                                                }

                                                if (key ==F3 || key == F2 )
                                                {
                                                sprintf(buff,"amixer cset numid=4 %d",count);
                                                system (buff);
                                                }
                                        }


                                        break;

					

	                        default : break;
                	}

        	}
        return SUCCESS;
	}
}


