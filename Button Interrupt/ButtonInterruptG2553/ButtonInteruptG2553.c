/**
 * Button Interrupt G2553
 * Created by Bradley Anderson
 * Last Updated on 10/8/2017
 */

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
