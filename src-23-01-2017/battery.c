#include<header.h>
int Battery (unsigned int flag)
{
	FILE *fp;
	int i;
  	float val,cnt; 
  	char str[5],bat[4],message[40]="";
  
	fp = fopen ("/proc/battery","r") ;  
  	fread (str,4,1,fp);

  	bat[0]=str[0];
  	bat[1]=str[1];
  	bat[2]=str[2];
  	bat[3]=str[3];
  	bat[4]='\0';
	
  	i= atoi (bat);
//	printf("%s  %i \n",bat,i);

  	cnt=(float) 8.4/4096;
  	val = i*cnt; 

  	sprintf(message,"VOLTAGE = %0.2fV ",val);  
  	lk_dispclr();
  	lk_disptext(1,4,"BATTERY ",0);
  	lk_disptext(3,2,message,1);
	if(flag==2)
	{
	lk_disptext(5,0,"Press Any Key to Exit",0); 
	lk_getkey();
	}
	else if(flag==1)
	{
		sleep(2);
	}
  	return 0;
 
}
