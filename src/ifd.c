#include <header.h>

union
{
 unsigned int temp;
 struct
   {
     unsigned char lsb;  //datalen lower byte.
     unsigned char msb;  //datalen higher byte.
   } uc;
} ui;

int card_select(int sel);
static int rlen=0;
int i;
int RLen;
int recordno1=0;
//int sam_test() 
Ifd_test() 
{
	int repeflag=0,ret=0,res=0,count=0,RLen=0,len=0,tmp=0,brflag,option=0;
	unsigned char buffer[255]="";

	unsigned char cmd[][15]={{0x00,0x20,0x00,0x00,0x05,0x55,0x55,0x55,0x55,0x55},//verify
		{0x00,0xDA,0x00,0x00} ,//write
		{0x21,0x00,0x00,0x05,0x55,0x55,0x55,0x55,0x55},//change password
		{0xDC,0x00,0x01,0x05,0x05,0x04,0x03,0x02,0x01},//update/
		{0x00,0xca,0x00,0x03,0x42},//read
		{0x00,0x22,0x00,0x00,0x02},//read records
		{0x00,0x9C,0x00,0x00,0x00} //format
	};
	unsigned char temp[5];
	unsigned char Wrtbuf[100],temp_buf[100];


	ret=SAM_Open();
	if(ret<0)
	{
		lk_dispclr();
		lk_disptext(2,0,"IFD Open Failed ",0);
		lk_getkey();
	}

start:	

	lk_dispclr();
	lk_disptext(1,0,"IFD Menu",0);
	lk_disptext(2,2,"1.CARD1",0);
	lk_disptext(3,2,"2.CARD2",0);

	lk_disptext(5,0,"Enter Your Option",0);		

	while (1)
	{
		res = lk_getkey();	

		if(res==1) {    
			tmp=card_select1(1); 
			if(tmp==-1)
				return -1;
			if(tmp == 3)
				option=1;
			break; 
		}

		if(res==2) 
		{ 
			tmp=card_select1(2); 
			if(tmp==-1)
				return -1;
			if(tmp == 3)
				option=1;
			break;
		}


		if(res==CANCEL)  {SAM_Close() ;return ERROR;}
		if((res!=CANCEL) && (res!=1) && (res!=2))

		{
			lk_dispclr();
			lk_disptext(5,0,"Entered Wrong Option",0);
			option=1;break;
		}

	}
	if(option)goto start;		
	//		brflag=0;
	res=SAM_GetAtr(&len,buffer);
	if(res<0)
	{
		lk_disptext(1,0,"NO ATR RECEIVED ",0);
		lk_disptext(2,0,"CARD MAY BE ABSCENT",0);
		lk_disptext(3,0,"INSERT CARD and TRY AGAIN ",0);
		sleep(2);		
		return 0;       
	}


repe:

	lk_dispclr();
	lk_disptext(1,2,"1.Write Record",0);
	lk_disptext(2,2,"2.Read Record",0);	
	lk_disptext(3,2,"3.No.of Records",0);
	lk_disptext(4,2,"4.Format Card",0);
	lk_disptext(5,0,"Enter Your Option",0);

	while (1)
	{

		res=lk_getkey();	

		if(res==CANCEL) 
		{
			SAM_Poweroff(); 
			repeflag=0; brflag=1; goto start; 
		}

		else if ( res > 0  &&  res < 5 )
			break;
	}


	switch(res)
	{
		case 0x01:

			RLen=0;
			res=SAM_SendCommand(cmd[0],10,buffer,&RLen);
			if(res <0)
			{
				printf (" IFD_sendcommand Error\n");
				lk_dispclr() ;
				lk_disptext(2,0,"IFD SEND COMMAND ERROR");
				SAM_Close();
				return -1;
			}

			lk_dispclr();
			memset(temp_buf,0,100);

			memset(Wrtbuf,0,100);
			unsigned char DATA[50]="";
			unsigned char data[50]="";
			memset(data,0,50);
			strcpy(data,temp_buf);

			count=lk_getalpha(2,0,temp_buf,15,strlen(data),0);
			if(count<0)
			{
				lk_dispclr();
				lk_disptext(2,0,(unsigned char *)"Operation Cancel",0);
				sleep(1);
				repeflag=1;	
				break;	
			}
			if(count>0)
			{

				temp_buf[count]='\0';
				memcpy(Wrtbuf,&cmd[1][0],4);
				Wrtbuf[4]=count;
				memcpy(&Wrtbuf[5],temp_buf,count);
				Wrtbuf[count+5]='\0';
			}

			lk_dispclr();

			RLen=0;

			SAM_SendCommand(Wrtbuf,(count+5),buffer,&RLen);
			repeflag=1;
			break;

		case 0x02:

			lk_dispclr();
			memset(temp,0,5);
			RLen=66;
			lk_disptext(2,2,"Enter Record No",0);
			res=lk_getnumeric(4,0,temp,4,strlen(temp),4);
			if(res<=0){
				lk_dispclr();
				lk_disptext(2,0,(unsigned char *)"Operation Cancel",0);
				sleep(1);

				SAM_Close();
				repeflag=1;
				break;
			}
			temp[res]='\0';
			recordno1=atoi((const char*)temp);
			printf("recordno1=%d temp[0]=%c\n",recordno1,temp[0]);
			cmd[4][3]=recordno1;

			if(SAM_SendCommand(cmd[4],5,buffer,&RLen)==ERROR)
			{

				lk_dispclr();
				lk_disptext(2,0,"Record Not Present",1);
				sleep(2);
				SAM_Close();

			}


			for(i=0;i<20;i++) {
				if(buffer[i] == 0xFF)
					buffer[i] = 0;
			}
			lk_dispclr();
			lk_disptext(1,0,(unsigned char *)"Record Data :",0);
			lk_disptext(2,0,(unsigned char *)buffer,0);
			sleep(2);

			repeflag=1;
			break;

		case 0x03:
			RLen = 2;
			res=SAM_SendCommand (cmd[5],5,buffer,&RLen);   // Read No.Of Records
			if(res < 0){
				printf ("SCR_SendCommand Error \n") ;
				SAM_Close();
				return -1 ;
			}






			memset(temp,0,5);
			lk_dispclr();
			lk_disptext(1,0,(unsigned char *)"NO OF RECORDS :",0);
			sprintf((char *)temp," %d%d",buffer[0],buffer[1]);
			lk_disptext(2,0,(unsigned char *)temp,0);
			sleep(2);


			repeflag=1;
			break;

		case 0x04:
			rlen=68;
			lk_dispclr();
			lk_disptext(2,3,(unsigned char *)"Formatting .. ",1);

			res=SAM_SendCommand (cmd[6],5,buffer,&RLen);   // Format
			if(res < 0){
				printf ("SCR_SendCommand Error \n") ;
				SAM_Close();
				return -1 ;
			}

			printf ("Receive Buffer: ") ;
			for (i=0;i<6;i++)
				printf ("%02x ",buffer[i]) ;
			printf ("\n") ;


			repeflag=1;
			break;
		default:
			repeflag=1;
			break;
	}//switch
	if(repeflag==1)goto repe;

	//	if(brflag==1)goto start;

	SAM_Close();

	return SUCCESS;
}


