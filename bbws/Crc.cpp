#include "Crc.h"

unsigned int CRCCalculation(unsigned char* buf, unsigned char number_byte)
{
	unsigned int crc;
	unsigned char bit_counter;


	//if( number_byte>1 );
	crc = 0xFFFF;
	while (number_byte > 0)
	{
		if (buf == nullptr) {
			break;
		}
		crc ^= *buf++;
		bit_counter = 0;
		while (bit_counter < 8)
		{
			if (crc & 0x0001)
			{
				crc >>= 1;
				crc ^= 0xA001;
			}
			else
				crc >>= 1;

			bit_counter++;
		}

		number_byte--;
	}
	return crc;
}
