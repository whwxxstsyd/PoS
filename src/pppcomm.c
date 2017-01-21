/************************************************************************************************

Copyright(c)2006, Linkwell Telesystems (P) Ltd
1-11-252/1/A, Gowra Klassic, Begumpet
Hyderabad 500016 INDIA
                                                                                                 
Author: SWATHI K
Dept: Research & Development
Created on: Nov 26 ,2006
File Name: pppcomm.c
Description:
* This file contains the funtions related to the PPP connection.
* It contains the Functions like ppp open,ppp close,ppp settings.
* Funs for uploading and Downloding Data using CURL Utility.

************************************************************************************************/
#define err_printf printf
#include<curl.h>

//#include "/home/swathi/projects/MMFSL/include/curl.h"
//#include "/home/swathi/projects/MMFSL/include/mmfsl_new.h"
#include<errno.h>
#define TIMEOUT 15
unsigned char PPP_SET_FLAG=0;
extern int errno;
/*int pppdial_gprs(char *dialno)
{
	char str[1000];
	FILE *rfp;

	sprintf(str,"#!/bin/sh\nTELEPHONE=\"%s\" \nexport TELEPHONE \nrm -f /var/run/ppp.link \nexec /usr/sbin/pppd    \\\n        debug /dev/ttyS0  \\\n        9600 0.0.0.0:0.0.0.0  \\\n        connect /etc/ppp/ppp-on-dialer",dialno);

	rfp = fopen("/etc/ppp/dialout","w");
	if(rfp<0)
		return -1;
	
	fprintf(rfp,"%s",str);
	fclose(rfp);
	return 0;
}

int ppp_options(char *userid, char *password)
{
	char str[1000];
	FILE *rfp;

	sprintf(str,"-detach\nlock\nasyncmap 0\ncrtscts\ndefaultroute\nmodem\nmru 552\nmtu 552\nname %s\npassword %s",userid,password);

	rfp=fopen("/etc/ppp/options","w");
	if(rfp<0) 
		return -1;
	
	fprintf(rfp,"%s",str);
	fclose(rfp);
	return 0;
}

int ppp_dial_update(char *dialno, char *gprsdomain)
{
	char str[1000];
	FILE *rfp;

	printf("DialNo=%s Gprsdomain=%s\n\n",dialno,gprsdomain);

sprintf(str,"#!/bin/sh\n/usr/sbin/chat -v      \\\n        TIMEOUT         3    \\\n        ABORT           \'\\nBUSY\\r\'      \\\n        ABORT           \'\\nNO ANSWER\\r\' \\\n        ABORT          \'\\nRINGING\\r\\n\\r\\nRINGING\\r\'    \\\n        ECHO            ON      \\\n        \'\'               AT     \\\n        \'OK-+++\\C-OK'   ATH0    \\\n        \'\'              AT+CSQ      \\\n        OK              AT+CGATT=1 \\\n        OK              \'AT+CGDCONT=1,\"IP\",\"%s\"\' \\\n       TIMEOUT         45      \\\n        OK              ATDT\'%s\'  \\\n        CONNECT         \'\'", gprsdomain, dialno);

	rfp=fopen("/etc/ppp/ppp-on-dialer","w");
	if(rfp<0) 
		return FAILED;
	else
		printf("ppp-on-dialer sucesss\n");

	printf("str = %s\n",str);
	
	fprintf(rfp,"%s",str);
	fclose(rfp);
	return SUCCESS;
}

int ppp_open()
{
	int fd9, i;
	if(PPP_SET_FLAG == 0)
	{
		err_printf ("PPP Connecting\n");
  		system ("rm -f /var/run/ppp.link");
  		system ("/etc/ppp/dialout &");
  		i = 0;
  		while (i < 35)
    		{
    			fd9 = open ("/var/run/ppp.link", O_RDONLY);
      			err_printf ("%d\n", fd9);
      			if (fd9>0 )
        		{
        			close (fd9);
          			break;
        		}
      			sleep (1);
      			i++;
    		}
   		if (i >= 35)
   		{
			ppp_close ();
		  	return FAILED;
		}
	err_printf ("PPP Connected \n");
	PPP_SET_FLAG = 1;
	}
	else
	{
		printf("PPP connection already opend\n");
	}
	 return SUCCESS;
}	

//returns 1 if ppp instantiated successfully else return 0
int ppp_close()
{
	char p_id[8];
  	char str[50]="";
  	int fd9;
	fd9 = open ("/var/run/ppp0.pid", O_RDONLY);
	if(PPP_SET_FLAG == 1)
	{
  		if (fd9)
    		{
      			read (fd9, p_id, 4);
      			p_id[4] = '\0';
      			sprintf (str, "kill %s", p_id);
      			printf ("\n%s\n", str);
      			system (str);
      			close (fd9);
      			//system("rm /var/run/ppp0.pid");
    		}
		else
			return FAILED;
		err_printf ("PPP Closed. \n");
		PPP_SET_FLAG = 0;
	}
	else
	{
		printf("ppp connection already closed\n");
	}
	sleep(2);
	return SUCCESS;
}*/

