/* ==========================================================
 * Company Name: Linkwell Telesystems Pvt. Ltd (visiontek.co.in)
 * API Description: GL14POS LCD, KPD and RTC APIs.  
*/
#ifndef LCDKPDRTC_H
#define LCDKPDRTC_H

int lk_open(void) ;
/* Description:
 * 	This API Function is used to open LCD and Keypad devices. 
 * Note: This function must be called before any LCD and Keypad functions.
 * Parameters: 
 * 	None
 * Return Values: 
 * 	0 on Success.
 * 	-1 on failure. 
 */ 

void lk_dispclr(void) ; 
/* Description: 
 * 	This API Function clears all pixels on LCD.
 * Note: This function must be called explicitly after lk_open to clear LCD
 * Parameters: 
 * 	None.
 * Return Values: 
 * 	None.
 */

void lk_dispfill (void) ;
/* Description: 
 * 	This API Function fills all pixels on LCD.
 * Parameters: 
 * 	None.
 * Return Values: 
 * 	None.
 */

int lk_displineclr (unsigned char line_no) ;
 
/* Description: 
 * 	This API Function Clears pixels of the Specified line on LCD.
 * Parameter: 
 * 	Line_no: 
 * 		Description: line number to clears the LCD.
 *  		type: Input 
 * 		Range: 0 - 5 
 * Return Values:   	
 *      '0' on Success.
 *     	'-1' on Error.
 *     	'-2' if there is argument error
 */

int lk_disptext(unsigned char line_no, unsigned char column, unsigned char *data, unsigned char font) ;
/*
 * Description: 
 * 	This API Function displays the string of data at specified line and column in a given font.
 * Parameters:
 * 	line_no:  
 * 		Description: line number to display the txt on the LCD. 
 * 		Type: Input
 * 		Range: depends on font
 * 			0-5  -> font 0;
 * 			0-4  -> font 1;
 * 			0-4  -> font 2;
 * 			0-3  -> font 3; 
 * 			 
 * 	column:  
 * 		Description: column number to Display the txt.
 * 		Type: Input
 * 		Range: 0 - 20 -> font 0, font 1; 
 * 		       0 - 9 -> font 2; 
 *		       0 - 18 -> fint 3;
 * 	data:  
 * 		Description: Buffer to display text data on LCD.
 * 		Type: Input
 * 		Range: Data Length range minimum is 1 character and maximum 124 characters, 
 * 	font:  
 * 		Description: type of font.
 * 		Type: Input
 * 		Range:  0 - 3
 * 			'0' 6x8 then each line displays 21 characters and lines range is 0-5
 * 			'1' 6x16 then each line displays 21 characters and possible 3 lines (because height is doubled)
 * 			'2' 12x8 then each line displays 10 characters and lines range is 0-4 (because width is doubled)
 * 			'3' 12x16 then each line displays 10 characters and possible 3 lines (both doubled)
 * Returns Values: 	
 * 	Number of characters Displayed on LCD
 * 	-1 on Failure.
 *     	-2 if there is arguments error
 */

void lk_close() ;
/* 
 * Description: 
 * 	This API Function is used to close device. 
*  Parameters:
*   	None.
*  Return Values:  	
*  	None.
*/

int lk_dispbmp ( unsigned char xstartcord, unsigned char ystartcord, unsigned char xendcord, unsigned char yendcord,unsigned char *bmp) ;
/* 
 * Description: 
 * 	This API Function displays the BMP Image on LCD at user given coordinates. 
 *	Windows tool provided to convert bmp to hex.
 * Parameters: 
 * 	xstartcord:
 * 		Description: Start of x co-ordinate 
 * 		Type: Input
 * 		Range: 0 - 127
 * 	xendcord: 
 * 		Description: end of x co-ordinate
 * 		Type: Input
 * 		Range: upto 127 
 * 	ystartcord:
 * 		Description: Start of y co-ordinate
 * 		Type: Input
 * 		Range: 0 - 63
 * 	yendcord:
 * 		Description: end of y co-ordinate
 * 		Type: Input
 * 		Range: upto 63
 *	bmp:  
 *		Description: Displays BMP hex data 
 *		Type: Input
 *		Range: (y) 64 x 128 (x)
 * Return Values: 
 * 	'0' on SUCCESS
 * 	-1 on Error	  
 *     	-2 if there is arguments error
 */

unsigned char lk_getkey (void) ;
/*
 * Description: 
 * 	This API Function is used to get key that is pressed. It will wait until key is pressed and returns the key value.
 *  Parameters: 
 *  	None.
 * Return Values: 
 * 	Numeric keys 
 * 	or
 * 	255
 */

