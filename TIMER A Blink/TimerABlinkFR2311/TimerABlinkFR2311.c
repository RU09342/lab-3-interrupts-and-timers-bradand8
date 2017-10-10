/**
 * Timer A Blink FR2311
 * Created by Texas Instruments
 * Edited by Bradley Anderson
 * Last Edited 10/8/2017
 */


#include <msp430.h> 

#define LED_0      BIT0      //Sets the pin for first LED1
#define LED_1      BIT0      //Sets the pin for the second LED2
#define LED1_OUT    P1OUT
#define LED2_OUT    P2OUT
#define LED1_DIR    P1DIR
#define LED2_DIR    P2DIR


void main(void){

    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;     // Needed to reprogram pins after low power mode for FR5x devices

    LED1_DIR |= (LED_0);      //Sets pins as output directions as defined above
    LED2_DIR |= (LED_1);

    LED1_OUT &= ~(LED_0);    //Sets the LEDs off by anding the bits with 0
    LED2_OUT &= ~(LED_1);

    TB0CCTL2 = CCIE;                 //enables Capture Compare Register CCR2 interrupt
    TB0CCTL1 = CCIE;
    TB0CTL = TBSSEL_2 + MC_2 + ID_3; // Set the timer B to SMCLCK, Continuos Mode, sets clock division to 8.
    TB0CCR2 = 15625;                  // 8Hz   --- 1000000/8/8 = 15625
    TB0CCR1 = 62500;                  // 2Hz   --- 1000000/8/2 = 62500


    __bis_SR_register(LPM0_bits + GIE); // LPM0 with general interrupts enabled

}


    // Timer A interrupt service routine
    #pragma vector = TIMER0_B1_VECTOR
    __interrupt void Timer_B( void )
    {
        switch( TB0IV ){
        case 2: // TB0CCR1
    {
        LED2_OUT ^= LED_1;        //Toggles LED1
        TB0CCR1 += 62500;
    }
      break;
      case 4: // TB0CCR2
    {
        LED1_OUT ^= LED_0;         //Toggles LED2
        TB0CCR2 += 15625;
    }
      break;

    case 10: // Overflow - TB0IFG
    {}
      break;
    }
  }
