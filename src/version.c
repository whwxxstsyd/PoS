#include <header.h>
#include <version.h>
int versioninfo(void)
{

      int opt=0;
      MENU_T menu;
      int selItem  = 0;
      int acceptKbdEvents = TRUE;
      int maxEntries = 0;
      
      menu.start                      =       0;
      menu.maxEntries                 =       4;
      maxEntries                      =       menu.maxEntries;

	char buff[80]="";


      strcpy(menu.title, "Version Menu");
                                                                                                                            
      strcpy(menu.menu[1],"Kernel ver" );
      strcpy(menu.menu[2],"Rootfs ver");
      strcpy(menu.menu[3],"Appl ver");
      strcpy(menu.menu[0],"Boot-loader ver");

      while(1)
      
      { 
         lk_dispclr();
         opt = scroll_menu(&menu,&selItem,acceptKbdEvents);
                                                                                                                            
         switch(opt)
           {
              case CANCEL:
                          return 0;
              case ENTER:
                        switch (selItem+1)
                         {
                        
                         case 2: 
				lk_dispclr();
				lk_disptext(2,2,"Kernel Details",0);
				if ( kernel_details(buff)< 0 )
				lk_disptext(4,2,"Unable to Get Details",0);
				else 
        			lk_disptext(4,0,buff,0); 
                                break;

                         case 3:
				lk_dispclr();
                                lk_disptext(2,2,"Rootfs Details ",0);
                                if ( rootfs_details(buff)< 0 )
                                lk_disptext(4,2,"Unable to Get Details",0);
                                else
                                lk_disptext(4,0,buff,0); 
                                break;
                         case 4:
                               lk_dispclr();
                               lk_disptext(2,0,"Application Details",0);
                               lk_disptext(4,2,"GL14-SD-APP-1031-3.5.IMG",0);
                               break;
                         case 1:
				lk_dispclr();
				lk_disptext(2,2,"U-boot Details",0);

			       	if (bootloader_details(buff)<0)
				
				lk_disptext(4,2,"Unable to Get Details",0);
				else     lk_disptext(4,0,buff,0);
					
					
                               break;
			
                       }
                }
           lk_getkey();
        }

	return 0;
}


