 /*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.2
 *
 * @version Package Version: 3.1.2
*/

/*
© [2026] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/
#include "mcc_generated_files/system/system.h"
#include "Sent_Receive.h"

/*
    Main application
*/

volatile bool dataReady = false;

void CLB_IRQ0_Handler(void)
{   
    dataReady = true;
}

int main(void)
{
    bool transferInProgress = false;
    uint8_t rxData;
    uint8_t nibbleNo = 0;
    uint8_t receivedBuffer[8];
    uint8_t printData;
    uint8_t bit3;
    uint8_t bit2;

    SYSTEM_Initialize();
    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts 
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global Interrupts 
    // Use the following macros to: 

    // Enable the Global Interrupts 
    INTERRUPT_GlobalInterruptEnable(); 

    // Disable the Global Interrupts 
    //INTERRUPT_GlobalInterruptDisable(); 


    CLB1_CLB0I_SetInterruptHandler(CLB_IRQ0_Handler);
    
    while(1)
    {
        if(dataReady == true)
        {
            rxData = CLBSWOUTL;
            receivedBuffer[nibbleNo++] = rxData & 0x0F;

            INTERRUPT_GlobalInterruptDisable();
            dataReady = false;
            INTERRUPT_GlobalInterruptEnable();
        }
        
        if(nibbleNo >= 8)
        {
            nibbleNo = 0;
            transferInProgress = false;

            printf("0x");
            for(uint8_t i = 0; i < 4; i++)
            {
                printData = (uint8_t)(receivedBuffer[2*i+1] + (receivedBuffer[2*i]<<4));
                printf("%02X", printData);
                if(i == 0)
                {
                    bit3 = ((receivedBuffer[0] & 0x08) ? 1 : 0);
                    bit2 = ((receivedBuffer[0] & 0x04) ? 1 : 0);
                }
                if(i == 3)
                    SMF_Processing(bit2, bit3);     
            }
            printf("\n\r");
        }
    }   
}