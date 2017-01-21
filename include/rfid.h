#ifndef __RFID_H__
#define __RFID_H__
/*
 *Company Name: Linkwell Telesystems Pvt. Ltd (visiontek.co.in)
 *@Author A.Prabhakar.(R&D Asst. Engineer).
 *Description:Gl14  RFID Device  APIs.  
 **/



/** @brief 
 * This API Function is used to open RFID device. 
 * Note: This function must be called before any rfid function.
 * @return
 *      opened file descriptor on success 
 *      < 1 on failure
 */
int tama_open(void);

/** @brief 
 * This API Function is used to close rfid device. 
 * Note: This function must be called before any rfid function.
 */
void tama_close(void);


/** @brief 
 *      This API Function is used to detect the targets of RFID Card reader
 * @param Tg_Nos: 
 *              Description: Number of targets to detect(Max. 2).
 *              type: INPUT
 *              Range: Max. 2 
 * @param Tg_Detected: 
 *              Description:Address of memory to store number of Tags detected
 *              type: INPUT 
 * @param Tg_ID: 
 *              Description:Address of memory to store Tag ID
 *              type: INPUT
 * @return      
 *     Number of Tags read/initialized is stored in the address passed to Tg_Detected.The read Tag is stored in 
 *     	location pointed by Tag ID pointer.
 *          0 on success.
 *         -1 on failure
 */
int tama_detectTarget(unsigned char Tg_Nos, unsigned char *Tg_Detected, unsigned char *Tg_ID);




/** @brief 
 *      This API Function authenticates a Tag's Block for writing/reading with the said key
 * @param Tg_No: 
 *              Description: Tag Number to authenticate(0 - Card 1, 1 - Card 2).
 *              Type: INPUT
 * @param Blk_Addr: 
 *              Description: Block address
 *              Type: INPUT 
 * @param index: 
 *              Description:key index
 *              Type: INPUT
 * @param Key_Type: 
 *              Description:Key type (Key A - 0x0A /Key B - 0x0B)
 *              Type: INPUT
 * @return      .
 *          0 on success.
 *          < 1 on failure.
 */
int tama_authenticate_mifare(unsigned char Tg_No, unsigned char Blk_Addr, unsigned char *Key, unsigned char Key_Type);




/** @brief 
 *      This API Function halts (Deselects) a tag for access
 * @param Tg_LID: 
 *              Description:  Tag's logical ID.
 *              type: INPUT
 * @return      
 *          0 on success.
 *          < 1 on Failure.
 */
int tama_halt_mifare(unsigned char Tg_LID);




/** @brief 
 *      This API Function reads the block data and stores it into passed address
 * @param Blk_Addr: 
 *              Description: Block address to read.
 *              type: INPUT
 * @param Data_In: 
 *              Description:pointer to the data in buffer.
 *              type: INPUT
 * @return      
 *          0 on success.
 *          < 1 on failure.
 */
int tama_read_target(unsigned char Blk_Addr, unsigned char *Data_In);



/** @brief 
 *      This API Function writes the data sent to the said block
 * @param Blk_Addr: 
 *              Description: Block address to write.
 *              type: INPUT
 * @param Data_Out: 
 *              Description:pointer to the data .
 *              type: INPUT
 * @param Dlen: 
 *              Description:length of data to write .
 *              type: INPUT
 * @return      
 *          0 on success.
 *          < 1 on failure.
 */
int tama_write_target(unsigned char Blk_Addr, unsigned char *Data_Out, int Dlen);
#endif
