#include "bcm_puzzle.h"
	
/*************************************************************************** 
// Function Name: getCrc32 
// Description  : caculate the CRC 32 of the given data. 
// Parameters   : pdata - array of data. 
//                size - number of input data bytes. 
//                crc - either CRC32_INIT_VALUE or previous return value. 
// Returns      : crc. 
****************************************************************************/
UINT32 getCrc32(byte *pdata, UINT32 size, UINT32 crc)
{
    while (size-- > 0) {
	crc = (crc >> 8) ^ Crc32_table[(crc ^ *pdata++) & 0xff];
    }
    return crc;
}
