/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

#include "mcc_generated_files/system/system.h"
#include "Sent_Receive.h"

/*
 * **************************************************************************
 * 
 * Resource used:
 *   - CLB used as encoder
 *       - CLBSWINL - data 
 *       - CLBSWINH0 - Start Frame 
 *       - CLB_IRQ0 - buffer empty interrupt 
 *       
 *   - Timer0 - tick timer for SENT protocol
 * 
 * **************************************************************************
 
*/

const uint8_t CrcLookup[16] = { 0, 13, 7, 10, 14, 3, 9, 4, 1, 12, 6, 11, 15, 2, 8, 5 };
static const uint8_t crc6_table[64] = {
     0, 25, 50, 43, 61, 36, 15, 22,
    35, 58, 17,  8, 30,  7, 44, 53,
    31,  6, 45, 52, 34, 59, 16,  9,
    60, 37, 14, 23,  1, 24, 51, 42,
    62, 39, 12, 21,  3, 26, 49, 40,
    29,  4, 47, 54, 32, 57, 18, 11,
    33, 56, 19, 10, 28,  5, 46, 55,
     2, 27, 48, 41, 63, 38, 13, 20
};

SENT_SSMF_Frame_t SSMF_Frame;
SENT_ESMF_Frame_t ESMF_Frame;

static uint8_t SENT_CalculateCRC(uint8_t *buffer)
{
  uint8_t calculatedCRC = 5;    // initialize checksum with seed "0101"
  uint8_t data;
  
  for (uint8_t i = 0; i < 3; i++)
  {
      data = buffer[i] & 0x0F;
      calculatedCRC = CrcLookup[calculatedCRC];
      calculatedCRC = (calculatedCRC ^ data) & 0x0F;       // NOTE original data values are used to generate the CRC value.
      data = (buffer[i] >> 4) & 0x0F;
      calculatedCRC = CrcLookup[calculatedCRC];
      calculatedCRC = (calculatedCRC ^ data) & 0x0F;       // NOTE original data values are used to generate the CRC value.
  }     
  // One more round with 0 as input
  calculatedCRC = CrcLookup[calculatedCRC]; 
  return calculatedCRC;
}

static uint8_t SENT_GetBit16(uint16_t value, uint8_t bit)
{
    return (uint8_t)((value >> bit) & 1U);
}

static uint8_t SENT_GetBit8(uint8_t value, uint8_t bit)
{
    return (uint8_t)((value >> bit) & 1U);
}

static uint8_t SENT_CalculateCRC_ESMF(uint32_t message_bits)
{
    uint8_t crc = 0x15U;    // initialize checksum with seed "00010101"

    for (uint8_t group = 0U; group < 4U; ++group)
    {
        uint8_t data_6bit = (uint8_t)((message_bits >> (18U - 6U * group)) & 0x3FU);
        crc = (uint8_t)(crc6_table[crc] ^ data_6bit);
    }
    // One more round with 0 as input
    crc = crc6_table[crc];

    return crc & 0x3FU;
}

static uint32_t SENT_BuildESMFMessage(bool config, uint8_t id, uint16_t data)
{
    uint8_t message_bits[24] = { 0U };
    uint32_t message = 0U;

    message_bits[0]  = SENT_GetBit16(data, 11);     // D11
    message_bits[2]  = SENT_GetBit16(data, 10);     // D10
    message_bits[4]  = SENT_GetBit16(data,  9);     // D9
    message_bits[6]  = SENT_GetBit16(data,  8);     // D8
    message_bits[8]  = SENT_GetBit16(data,  7);     // D7
    message_bits[10] = SENT_GetBit16(data,  6);     // D6
    message_bits[12] = SENT_GetBit16(data,  5);     // D5
    message_bits[14] = SENT_GetBit16(data,  4);     // D4
    message_bits[16] = SENT_GetBit16(data,  3);     // D3
    message_bits[18] = SENT_GetBit16(data,  2);     // D2
    message_bits[20] = SENT_GetBit16(data,  1);     // D1
    message_bits[22] = SENT_GetBit16(data,  0);     // D0


    message_bits[3] = config ? 1 : 0;

    if(!config)
    {
        message_bits[5]  = SENT_GetBit8(id, 7);     // ID7
        message_bits[7]  = SENT_GetBit8(id, 6);     // ID6
        message_bits[9]  = SENT_GetBit8(id, 5);     // ID5
        message_bits[11] = SENT_GetBit8(id, 4);     // ID4
        message_bits[15] = SENT_GetBit8(id, 3);     // ID3
        message_bits[17] = SENT_GetBit8(id, 2);     // ID2
        message_bits[19] = SENT_GetBit8(id, 1);     // ID1
        message_bits[21] = SENT_GetBit8(id, 0);     // ID0
    }
    else
    {
        message_bits[5]  = SENT_GetBit8(id, 3);     // ID3
        message_bits[7]  = SENT_GetBit8(id, 2);     // ID2
        message_bits[9]  = SENT_GetBit8(id, 1);     // ID1
        message_bits[11] = SENT_GetBit8(id, 0);     // ID0
        message_bits[15] = SENT_GetBit16(data, 15); // D15
        message_bits[17] = SENT_GetBit16(data, 14); // D14
        message_bits[19] = SENT_GetBit16(data, 13); // D13
        message_bits[21] = SENT_GetBit16(data, 12); // D12
    }

    for (uint8_t bit = 0U; bit < 24U; ++bit)
        message = (message << 1) | (uint32_t)(message_bits[bit] & 1);
        
    return message & 0xFFFFFFUL;
}