int lk_dispbox (unsigned char line_no, unsigned char cmnd) ;
/*
 * Description: 
 * 	This API Function Displays Box at Specified Line. 
 * Parameters: 
 * 	line_no: 
 * 		Description: line number to display the box on the LCD. 
 * 		Type: Input
 * 		Range: 0 - 5
 *      cmnd:   
 *      	Description: cmnd should be 0x00 or 0x01. 
 *      	Type: Input
 *      	Range: 0 - 1
 *      		'0' for box
 *      		'1' for no box 
 *			Note: display text in the box after drawing box (i.e. don't draw box after write text)
 * Returns Values: 
 * 	'0' on Success
 * 	'-1' on error
 *     	'-2' if there is arguments error
 */

int lk_getalpha (unsigned char line_no, unsigned char start_pos, unsigned char *data, unsigned char max_cnt, unsigned char count,unsigned char keytype) ;
/* 
 * Description: 
 * 	This API function is used to pass a buffer with a Null string or a non-null string and the subsequent alpha numeric characters are filled from keypad entry by user. Entire String is displayed in LCD. Alpha Key is pressed to toggle among numeric and various alphabets for a single key. 
 * Parameters:  
 * 	line_no: 
 * 		Description: line number to display edit keys on the LCD.
 * 		Type: Input
 * 		Range: 0 - 5
 *	start_pos: 
 *		Description: Specifies the column position to display or to take input.
 *		Type: Input
 *		Range: 0 - 19
 *    	data: 
 *    		Description: Target buffer to be filled with edit keys data.
 *    		Type: Input / Output
 *    		Range: only 21 characters are visible if starts at 0
 *     	max_cnt: 
 *     		Description: Number of alphabets to be taken from the keypad.(maximum 21 alphabets are visible at once on display if starts at 0)
 *     		Type: Input
 *     		Range: 20 characters are visible (Limit depends on buffer size taken)	 
 *     	count: 
 *     		Description: This field signifies the length of a non-null string in the buffer. In the case of a Null String it is zero. Both start_pos and count act as a base and offset for the input from keypad.
 *     		Type: Input
 *     		Range: 0 - 20
 *   	Keytype: 
 *   		Description: edit key type (should be 0)
 *   		Type: Input
 *   		Range:	0 for shift key (Future expansion)
 * Return Values:
 *     	Number of characters entered
 *     	'0' pressed Enter key without data.
 *     	'-1' Cancel key Pressed.
 *     	'-2' if there is argument error
 */
     	
int lk_getnumeric ( unsigned char line_no, unsigned char start_pos, unsigned char *data, unsigned char max_cnt, unsigned char count) ;

/*
 * Description: 
 * 	This API function is used to pass a buffer with a Null string or a non-null string and the subsequent Numeric characters are filled from keypad entry by user. Entire String is displayed in LCD.
 * Parameters:  
 * 	line_no: 
 * 		Description: line number to display edit keys on the LCD.
 * 		Type: Input
 * 		Range: 0 - 5
 *	start_pos: 
 *		Description: Specifies the column position to display or to take input.
 *		Type: Input
 *		Range: 0 - 20
 *    	data: 
 *    		Description: Target buffer to be filled with edit keys data.
 *    		Type: Input / Output
 *    		Range: only 21 characters are visible if starts at 0
 *     	max_cnt: 
 *     		Description: Number of numerics to be taken from the keypad (maximum 21 alphabets are visible at once on display if starts at 0)
 *     		Type: Input
 *     		Range: 21 characters are visible (Limit depends on buffer size taken)	 
 *     	count: 
 *     		Description: This field signifies the length of a non-null string in the buffer. In the case of a Null String it is zero. 
 *     				Both start_pos and count act as a base and offset for the input from keypad.
 *     		Type: Input
 *     		Range: 0 - 20
 *   	Keytype: 
 *   		Description: edit key type (should be 0)
 *   		Type: Input
 *   		Range:	0 for shift key (Future expansion)
 * Return Values:
 *     	Number of characters entered
 *     	'0' pressed Enter key without data.
 *     	'-1' Cancel key Pressed.
 *     	'-2' if there is argument error
 *
 *     	NOTE: 20 character input not displayed no LCD; 
 */     	
	

