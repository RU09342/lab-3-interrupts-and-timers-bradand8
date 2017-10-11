# TIMER A Blink
This lab introduces the use of the built in timers of the MSP430 devices. Using timer interrupts are useful to determine a specific rate at which an LED will blink. 

## Clock sources
The timer is composed of a 16-bit timer counter. The TAXR register either increments or decrements with the rising edge of the clock signal. By Setting TASSEL bits, the clock sources can be selected. The source can also be further divided by TAIDEX bits. Using TACTL allows the user to choose a clock, count mode and further clock division as desired. 
* TASSEL 0    -- TAXCLK
* TASSEL 1    -- ACLK, 32K Hz frequency 
* TASSEL 2    -- SMCLK 1M Hz frequency
* TASSEL 3    -- INCLK

##  Timer Modes 
There are different modes for a timer that indicate how the timer will count and can be selected via Timer Mode Control (MC).
* MC_0      -- stops the timer
* MC_1      -- Up count Mode, timer counts from 0 to a specific value set by TAXCCR0
* MC_2      -- Continuous count Mode, timer counts from zero to 0FFFFh.
* MC_3      -- Up/Down Mode, timer counts from zero to a value of TAXCCR0 and then backwards to zero from there.

 
## Base code MSP430G2553
The following code toggles two LEDs at a speed set by the timers. Pre dividers can be included by adding an ID_X to the TA0CTL. Enabling two capture compare registers and a corresponding interrupt vector allows for a specific frequency to be set at which each LED toggles.
Timer_A interrupt enable TAIE, and TAIFG Timer_A interrupt flag  are used to enable the interrupts and keep track of when they occur.

The interrupt service routine utilizes a switch statement based on the TA0IV (interrupt vector for capture compare flags) toggles the specific LED when the capture compare register value is reached. TA0IV returns an even value corresponding to the highest priority pending interrupt. 

The code for the MSP430G2553 is given below:

```
#define LED_0      BIT0      //Sets the pin for first LED1
#define LED_1      BIT7      //Sets the pin for the second LED2
#define LED1_OUT    P1OUT
#define LED2_OUT    P4OUT
#define LED1_DIR    P1DIR
#define LED2_DIR    P4DIR


void main(void){

    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer


    LED1_DIR |= (LED_0);      //Sets pins as output directions as defined above
    LED2_DIR |= (LED_1);

    LED1_OUT &= ~(LED_0);    //Sets the LEDs off by anding the bits with 0
    LED2_OUT &= ~(LED_1);

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
        LED2_OUT ^= LED_1;        //Toggles LED1
        TA0CCR1 += 62500;
    }
      break;
      case 4: // TA0CCR2
    {
        LED1_OUT ^= LED_0;         //Toggles LED2
        TA0CCR2 += 15625;
    }
      break;

    case 10: // Overflow - TA0IFG
    {}
      break;
    }
  }
```
## Difference between micro Processors

* MSP430G2553
* MSP430FR2311    *Note no Timer A*
* MSP430FR6989
* MSP430F5529
* MSP430FR5994

To make the transitioning between microprocessors easier, the top of the program defines parameters for the bit that must be toggled for LED 1 and 2, aswell as the port output and direction. Based on the particular microprocessor, all that needs to be changed are these bits. The one exception is the FR2311 which has no A timer, but instead a B timer that requires the Registers and the interrupt service routine vectors to be changed from A to B.

## Advantage to using a Timer to blink an LED
Aside from the easibility to set a frequency for blinking the LEDs, each timer can use multiple capture compare registers to access seperate LEDs with the same timer.


