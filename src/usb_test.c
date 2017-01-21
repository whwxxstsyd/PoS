#include<header.h>
int usbmount=0;
int usb_test(void)
{
	int key;
		
	while (1)
        {
		lk_dispclr();
		lk_disptext(1,0,"USB TEST MENU",0);
			
		lk_disptext(2,4,"1.Devices",0);
		lk_disptext(3,4,"2.Barcode",0);
		lk_disptext(4,4,"3.Mass Storage",0);

		key = lk_getkey();

		if (key == 1){
			usb_detect(); }

		else if (key == 2 )
			{	
			sleep(1); //device has to be ready after giving power
			scan_barcode();	
			sleep(1);
			
			}

		else if (key == 3 ){
			mass_storage();
			}	
		else if ( key == CANCEL )
			break;
	 }

	return SUCCESS;

}
	
