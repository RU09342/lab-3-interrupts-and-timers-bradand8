/**
 * Timer A Blink G2553
 * Created by Texas Instruments
 * Edited by Bradley Anderson
 * Last Editted 10/8/2017
 */


#include <msp430.h> 

#define LED_0      BIT0      //Sets the pin for first LED1
#define LED_1      BIT6      //Sets the pin for the second LED2
#define LED_OUT    P1OUT
#define LED_DIR    P1DIR


void main(void){

    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer


    LED_DIR |= (LED_0 + LED_1);      //Sets pins as output directions as defined above
    LED_OUT &= ~(LED_0 + LED_1);     //Sets the LEDs off by anding the bits with 0

    TA0CCTL2 = CCIE;                 //enables Capture Compare Register CCR2 interrupt
    TA0CCTL1 = CCIE;
    TA0CTL = TASSEL_2 + MC_2 + ID_3; // Set the timer A to SMCLCK, Continuos Mode, sets clock division to 8.
    TA0CCR2 = 15625;                  // 8Hz   --- 1000000/8/8 = 15625
    TA0CCR1 = 62500;                  // 2Hz   --- 1000000/8/2 = 62500


    __bis_SR_register(LPM0_bits + GIE); // LPM0 with general interrupts enabled

}


    // Timer A interrupt service routine
    #pragma vector = TIMER0_A1_VECTOR
    __interrupt void Timer_A( void )
    {
        switch( TA0IV ){
        case 2: // TA0CCR1
    {
        LED_OUT ^= LED_1;        //Toggles LED1
        TA0CCR1 += 62500;
    }
      break;
      case 4: // TA0CCR2
    {
        P1OUT ^= LED_0;         //Toggles LED2
        TA0CCR2 += 15625;
    }
      break;

    case 10: // Overflow - TA0IFG
    {}
      break;
    }
  }
