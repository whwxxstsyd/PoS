#ifndef MAGSWIPE_H
#define  MAGSWIPE_H

//This functon opens the device 
//It returns SUCCESS(1) if the device opened successfully, otherwise reurn MAG_SW_ERR
int mscr_open();

//This function reads the data of the both tracks from the card reader 
//Pointers to the buffers where tracks data to be copied are to be passed as arguments, track1 and track2
//are charecter pointer data types and the memory allocated to them should be length of the expected data+1 
//(suggested 256 bytes each)
// returns 
// 	'1' if only track1 data is valid and copied data into track_1_data buffer
// 	'2' if only track2 data is valid and copied data into track_2_data buffer
// 	'3' if only track2 data is valid and copied data into track_3_data buffer
// 	'4' if track 1 & 2 are valid and copied data into track_1_data buffer & track_2_data buffer
// 	'5' if track 2 & 3 are valid and copied data into track_2_data buffer & track_3_data buffer
// 	'6' if track 1 & 3 are valid and copied data into track_1_data buffer & track_3_data buffer
// 	'7' if track 1, 2 & 3 are valid and copied into all three buffers, 
// 	MAG_SW_ERR (-1) if there is no valid data of all three tracks or device not opened. 
int mscr_read(char *track_1_data, char *track_2_data, char *track_3_data); 

//This function clears the card reader device buffer returns SUCCESS on success, returns MAG_SW_ERR if the device not opened.
int mscr_flush(); 

//This fucntion is used to check wether the device is having valid data ( both track1 and track2 data).
// returns SUCCESS if the valid data present, return MAG_SW_ERR if there is no valid data.
int mscr_getstate(); 

//This function close the device
// returns SUCCESS if the device closed successfully and returns MAG_SW_ERR if the device is not opened.
int mscr_close();

#endif 
