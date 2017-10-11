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

## Task
Your goal for this part of the lab is to replicate your button code from Lab 2, where the LED should change states only when the button is pressed. This can be extended to include behaviors such as only have the LED on when the button is depressed, or have the LED blink one color when pressed and another when it is let go. Another behavior extends from the second lab which is speed control based on the button presses. For example, have the rate of the LED cycle between a "low", "Medium", and "High" rate of speed.

## Extra Work 
### Binary Counter/Shift Register
Either use a function generator, another processor, or a button to control your microcontroller as an 8-bit binary counter using 8 LEDs to indicate the current status of the counter.

## Extra Work Multiple Buttons
Come up with a behavior of your own that incorporates needing to use two buttons or more and these two buttons must be implemented using interrupts.

