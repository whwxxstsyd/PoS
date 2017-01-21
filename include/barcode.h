#ifndef USB__BAR__CODE__
#define USB__BAR__CODE__

/*
 *Company Name: Linkwell Telesystems Pvt. Ltd (visiontek.co.in)
* @Author A.Prabhakar.(R&D Asst. Engineer).
* Description: GL14 Barcode  APIs.  
*
*/

/** @brief 
 * This API Function is used to open barcode device. 
 * Note: This function must be called before any barcode function.
 * @return
 *           0 on Success.
 *          -1 on failure. 
 **/

int bar_code_open(void);


/** @brief 
 *  This API Function reads the barcode.
 *@param rxbuf: 
 *  Description: buffer used to store barcode data.
 *          type: output 
 *         Range: 0 - 256 
 *@param len: 
 *   Description:len means size of data to be read (For future expansion. Now, it will return on enter)
 *                     Returns data size read.
 *          type: input
 *         Range: 0 - 256 
 *@return      
 *          >0 on Success.
 *          -1 on Error.
 */
int bar_code_read (char *rxbuf,int len);


/** @brief 
 * This API Function closes the barcode.
 * @return      
 *      0 on Success.
 *      -1 on Error.
 */
int bar_code_close (void);
#endif

