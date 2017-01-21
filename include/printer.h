#ifndef PRINTER_H
#define PRINTER_H

/*
 *Company Name: Linkwell Telesystems Pvt. Ltd (visiontek.co.in)
 *@Author A.Prabhakar.(R&D Asst. Engineer).
 *Description:GL14  Printer Device  APIs.  
 * 
 * */

/** @brief 
 * This API Function is used to open the printer device . 
 * Note: This function must be called before any printer function.
 * @return
 *      1 on Success. 
 *      2 if the device is already opend
 *     -1 on failure.
 */
int prn_open();  



/** @brief 
 *This API Function is used to close the printer device . 
 *@return
 *       1 if the device closed successfully
 *      -1 if the device is not close.
 **/
int prn_close(); 


/** @brief 
 *        This API Function is used to prints the text  .
 *@param text2: 
 *Description: pointer to the buffer from which the text to be printed.
 *         type: INPUT
 *   
 *@param len: 
 *Description:  length of the text.
 *Type: INPUT
 *@param font: 
 *Description: font of the the text presently there are two fonts are supported (1= Reguler and 2= Bold  ).
 *      Type: INPUT
 * @return    
 *            0 on Success.
 *           -1 if the device not opened .
 *           -2 if the length is more .
 *           -3  NO Paper .
 *           -4 Low Battery.      
 *           -5 Max temp .        
 *           -6 No Lines.        
 *           -7 WRITE_ERROR.     
 *
 **/
int prn_write_text(unsigned char *text2, int len, int font);

/** @brief 
 * This API Function is used to advance the paper .
 *   @param scanlines: 
 * Description: scanlines is to be passed as parameter (1 text line is equal to 17 scan lines).
 *           type: INPUT
 *       @return    
 *                 -1 if the device not opened,else the response from the ioctl function.
 **/
int prn_paper_feed(int scanlines);


/** @brief 
 *       This API Function is used to print bmp data  .
 * @param bmp: 
 *      Description: pointer to the buffer from which the data to be printed.the image is 144x144 pixels
 *             type: INPUT
 * @param len: 
 *         Description:  length of the text.
 *                type: INPUT
 * @return    
 *               0  no. of characters written on success
 *              -1 if error occurs.
 *		-2 if the length is more .
 *		-3  NO Paper .
 *		-4 Low Battery.      
 *		-5 Max temp .        
 *	        -6 No Lines.        
 *	        -7 WRITE_ERROR.     
 *
 **/
int prn_write_bmp(unsigned char *bitmap, long len);



/** @brief 
 * 	This API Function is used printer papar status .
 *  @return   
 * 		   0 on Success.
 * 		   -1 on Error.
 *
 **/
	
int prn_paperstatus(void);
#endif
