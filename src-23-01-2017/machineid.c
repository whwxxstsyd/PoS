#include <header.h>

int uid(unsigned char * );

int Machineid  (void)
{
        int key;

	unsigned char buff[24]="";
                                                                                                                             
        while (1)
        {
        lk_dispclr();
        lk_disptext(1,0,"Machine ID MENU",0);
                                                                                                                             
        lk_disptext(2,2,"1.Hardware ID",0);
        lk_disptext(3,2,"2.Terminal ID",0);
	lk_disptext(4,2,"3.UID",0);
                                                                                                                             
        lk_disptext(5,0,"Enter Your Option",0);
                                                                                                                             
                key = lk_getkey();
                                                                                                                             
                if (key == 1)
                        hwid();
                else if (key == 2)
			pinpadid();
		else if (key==3)
			{
				 lk_dispclr();
				if( uid(buff)==-1)
       				lk_disptext(2,2,"Unable to get UID",1);
        
       				else 
        			{	lk_disptext(2,6," UID IS",1);
        				lk_disptext(4,3,buff,0);
					fprintf(stderr,"UID IS  %s",buff);
					fprintf(stderr,"\n");
        			}
				lk_getkey();
			}
			
                else if (key == CANCEL)
                        break;
        }
                                                                                                                             
        return 0;
}

int pinpadid (void)
 {
     int key=0;
     char machineid[20]="";

     key=lk_getpinpadid(machineid);

     machineid[10]='\0';
     
     if(key==-1)   // if machine is not available
      {
        fprintf(stderr,"\nMACHINE ID NOT AVAILABLE\n");
        lk_dispclr();
        lk_disptext(2,6,"MACHINE ID",0);
        lk_disptext(3,4,"NOT AVAILABLE",0);
        lk_getkey();
        return -1;
      }

    fprintf(stderr,"\n MACHINE ID  = %s\n",machineid);
    
    lk_dispclr();
    lk_disptext(1,5,"MACHINE ID",1);
    lk_disptext(3,5,machineid,1);
    lk_getkey();  // waiting for key
   
    return SUCCESS;

 }

int hwid()
 {

     int key=0;
     char hwid[20]="";

     key=lk_gethwid(hwid);
     hwid[8]='\0';
     if(key==-1)   // if machine is not available
      {
        fprintf(stderr,"\nHWID IS NOT AVAILABLE\n");
        lk_dispclr();
        lk_disptext(2,8,"HWID",0);
        lk_disptext(3,4,"NOT AVAILABLE",0);
        lk_getkey();
        return -1;
      }
    fprintf(stderr,"\nHWID ID  = %s\n",hwid);
    lk_dispclr();
    lk_disptext(1,5,"HWID",1);
    lk_disptext(3,5,hwid,1);
    lk_getkey();  // waiting for key

    return SUCCESS;

 }		

int uid(unsigned char *buff)
{
	FILE *fp;
	memset(buff,0x00,24);	
	fp=fopen("/proc/uid","r");
	
	if (fp==NULL)
	return -1;

	if ( fgets(buff,17,fp)==NULL)
	return -1;

	

	return 0;

}
	
	
	
	