int lk_getpassword (unsigned char *ptr, unsigned char line_no, unsigned char max_cnt) ;
/*
 * Description:
 * 	This API Function is used to get the password from the keypad. Digits entered will be displayed as ‘*’ on the display 
 * 	and fills the target buffer with entered digits.
 * Parameters: 
 * 	ptr: 
 * 		Description: buffer to be filled with the password entered through keyboard. 
 * 		Type: Input
 * 		Range: 21 characters ('*'s) are visible (Limit depends on buffer size taken)
 * 	Line_no: 
 * 		Description: line number to display on the LCD. 
 * 		Type: Input
 * 		Range: 0 - 5
 * 	max_cnt: 
 * 		Description: Maximum Number of digits to be taken from the keypad.
 * 		Type: Input
 * 		Range: 21 characters ('*'s) are visible (Limit depends on buffer size taken)
 * Return Values:
 * 	Number of digits entered on Success.
 * 	0 if user pressed enter key without data.
 * 	-1 if Cancel key is pressed.
 * 	-2 on the argument errors.
 */ 	

int lk_getamount (unsigned char line_no, unsigned char start_pos, unsigned char *ptr, unsigned char max_digits, unsigned char decimal_pos) ;
/*
 * Description:
 *       This API function is used to get amount from user.
 * Parameters:
 * 	line_no: 
 * 		Description: line number to display on the LCD.
 * 		Type: Input
 * 		Range: 0 - 5
 * 	start_pos: 
 * 		Description: Specifies the column position to take input.
 * 		Type: Input
 * 		Range: 0 - 20
 * 	Ptr: 
 * 		Description: Target buffer to be filled with the amount.
 * 		Type: Input
 * 		Range: 21 characters ('*'s) are visible (Limit depends on buffer size taken)
 * 	max_digits: 
 * 		Description: Maximum number of numeric characters to be taken from the keypad.
 * 		21 is the maximum numeric characters are visible at once on display if we selected Start position as 0.
 * 		Type: Input
 * 		Range: 21 characters ('*'s) are visible (Limit depends on buffer size taken)
 * 	decimal_pos: 
 * 		Description: Number of decimal positions required after decimal point + 1.Suppose we want 2 decimal positions we have 
 * 		give decimal position as 3. Range is 1 to 4(we can obtain max 3 decimal positions).
 * 		Type: Input
 * 		Range: 1 - 4
 * Return Values:
 *     	Number of characters entered
 *     	'0' pressed Enter key without data.
 *     	'-1' Cancel key Pressed.
 *     	'-2' if there is argument error
 */ 		

int lk_getrtc(struct tm *) ;
/*
 * Description:
 *     	This API Function gets the time from the RTC chip or from the OS if already set.
 * Parameters :
 * 	A pointer to tm structure. (time.h)The API call populates this structure
 * Return Values:
 * 	0 on success.
 * 	-1 on failure.
 */ 	

int lk_setrtc(struct tm *) ;
/*
 * Description:
 *       This API function sets the time to the RTC chip as well as for OS.
 * Parameters:
 * 	A pointer to tm structure. The API call populates this structure.
 * Return Values:
 * 	0 on success.
 * 	-1 on failure.
 */

int lk_dispbutton(unsigned char *button1, unsigned char *button2, unsigned char *button3, unsigned char *button4) ;
/*
 * Description:
 * 	This API Function Display the Four Buttons at 5th line of LCD. 
 * Parameters:
 * 	 Button1, Button2, Button3, Button4:
 *		Description: Buffers to display 4 characters of each button
 *		Type: Input
 *		Range: 4 characers only including space character
 * Return Values: 
 * 	0 on Success
 * 	-1 on error
 */ 	

int lk_disphlight(unsigned char line_no) ;
/* 
 * Description:
 *     This API function is used to highlight a given row of text on LCD.
 * Parameters:
 *     line_no: 
 *     		Description: line number to display the text on the LCD. 
 *     		Type: Input
 *     		Range: 0 - 5
 * Return Values:
 *	0 on success.
 *     -1 on failure.
 *     -2 on argument errors.
*/

int lk_dispfont (unsigned char *user_font,unsigned char font_width) ;

/* 
 * Description: 
 * 		This API Function which type of Font to be Displayed on LCD.
 * Parameters: 
 * 	user_font: 
 * 		Description: which font table to be displayed of 6x8 character size.
 * 		Type: Input
 * 		Range: 255 characters font table
 *	font_width: 
 *		Description: width of the given Font.
 *		Type: Input
 *		Range: 6
 * Return Values: 
 * 	0 on Success
 * 	-1 on Error		
 * Note: This function should call immediately after lk_open() 
 */

