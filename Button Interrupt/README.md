# Button Interrupt
While a button can toggle an LED in multiple ways, the previous labs relied on the PXIN register to see if there was a change in the button input. This concept, known as Polling, can be quite inefficient as it as the processor spends a lot of time trying to see if a change has occured with the button input. A better way to utilize the button is by a button interrupt. This utilizes a few other registers:

* PXIE   - enables the interrupt and the port given, X
* PXIES  - enables the interrupt edge select to switch between a rising edge and a falling edge interrupt
* PXIFG  - Interrupt flag to signify to the processor an interrupt has occured. 

Using 
```  __bis_SR_register(GIE) ``` enables all setable interrupts on the processor.

With the interrupt enabled, the processor can wait until the interrupt occurs, and then act accordingly. The key to the interrupt is the following code segment:

```c
#pragma vector=PORTX_VECTOR
__interrupt void Port_X(void)
{
}
```
The pragma vector tells the compiler to execute a particular code when an interrupt is triggered.

## Base Code
The basic code for a button interrupt on the MSP430G2553 is given below.

```
#include <msp430.h> 

/**
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

            P1DIR = 0x01;       //sets bit 0 of P1 as the output
            P1REN = BIT3;       //Enables Pullup resistor on pin 1.3
            P1OUT = BIT3;       //Makes pullup resistor for button
            P1IE |= BIT3;       //enables interupt for button
            P1IFG &= ~BIT3;     //ands the interupt flag with 0 to clear it

            __bis_SR_register(GIE);  // enables all maskable interupts.  G-Global I-Interupt E- Enable

            for (;;){}   //Initializes a continuous loop
}
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void){

    volatile int i;         //integer value for loop
                        if((~P1IN&BIT3))  //If the Button (P1.3) is Pressed, allows the LED to toggle
                           P1OUT ^= 0x01; //Toggles bit 0 on P1 by XORing bit 0 with itself
                        i = 8000;         //
                        do i--;           // Initiates a delay between toggling bit 0
                        while (i != 0);   //
}
```
The code is intended to only toggle the LED when the button is pressed, as indicated to the processor by the interrupt flag. If we un-negate the ~P1IN bit, the LED will toggle originally and only pause when the button is pressed.

## Differences Among Micro Processors
* MSP430G2553
* MSP430FR2311
* MSP430FR6989 
* MSP430F5529  - The interrupt vectors for the F5529 processor all occur on port 2 instead of port 1
* MSP430FR5994 - The interrupt vectors for the FR5994 occur on port 5 instead of port 1

Aside from that, the only things necessary to change are the bits that correspond with the buttons, just like the button blink code.

## Extra Work Multiple Buttons
The extra work for this Lab involved using two different buttons for two interrupts on the MSP430F5529. Two pragma vector, Port 1 and Port 2, were used for the interrupts and both interrupts toggled at different speeds.

