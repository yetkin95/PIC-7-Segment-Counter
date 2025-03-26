/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.65.2
        Device            :  PIC18F26K22
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/
#include <xc.h>
#include "mcc_generated_files/mcc.h"
#include "charsetdef.h"
int sn_sayac=0;
/*
                         Main application
 */
char driver[5]={0X10,0X01,0X02,0X04,0X08};
char buff[5]={0X10,0X01,0X02,0X04,0X08};

char dispdata[5]={CH_0,CH_1,CH_2,CH_3,0b00000001};
void bcd(int sayi)
{


int a,n,t;
int i;

    a=0;
	while(sayi>=1)
	{
	     n=sayi%10;
		 sayi=sayi/10;
		 dispdata[a]=n;
		 a++;
         
        for(i=0;i<a;i++)
        {
            switch(dispdata[i])
            {
                case 0: 
                    dispdata[i]=CH_0; break;
                
                case 1: 
                    dispdata[i]=CH_1; break;
                case 2: 
                    dispdata[i]=CH_2; break;
                
                case 3:
                    dispdata[i]=CH_3; break;
                case 4: 
                    dispdata[i]=CH_4; break;
                
                case 5: 
                    dispdata[i]=CH_5; break;  
                case 6: 
                    dispdata[i]=CH_6; break;
                
                case 7: 
                    dispdata[i]=CH_7; break;
                case 8:
                    dispdata[i]=CH_8 ; break;
                case 9: 
                    dispdata[i]=CH_9; break;
                default: 
                    dispdata[i]=CH_0; break;
            }
            
        }
 	}
	
	
}

void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();
    TMR0_WriteTimer(0xfc17);
    TMR0_StartTimer();
    INTERRUPT_GlobalInterruptEnable();

    while (1)
    {   
        
        bcd(sn_sayac);
        
        __delay_ms(200);
    }
}
/**
 End of File
*/