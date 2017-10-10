/**
 * Bradley Anderson
 * Button Interrupt MSP430FR5994
 * Date Created 10/7/2017
  */


#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;      //Allows the I/O to reset from LPM ish


        P1DIR = 0x01;       //sets bit 0 of P1 as the output

        P5REN = BIT5;       //Enables Pullup resistor on pin 5.5
        P5OUT = BIT5;       //Clears bit 1 of P5 making it a Pullup Resistor
        P5IE |= BIT5;       //enables interrupt for button
        P5IFG &= ~BIT5;     //ands the interrupt flag with 0 to clear it

    __bis_SR_register(GIE);  // enables all maskable interupts across board.  G-Global I-Interupt E- Enable

    for (;;){}   //Initializes an empty loop

}
    #pragma vector=PORT5_VECTOR         //Interrupt  Service Routine
   __interrupt void Port_5(void){      //

       volatile int i;         //integer value from internal counter

         if(~P5IN & BIT5)    //If the Button (P5.5) is Pressed, allows the LED to toggle
                P1OUT ^= BIT0; //Toggles bit 0 on P1 by XORing bit 0 with 1

                i = 20000;         //
                do i--;           // Initiates a delay between toggling bit 0
                while (i != 0);   //
 }
