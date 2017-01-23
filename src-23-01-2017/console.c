#include <header.h>

int Console_menu( void )  
{
        int opt=0;
        MENU_T menu;
        char event;
                                                                                                                            
        int selItem  = 0;
        int acceptKbdEvents = TRUE;
        int maxEntries = 0;
        short scroll = 0;
                                                                                                                            
                                                                                                                            
        menu.start                      =       0;
        menu.maxEntries                 =       2;
        maxEntries                      =       menu.maxEntries;
                                                                                                                            
        strcpy(menu.title, "Console Menu");
        strcpy(menu.menu[0],"1.Serial Console" );
        strcpy(menu.menu[1],"2.USB Console ");
                                                                                                                            
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
                                serial_console();
                                break;
                                                                                                                            
                        case 2 :
                                usb_console();
                                break;
                        }
                default : break;
                }
        }
        return 0;
}

int serial_console(void)
{
	int ret ;

        ret = system("/sbin/serialconsole") ;
        if(ret!=0){
                fprintf(stderr,"Serial console enable problem\n") ;
                return -1 ;
        }
	sleep(20) ;
	return 0 ;
}	

int usb_console(void)
{
	int ret ;

        ret = system("/sbin/usbconsole") ;
        if(ret!=0){
                fprintf(stderr,"USB console enable problem\n") ;
                return -1 ;
        }
	sleep(20) ;
	return 0 ;
}	
