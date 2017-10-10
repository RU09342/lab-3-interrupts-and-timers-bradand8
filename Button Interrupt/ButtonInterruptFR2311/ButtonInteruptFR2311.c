/**
 * Bradley Anderson
 * Button Interupt FR2311
 * Date Created 10/7/2017
 */


#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;

            P1DIR = BIT0;       //sets bit 0  as an output
            P1REN = BIT1;       //Enables Pullup resistor on pin 1.1
            P1OUT = BIT1;       //Clears bit 1 of P1
            P1IE |= BIT1;       //enables interupt for button
            P1IFG &= ~BIT1;     //ands the interupt flag with 0 to clear it

           __bis_SR_register(GIE);  // enables all maskable interupts across board.  G-Global I-Interupt E- Enable

            for (;;){}   //Initializes a continuous loop
}

    #pragma vector=PORT1_VECTOR
            __interrupt void Port_1(void){

                volatile int i;         //integer value from internal counter

                 if(~P1IN & BIT1)    //If the Button (P1.1) is Pressed, allows the LED to toggle
                        P1OUT ^= 0x01; //Toggles bit 0 on P1 by XORing bit 0 with itself

                        i = 10000;        //
                        do i--;           // Initiates a delay between toggling bit 0
                        while (i != 0);   //


}