static uint16_t Parse_MSB(const uint8_t *buffer, uint8_t start, uint8_t count)
{
    uint16_t val;
    for(uint8_t i = 0; i < count; i++)
        val = (val << 1) | (buffer[start + i] & 1);
    return val;
}

bool Detect_Pattern(uint8_t bit3)
{
	static uint8_t counter = 0;
	static bool correct_pattern = true;

	if (counter == 12 || counter == 17)
	{
		if (bit3 != 0)
			correct_pattern = false;
	}
	else if (counter < 6)
	{
		if (bit3 != 1)
			correct_pattern = false;
	}
	else if (counter == 6)
	{
		if(bit3 != 0)
			correct_pattern = false;
	}
	counter++;
	
	if(counter == 18 && correct_pattern == true)
	{
        counter = 0;
		correct_pattern = true;
    }
	
	if(correct_pattern == false)
	{
		counter = 0;
		correct_pattern = true;
		return false;
	}
	else
		return true;
}

void SSMF_Processing(uint8_t bit2, uint8_t bit3)
{
    uint8_t buffer[16];
    static uint8_t counter = 0;

    if(bit3 == 1)
        counter = 0;
    else
        counter++;
    buffer[counter] = bit2;
    
    if(counter == 15)
    {
        SSMF_Frame.ID = Parse_MSB(&buffer[0], 0, 4) & 0x0F;
        SSMF_Frame.Data = (uint8_t)((Parse_MSB(&buffer[0], 8, 4) & 0x0F) << 4) | (Parse_MSB(&buffer[0], 4, 4) & 0x0F);
        SSMF_Frame.CRC = Parse_MSB(&buffer[0], 12, 4) & 0x0F;
        uint8_t SSMFMessageCRC[3] = {SSMF_Frame.ID, SSMF_Frame.Data, 0x00};
        if (SENT_CalculateCRC(SSMFMessageCRC) == (uint8_t)SSMF_Frame.CRC)
            printf("\nSSMF Message: ID = %X, Data = %X, CRC is: %X\n\n\n", SSMF_Frame.ID, SSMF_Frame.Data, SSMF_Frame.CRC);
        counter = 0;
    }
}

void ESMF_Processing(uint8_t bit2, uint8_t bit3)
{
	static uint8_t buffer_bit2[18], buffer_bit3[18];
	static uint8_t counter = 0;

	if(Detect_Pattern(bit3))
	{
		printf("\tBit3: %X, Bit2: %X, Counter: %d\n", bit3, bit2, counter);

		buffer_bit2[counter] = bit2;
		buffer_bit3[counter] = bit3;
		counter++;
		
		if(counter == 18)
		{
			ESMF_Frame.Config = buffer_bit3[7];

			if(ESMF_Frame.Config == true)
			{
				ESMF_Frame.ID = Parse_MSB(&buffer_bit3[0], 8, 4) & 0x0F;
				ESMF_Frame.Data = (Parse_MSB(&buffer_bit3[0], 13, 4) & 0x0F) << 12;
				ESMF_Frame.Data |= Parse_MSB(&buffer_bit2[0], 6, 12) & 0xFFFF;
			}
			else
			{
				ESMF_Frame.ID = (uint8_t)((Parse_MSB(&buffer_bit3[0], 8, 4) & 0x0F) <<  4) | (Parse_MSB(&buffer_bit3[0], 13, 4) & 0x0F);
				ESMF_Frame.Data = Parse_MSB(&buffer_bit2[0], 6, 12) & 0x0FFF;
			}

			ESMF_Frame.CRC = Parse_MSB(&buffer_bit2[0], 0, 6) & 0x3F;

			if (SENT_CalculateCRC_ESMF(SENT_BuildESMFMessage(ESMF_Frame.Config, ESMF_Frame.ID, ESMF_Frame.Data)) == ESMF_Frame.CRC)
                printf("\nESMF Message: ID = %X, C = %X, Data = %X, CRC is: %X\n\n\n", ESMF_Frame.ID, ESMF_Frame.Config, ESMF_Frame.Data, ESMF_Frame.CRC);

			counter = 0;
		}
	}
	else
	{
	    counter = 0;
	    printf("\tBit3: %X, Bit2: %X, Counter: %d\n", bit3, bit2, counter);
	    printf("ESMF Message Sync Failed!\n\n\n");
	}
}

void SMF_Processing(uint8_t bit2, uint8_t bit3)
{
    if(SLOW_MESSAGE_MODE == 1)
        ESMF_Processing(bit2, bit3);
    else if(SLOW_MESSAGE_MODE == 0)
        SSMF_Processing(bit2, bit3);  
}