/**
  TMR0 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    tmr0.c

  @Summary
    This is the generated driver implementation file for the TMR0 driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This source file provides APIs for TMR0.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.65.2
        Device            :  PIC18F26K22
        Driver Version    :  2.01
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.45
        MPLAB 	          :  MPLAB X 4.15
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

/**
  Section: Included Files
*/

#include <xc.h>
#include "charsetdef1.h"
#include "tmr0.h"
//#include "../mcc_generated_files/../../../../picworks/sevensegment/sevensegment.X/charsetdef.h"
//#define _XTAL_FREQ 16000000
/**
  Section: Global Variables Definitions
*/ int sn_sayac=0;
char dispdata[5]={CH_0,CH_1,CH_2,CH_3,0b00000001};
char driver[5];
void (*TMR0_InterruptHandler)(void);
int index=0;
volatile uint16_t timer0ReloadVal;

/**
  Section: TMR0 APIs
*/
unsigned int roletimer=0;

void shiftch(int ch)
{
    int i;
    LATC0=0;
    for(i=0;i<8;i++)
    {
       if (ch & 0X80)
       {
           LATC1=1;
       }
           
       else
       {
            LATC1=0;
       }
          
       LATC0=1;
       //Nop();                   //nooperation
       LATC0=0;
       ch<<=1;
    }
}

void TMR0_Initialize(void)
{
    // Set TMR0 to the options selected in the User Interface

    //Enable 16bit timer mode before assigning value to TMR0H
//    T0CONbits.T08BIT = 1;

    // TMR0H 255; 
    TMR0H = 0xf0;

    // TMR0L 230; 
    TMR0L = 0x5f;

	
    // Load TMR0 value to the 16-bit reload variable
    timer0ReloadVal = (uint16_t)((TMR0H << 8) | TMR0L);

    // Clear Interrupt flag before enabling the interrupt
    INTCONbits.TMR0IF = 0;

    // Enabling TMR0 interrupt.
    INTCONbits.TMR0IE = 1;

    // Set Default Interrupt Handler
    TMR0_SetInterruptHandler(TMR0_DefaultInterruptHandler);

    // T0PS 1:4; T08BIT 16-bit; T0SE Increment_hi_lo; T0CS T0CKI; TMR0ON enabled; PSA assigned; 
    T0CON = 0x81;
}

void TMR0_StartTimer(void)
{
    // Start the Timer by writing to TMR0ON bit
    T0CONbits.TMR0ON = 1;
}

void TMR0_StopTimer(void)
{
    // Stop the Timer by writing to TMR0ON bit
    T0CONbits.TMR0ON = 0;
}

uint16_t TMR0_ReadTimer(void)
{
    uint16_t readVal;
    uint8_t readValLow;
    uint8_t readValHigh;

    readValLow  = TMR0L;
    readValHigh = TMR0H;
    readVal  = ((uint16_t)readValHigh << 8) + readValLow;

    return readVal;
}

void TMR0_WriteTimer(uint16_t timerVal)
{
    // Write to the Timer0 register
    TMR0H = timerVal >> 8;
    TMR0L = (uint8_t) timerVal;
}

void TMR0_Reload(void)
{
    // Write to the Timer0 register
    TMR0H = timer0ReloadVal >> 8;
    TMR0L = (uint8_t) timer0ReloadVal;
}

void TMR0_ISR(void)
{

    // clear the TMR0 interrupt flag
    INTCONbits.TMR0IF = 0;

    // reload TMR0
    // Write to the Timer0 register
//    TMR0H = timer0ReloadVal >> 8;
 //   TMR0L = (uint8_t) timer0ReloadVal;
   TMR0_WriteTimer(0xfc17);
  //  if(TMR0_InterruptHandler)
 //   {
  //      TMR0_InterruptHandler();
  //  }
    
    
    // add your TMR0 interrupt custom code  
    
      roletimer++;
    //if(roletimer<1000) LATA4=0;
    //else LATA4=0;
    if(roletimer>=1000) 
    {
            sn_sayac++; 
    }  
    if(sn_sayac>=9999)
    {
            sn_sayac=0;
    }        
    LATA5=0;    //RA5--> OE
   shiftch(dispdata[index]);
    shiftch(driver[index]);
   
    LATA5=1;
    index++;
    if(index>3)
        index=0;
}


void TMR0_SetInterruptHandler(void (* InterruptHandler)(void)){
    TMR0_InterruptHandler = InterruptHandler;
}

void TMR0_DefaultInterruptHandler(void){
    // add your TMR0 interrupt custom code
    // or set custom function using TMR0_SetInterruptHandler()
    

}

/**
  End of File
*/