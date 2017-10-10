/**
 * Bradley Anderson
 * Two Button Interrupt F5529 Extra Work Lab3
 * Date Created 10/8/2017
 */


#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer



            P1DIR = (BIT0|~BIT1);       //sets bit 0 of P1 as the output and bit 1 of P1 as input
            P4DIR = BIT7;       //sets bit 7 of P4 as the output LED 2

            P2DIR = ~BIT1;       //sets bit 1 of P2 as an input, the button

            P1REN = BIT1;       //Enables Pullup Resister on pin 1.1, button 2
            P1OUT = BIT1;       //Clears bit 1 of P1
            P1IE |= BIT1;       //enables interrupt for button2
            P1IFG &= ~BIT1;     //ands interrupt flag with 0 to clear it

            P2REN = BIT1;       //Enables Pullup resistor on pin 2.1
            P2OUT = BIT1;       //Clears bit 1 of P2
            P2IE |= BIT1;       //enables interrupt for button
            P2IFG &= ~BIT1;     //ands the interrupt flag with 0 to clear it

                   __bis_SR_register(GIE);  // enables all maskable interupts across board.  G-Global I-Interupt E- Enable

                   for (;;){}   //Initializes a continuous loop
}
        #pragma vector=PORT2_VECTOR         //Interrupt  Service Routine
        __interrupt void Port_2(void){      // Changed to Port_2

            volatile int i;
                 if(P2IN & BIT1)    //If the Button (P2.1) is Pressed, allows the LED to toggle
                        P1OUT ^= 0x01; //Toggles bit 0 on P1 by XORing bit 0 with itself

                        i = 8000;         //
                        do i--;           // Initiates a delay between toggling bit 0
                        while (i != 0);   //

            }

        #pragma vector=PORT1_VECTOR         //Interrupt  Service Routine
        __interrupt void Port_1(void){      // Changed to Port_2

            volatile int i;
                 if(~P1IN & BIT1)    //If the Button (P1.1) is Pressed, allows the LED to toggle
                        P4OUT ^= BIT7; //Toggles bit 7 on P4 by XORing bit 0 with itself

                        i = 16000;         //
                        do i--;           // Initiates a delay between toggling bit 0
                        while (i != 0);   //

            }