int lk_bkl_timeout(int bkltime) ;
/*
 * Description:
 *     This API function sets statically LCD backlight timeout. The default timeout is 4 sec. If you want the change the 
 *	backlight timeout permanently you have to call this function once in your application.
 * Parameters:
 *    	bkltime:
 *    		Description: back light timeout in seconds and the range is 4 sec to 30 sec.
 *		Type: Input
 *		Range: 4 - 30
 * Return Values:
 *       0 on success.
 *      -1 on failure.
 *      -2 on argument errors.
 */

int lk_lcdintensity(unsigned char value) ;
/*
 * Description:
 *	This API shows LCD Intensity.
 * Parameters: 
 *	 Value: 
 *	 	Description: (0-63) Default value is 24.
 *	 	Type: Input
 *	 	Range: 0 - 63
 * Return values: 
 *  	0 on Success 
 *	-1 on Failure
 *      -2 on argument errors.
*/

int lk_gsmsignal(unsigned long value) ;
/*
 * Description: 
 *  	This function is to display signal strength of GSM modem which is connected to ttymxc0. 
 *  	By giving 'at+csq' command to modem, we can get the GSM signal strength. 
 *  	By giving the GSM signal strength value to this function we can update the signal strength bars on top of the LCD.
 * Parameters:
 * 	gsm_signal:
 * 		Description: GSM modem signal strength value. 
 * 		Type: Input
 * 		Range: 0 - 31 (if wit at+csq receive 99 then pass 0 to show no signal on LCD)
 *      	Greater than 31 or less than 1 - No bars
 *      	Greater than 25 - 4bars
 *		Greater than 15 - 3bars
 *		Greater than 10 - 2bars
 *		Greater than 1 - 1bar
 * Return Values:
 *    	0 on success.
 *      -1 on failure.
 */

int lk_dispbklight(int val) ;
/*
 * Not Yet Implemented
 */ 

unsigned char lk_getkey_wait(void) ;
/*
 * Description: 
 * 	This function returns key pressed at that particular instant, if there is no key event returns 0xff. This 
 * 	function is similar to lk_getkey, only difference is it returns 0xff if there is no key pressed and it won’t 
 * 	waits for a key.
 * Parameters : 
 * 	None
 * Return Values:
 * 	Corresponding key value or 0xff.
 */ 	

int lk_buzzer (int count);
/*
 * Description:
 * 		This API Function gives buzzer Beep count time.
 * Parameters:
 *  	    count: 
 *  	    	Description: Time count to get buzzer
 *		Type: Input
 *		Range: 0 - 10 
 * Return Values:
 *  	0 on success.
 *      -1 on failure.
 * Limits are like below 
 * 	if count <=0  it will give one beep.
 *     	if count > 10 it gives maximum of 10 Beeps 	
 */

int lk_underline(unsigned char line_no, unsigned char col, unsigned char length, unsigned char font_width);
/*
 * Description:
 * 		This API Function underlines the text On LCD. 
 * Parameters: 
 *	line_no: 
 * 	     	Description: line number to display the text on the LCD.
 * 	     	Type: Input
 * 	     	Range: 0 - 4
 * 	col:  
 * 		Description: Column number to starting underline.
 * 		Type: Input
 * 		Range: 0 -20
 *	length: 
 *		Description: Number of characters to underline.
 *		Type: Input
 *		Range: max 21 characters (depends on col)
 *	font_width:  
 *		Description: Font width is 6.
 *		Type: Input
 *		Range: 6
 * Return Values: 
 * 	0 on success
 * 	-1 on Error
 * 	-2 on arguments error
 */

int lk_getpinpadid (char *machineid);
/*
 * Description: 
 * 	This API function is used to get the PIN PAD ID.
 * 		(Pre Requirements: This id should be set at u-boot prompt before call this API like below 
 * 		VISIONTEK # setenv machineid 1234567890
 * 		VISIONTEK # saveenv)	 
 * Parameters:
 * 	machineid: 
 * 		Description: Read machine ID of 10 digits from u-boot environment variables.
 * 		Type: Output
 * 		Range: 10 digits (bytes) 
 * Return Values: 
 * 	0 on SUCCESS
 *	-1 on Failure
 */

 int lk_gethwid (char *hwid);
/*
 * Description: 
 * 	This API function is used to get the Hardware ID.
 * 		(Pre Requirements: This id should be set at u-boot prompt before call this API like below 
 * 		VISIONTEK # setenv hwid 87654321
 * 		VISIONTEK # saveenv)	 
 * Parameters: 
 * 	hwid:  
 * 		Description: Read Hardware ID of 8 digits from u-boot environment variables.
 * 		Type: Output
 * 		Range: 8 digits (bytes)
 * Return Values: 
 * 	0 on Success 
 * 	-1 on Failure
 */
#endif
