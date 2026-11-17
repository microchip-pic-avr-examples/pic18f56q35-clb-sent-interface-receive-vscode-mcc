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

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef SENT_RECEIVE_H
#define	SENT_RECEIVE_H

#ifdef	__cplusplus
extern "C" {
#endif
    

#define SLOW_MESSAGE_MODE 1 // 0 - Short Serial Message Format; 1 - Enhanced Serial Message Format; -1 - No Serial Message


typedef struct
{
    uint8_t ID;
    uint8_t Data;
    uint8_t CRC;
} SENT_SSMF_Frame_t;

typedef struct
{
    bool Config;
    uint8_t ID;
    uint16_t Data;
    uint8_t CRC;
} SENT_ESMF_Frame_t;

static uint8_t SENT_CalculateCRC(uint8_t *buffer);
static uint8_t SENT_GetBit16(uint16_t value, uint8_t bit);
static uint8_t SENT_GetBit8(uint8_t value, uint8_t bit);
static uint8_t SENT_CalculateCRC_ESMF(uint32_t message_bits);
static uint32_t SENT_BuildESMFMessage(bool config, uint8_t id, uint16_t data);
static uint16_t Parse_MSB(const uint8_t *buffer, uint8_t start, uint8_t count);
bool Detect_Pattern(uint8_t bit3);
void SSMF_Processing(uint8_t bit2, uint8_t bit3);
void ESMF_Processing(uint8_t bit2, uint8_t bit3);
void SMF_Processing(uint8_t bit2, uint8_t bit3);

#ifdef	__cplusplus
}
#endif

#endif	/* SENT_RECEIVE_H */

