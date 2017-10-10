/**
 * Button Based Delay FR5994
 * Created by TI
 * Edited by Bradley Anderson
 * Last Edited 10/8/2017
 */



#include <msp430.h> 

#define LED_0       BIT0
#define LED_OUT     P1OUT  //Defines specific outputs to make it easier to switch  between boards
#define LED_DIR     P1DIR
#define BUTTON_IN   P5DIR
#define BUTTON      BIT6

unsigned int count = 0;
unsigned int eButton = 0x00;
unsigned int q = 0;
unsigned int touchButton;

void startTimer (int freq);

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5; //needed FR devices

    LED_DIR |= (LED_0); // Set P1.0 to output direction
    LED_OUT &= ~(LED_0); // Set the LED off

    BUTTON_IN &= ~BUTTON; //P5.6 becomes an input

    P5REN |= BUTTON; //Enables a pullup/down resistor
    P5OUT |= BUTTON; //Makes the resistor pullup

    P5IES |= BUTTON; //Triggers interrupt when button is pressed
    P5IE |= BUTTON; //Enables the interupt for the button
    P5IFG &= ~BUTTON; //Clears interuptflag

    startTimer(10); //Starts the timer at 10Hz originally

__enable_interrupt(); // Interrupts get enabled

__bis_SR_register(LPM0 + GIE); // General Interrupts in LowPowerMode 0

}

void startTimer(int freq) //function to set a particular frequency
{
    int t;

    TA0CCTL0 = CCIE; //Enable interupt for Capture Compare
    TA0CTL = TASSEL_2 + MC_1 + ID_3;  //Choose SMCLK (1000000Hz) divided by 8 = 125000, in Upcount Mode

    t = (125000 / freq); // Divides the clock by the desired frequency to give t --> 125000 / 10 = 12500
    TA0CCR0 = t;         // Set capture comp reg 0 to 12500. --> 125000/12500 gives desired 10Hz
}

//Timer A ISR
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A0(void)
{
    if (eButton != 0x00) {
     if (P5IN & BUTTON) {  // Triggers interrupt when Button pressed
        touchButton = 0;
        eButton = 0;
        count = 0;
    }
     else { //increments arbitrary variable q
         LED_OUT |= LED_0;     // Toggles LED 1
         q++;                  // q increments while button is being pressed
         }

    }

    else  { // increments count until the count is equal to variable q
        if (count == q) { //Toggles the LED
        LED_OUT ^= LED_0;
        count = 0; //Resets count after LED Toggle
        }

        else
            count++; //increments count
        }
    }

// Port 1 interrupt service routine
#pragma vector=PORT5_VECTOR
__interrupt void Port_5(void)
{
    eButton = 1; //  Button is Enabled
    q = 0;       // resets the counter compare variable
    touchButton = 1; //Button is being touched
    P5IFG &= ~BUTTON; // Clears the interrupt flag by and operation

}
