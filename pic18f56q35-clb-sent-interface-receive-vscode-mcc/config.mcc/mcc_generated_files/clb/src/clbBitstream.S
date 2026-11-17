/**
 *  @file clbBitstream.s
 *
 *  @brief CLB bitstream data for the PIC18FxyQ35 device family
 *
 **/
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

/*
    The bitstream data can be accesed from C source code by referencing the 'start_clb_config' symbol as such:

    extern uint16_t start_clb_config;
    uint16_t clbStartAddress = (uint16_t) &start_clb_config;

    IMPORTANT: You must always use the address of these symbols and not the value of the symbols themselves.
               If values instead of addresses are used, the linker will silently generate incorrect code.

    uint16_t clbStartAddress = start_clb_config; // This is incorrect!

    NOTE: This module requires C preprocessing.
          This can be enabled via the command line option: -xassembler-with-cpp
*/


#include <xc.inc>


#if !(defined (_18F26Q35) || defined (_18F46Q35) || defined (_18F56Q35) \
    || defined (_18F25Q35) || defined (_18F45Q35) || defined (_18F55Q35) \
    || defined (_18F24Q35) || defined (_18F44Q35) || defined (_18F54Q35))
	
    #error This module is only suitable for PIC18F56Q35 family devices
#endif

GLOBAL  _start_clb_config
GLOBAL  _end_clb_config

PSECT  clb_config,global,class=CONST,delta=1,noexec,keep,reloc=100h

_start_clb_config:
    DW  0x01FE
    DW  0x00E2
    DW  0x00FE
    DW  0x007E
    DW  0x0040
    DW  0x0040
    DW  0x0040
    DW  0x0040
    DW  0x0040
    DW  0x0040
    DW  0x0040
    DW  0x0040
    DW  0x0040
    DW  0x0040
    DW  0x0040
    DW  0x0040
    DW  0x0040
    DW  0x0040
    DW  0x0040
    DW  0x0040
    DW  0x0040
    DW  0x0040
    DW  0x0040
    DW  0x0040
    DW  0x0040
    DW  0x0040
    DW  0x0040
    DW  0x0040
    DW  0x0040
    DW  0x0040
    DW  0x0040
    DW  0x0040
    DW  0x0008
    DW  0x0000
    DW  0x0000
    DW  0x0043
    DW  0x2000
    DW  0x006C
    DW  0xE4E4
    DW  0xAAAA
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0xAAAA
    DW  0x7134
    DW  0x1325
    DW  0x0521
    DW  0x0001
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0001
    DW  0x0089
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x7000
    DW  0x0300
    DW  0x0000
    DW  0x0000
    DW  0x4444
    DW  0x8000
    DW  0xE4E4
    DW  0xCCCC
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0xAAAA
    DW  0x0054
    DW  0x5569
    DW  0x0524
    DW  0x0060
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0004
    DW  0x008A
    DW  0x0000
    DW  0x0000
    DW  0x0050
    DW  0x0000
    DW  0x0300
    DW  0x0000
    DW  0x0002
    DW  0x060A
    DW  0xF0CC
    DW  0xF0F0
    DW  0xCCCC
    DW  0xF0F0
    DW  0xCCCC
    DW  0xF0F0
    DW  0xF0F0
    DW  0xA152
    DW  0x1420
    DW  0x0500
    DW  0x0030
    DW  0x0400
    DW  0x0030
    DW  0x0500
    DW  0x0100
    DW  0x00FC
    DW  0x0000
    DW  0x0000
    DW  0x00E0
    DW  0x0001
    DW  0x0200
    DW  0x0000
    DW  0x0000
    DW  0x1222
    DW  0xAFA0
    DW  0xAAAA
    DW  0xFF00
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0xAAAA
    DW  0xA352
    DW  0x2105
    DW  0x0004
    DW  0x5000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0004
    DW  0x008C
    DW  0x0000
    DW  0x0000
    DW  0x0030
    DW  0x0000
    DW  0x0200
    DW  0x0000
    DW  0x0000
    DW  0xC000
    DW  0xAA00
    DW  0xFF00
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0xA550
    DW  0xA004
    DW  0x5000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0007
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x3000
    DW  0x0000
    DW  0x0002
    DW  0x0001
    DW  0x5050
    DW  0x1450
    DW  0xAAAA
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0108
    DW  0x3261
    DW  0x0001
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0005
    DW  0x0000
    DW  0x0000
    DW  0x00B0
    DW  0x0000
    DW  0x0000
    DW  0x0001
    DW  0x0000
    DW  0xC0E0
    DW  0x0550
    DW  0xFF00
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0xAAAA
    DW  0x4521
    DW  0xA204
    DW  0x3000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0004
    DW  0x0084
    DW  0x0008
    DW  0x0000
    DW  0x0050
    DW  0x0000
    DW  0x0000
    DW  0x0001
    DW  0x0000
    DW  0xC8C0
    DW  0x0505
    DW  0x0000
    DW  0xF0F0
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0xAAAA
    DW  0xA231
    DW  0x0104
    DW  0x0000
    DW  0x0100
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0003
    DW  0x008A
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x20A8
    DW  0xAAAA
    DW  0x0000
    DW  0x0000
    DW  0xCCCC
    DW  0x0000
    DW  0x0000
    DW  0xFF00
    DW  0x9254
    DW  0x0003
    DW  0x0000
    DW  0x0000
    DW  0x0050
    DW  0x0000
    DW  0x0000
    DW  0x3000
    DW  0x0092
    DW  0x0038
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0005
    DW  0x0000
    DW  0x0000
    DW  0xA820
    DW  0xB800
    DW  0xCCCC
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x3254
    DW  0x3265
    DW  0x0050
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0004
    DW  0x0000
    DW  0x0000
    DW  0x00F0
    DW  0x0D00
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0xC0A0
    DW  0xA820
    DW  0xAAAA
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0xA532
    DW  0x32A4
    DW  0x0003
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0004
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0xB080
    DW  0xAAAA
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x2463
    DW  0x0004
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0002
    DW  0x0000
    DW  0x0000
    DW  0x00D0
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0001
    DW  0x0000
    DW  0x0000
    DW  0xAAAA
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0001
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0002
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
_end_clb_config:
 