/*int GET_mesg_clear(char *http_url)
{
	CURL *curl;
	CURLcode res;
	int result = 0;
	errno=0;	
	curl = curl_easy_init();
	
	if(curl)
	{
   	 	res=curl_easy_setopt(curl, CURLOPT_URL, http_url);
		perror("1:\n");
		res=curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1);
		perror("2:\n");
        	res=curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 5);
		perror("3:\n");
        	res=curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5);
		perror("4:\n");
        	res=curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1); 
		perror("5:\n");
		getchar();	
		err_printf("Posting message...\n");
  		res = curl_easy_perform(curl); //post away!
		if(res == 0)
			result = 1;
		else
			//message was not successfully posted to server
			result = 0;
	}
	
	//there must be a corresponding curl_easy_cleanup() to curl_easy_init()
	curl_easy_cleanup(curl);
	
	return result;
}*/

/*int GET_mesg_ssl(char *https_url)
{
	CURL *curl;
	CURLcode res;
	int result = 0;
		
	curl = curl_easy_init();
	
	if(curl)
	{
   	 	curl_easy_setopt(curl, CURLOPT_URL, https_url);*/
		
		/*
		 * If you want to connect to a site who isn't using a certificate that is
		 * signed by one of the certs in the CA bundle you have, you can skip the
		 * verification of the server's certificate. This makes the connection
		 * A LOT LESS SECURE.
		 *
		 * If you have a CA cert for the server stored someplace else than in the
		 * default bundle, then the CURLOPT_CAPATH option might come handy for
		 * you.
		 */
//		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
		
		/*
		 * If the site you're connecting to uses a different host name that what
		 * they have mentioned in their server certificate's commonName (or
		 * subjectAltName) fields, libcurl will refuse to connect. You can skip
		 * this check, but this will make the connection less secure.
		 */
/*		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
	
		err_printf("Posting message...\n");
  		res = curl_easy_perform(curl); //post away!
		if(res == 0)
			result = 1;
		else
			//message was not successfully posted to server
			result = 0;
	}
	//there must be a corresponding curl_easy_cleanup() to curl_easy_init()
	curl_easy_cleanup(curl);
	
	return result;
}*/

//the http_url could also be a file!
int GET_file_clear(char *http_url, char *filename)
{
	int result;
/*	CURL *curl;
	CURLcode res;
	FILE *out_fd = (FILE *) 0;
	int result = 0;
	errno=0;
	curl = curl_easy_init();	
	if(curl)
	{
		perror("1:\n");
   	 	err_printf("Downloading %s file...\n", filename);
		out_fd = fopen (filename, "w");//open for read and write			
		perror("2:\n");
		res=curl_easy_setopt(curl, CURLOPT_FILE, out_fd);
		perror("3:\n");
        	res=curl_easy_setopt(curl, CURLOPT_TIMEOUT, 60);
		perror("4:\n");
    		//curl_easy_setopt(curl, CURLOPT_HEADER, 0);
    		res=curl_easy_setopt(curl, CURLOPT_URL, http_url);
		perror("5:\n");
		res=curl_easy_setopt(curl,CURLOPT_USERPWD,"Pilot:Pilot123");
		perror("6:\n");
  		res = curl_easy_perform(curl); //post away!
		if(res == 0)
			result = 1;
		else
			//message was not successfully posted to server
			result = 0;
		fclose(out_fd);
		perror("7:\n");
	}
	//there must be a corresponding curl_easy_cleanup() to curl_easy_init()
	curl_easy_cleanup(curl);
	perror("8:\n");
*/	
	return result;
}

//the https_url could also be a file!
/*int GET_file_ssl(char *https_url, char *filename)
{
	CURL *curl;
	CURLcode res;
	FILE *out_fd = (FILE *) 0;
	int result = 0;
	
	curl = curl_easy_init();	
	if(curl)
	{
   	 	err_printf("Downloading %s file...\n", filename);
		out_fd = fopen (filename, "w");//open for read and write			
		curl_easy_setopt(curl, CURLOPT_FILE, out_fd);
    		curl_easy_setopt(curl, CURLOPT_HEADER, 0);
    		curl_easy_setopt(curl, CURLOPT_URL, https_url);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);

  		res = curl_easy_perform(curl); //post away!
		if(res == 0)
			result = 1;
		else
			//message was not successfully posted to server
			result = 0;
		fclose(out_fd);
	}
	//there must be a corresponding curl_easy_cleanup() to curl_easy_init()
	curl_easy_cleanup(curl);
	
	return result;
}*/
