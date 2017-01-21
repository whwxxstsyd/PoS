#include <header.h>

int MagHead_test()
{

	int opt=0,ret;
	MENU_T menu;
	char event;


	int selItem  = 0;
	int acceptKbdEvents = TRUE;
	int maxEntries = 0;
	short scroll = 0;

	menu.start                      =       0;
	menu.maxEntries                 =       3;
	maxEntries                      =       menu.maxEntries;

	strcpy(menu.title, "Swipe Card Menu");

	strcpy(menu.menu[0],"Read Track-1" );
	strcpy(menu.menu[1],"Read Track-2" );
	strcpy(menu.menu[2],"Read Track-3" );

	while(1)
	{
		opt = scroll_menu(&menu,&selItem,acceptKbdEvents);


		switch(opt)
		{
			case CANCEL:

				return;
			case ENTER:
			case 1: case 2:
				system("rmmod d14");
				usleep(10);
				system("insmod /home/d14.ko");


				switch (selItem+1)
				{

					case 1:
						read_track1();
						break;
					case 2:
						read_track2();
						break;
					case 3:
						read_track3();
						break;
				}

			default : break;

		}
	}

}

     // Track1 -----  Magnetic swipe //


int read_track1()
{
        int evnt;
        char track1[256], track2[256],track3[256];

	memset(track1,0x00,256) ;
	memset(track2,0x00,256) ;
	memset(track3,0x00,256) ;

        lk_dispclr();
        lk_disptext(2, 3, "Swipe The Card", 0);
                                                                                                                            
        while (1)
        {	
                evnt = mscr_getstate();
                if (evnt == 1)
                {
                   evnt = mscr_read(track1, track2,track3);
			//if(evnt != -1){
			if(evnt == 1 || evnt == 4 || evnt == 6 || evnt == 7){
                   		lk_dispclr();
                   		lk_disptext(1,0,"TRACK 1 DATA",0);
                   		lk_disptext(2,0,track1,0);
				sleep(2);
				break;
			}
         	}
		if(lk_getkey_wait()==CANCEL)
		break;
	}
        //lk_dispclr();
        //lk_disptext(2, 3, "Press any key", 0);
	//if(lk_getkey()==CANCEL)
//		break;
return 0;

}

			// Track 2 ----- Magnetic swipe //


int read_track2()
{
        int evnt;
        char track1[256], track2[256],track3[256];

	memset(track1,0x00,256) ;
	memset(track2,0x00,256) ;
	memset(track3,0x00,256) ;

        lk_dispclr();
        lk_disptext(2, 3, "Swipe The Card", 0);
                                                                                                                            
        while (1)
        {
                evnt = mscr_getstate();
                if (evnt == 1)
                {
                        evnt = mscr_read(track1, track2,track3);
			if(evnt == 2 || evnt == 4 || evnt == 5 || evnt == 7){
                        lk_dispclr();
                        lk_disptext(1,0,"TRACK 2 DATA",0);
                        lk_disptext(2,0,track2,0);
			sleep(2);
			break;	
			}
                 }
                                                                                                                            
                 if(lk_getkey_wait()== CANCEL) 
                 break;
         }
        //lk_dispclr();
        //lk_disptext(2, 3, "Press any key", 0);
         //if(lk_getkey()== CANCEL) 
  return 0;

}

			// Track 3 ---- Magnetic swipe //

int read_track3()
{
        int evnt;
        char track1[256], track2[256],track3[256];

	memset(track1,0x00,256) ;
	memset(track2,0x00,256) ;
	memset(track3,0x00,256) ;

        lk_dispclr();
        lk_disptext(2, 3, "Swipe The Card", 0);
                                                                                                                            
        while (1)
        {
                evnt = mscr_getstate();
                if (evnt == 1)
                {
                        evnt = mscr_read(track1, track2,track3);
			//if(evnt != -1){
			if(evnt == 3 || evnt == 5 || evnt == 6 || evnt == 7){
                        lk_dispclr();
                        lk_disptext(1,0,"TRACK 3 DATA",0);
                        lk_disptext(2,0,track3,0);
			sleep(2);
			break;
			}
                 }
                                                                                                                            
                 if(lk_getkey_wait()== CANCEL) 
                 break;
         }
        //lk_dispclr();
        //lk_disptext(2, 3, "Press any key", 0);
        //if(lk_getkey()== CANCEL) 
  	return 0;

}