int card_select1(int sel)
{

	int key=0,ret=0,i=0;
	char ch[2]="";
	lk_dispclr();
	int selection=0;
	switch(sel)
	{


		case 1: lk_dispclr();
			lk_disptext(2,0,"1.Card1 5v",0);
			lk_disptext(3,0,"2.Card1 3v",0);
			//lk_disptext(4,0,"3.Card1 1.8v",0);
			key=lk_getkey();
			selection=key;
			if(key==CANCEL)
			{
				return -1;
			}
			break;
		case 2:
			lk_dispclr();
			lk_disptext(2,0,"1.Card2 5v",0);
			lk_disptext(3,0,"2.Card2 3v",0);
			//lk_disptext(4,0,"3.Card2 1.8v",0);
			key=lk_getkey();
			selection=key+3;
			if(key==CANCEL)
			{ 
				return -1;
			}
			break;


		default : break;

	}

	if((key == 1) || (key == 2))
	{

		ret = SAM_ColdReset(selection);

		if(ret)
		{
			lk_dispclr();
                        lk_disptext(2,0,"IFD PowerUP failed",0);
                        lk_disptext(3,0,"ATR not received..",0);
                        lk_disptext(4,0,"check SIM presence",0);

                        SAM_Poweroff();
                        SAM_Close();

                        lk_getkey();
			fprintf(stderr,"IFD PowerUP Failed\n");
			return ERROR;

		}
		else if(ret==0)
		{
			lk_dispclr();
			lk_disptext(2,0,"IFD SUCCESSFULY POWERUP",0);
			printf("IFD SUCCESSFULY POWERUP ");
			sleep(2);
		}
	}	
	else return 3;

	return 0;
}
