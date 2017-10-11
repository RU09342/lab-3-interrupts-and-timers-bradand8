# Button Based Delay
Previously the delays were already set in the code when the MSP430s were programmed. In this lab, a button is used to set the rate at which the LED toggles based on how long the button was held. 

## Specifications
The initial LED frequency should be at the rate of 10Hz upon first starting up. Then with the use of a button, the frequency should be overwritten basesd on how long the Button was pressed. Using an additional function allows a particular start up frequency to be chosen. T

## The Code Key Concepts
As discussed in specififications, the initial Frequency should be 10Hz. To do this an additional method was written that divides the clock by the desired frequency, stores this frequency in the Timer Capture Comper register, and this allows the desired frequency to be chosen by calling the function with the desired frequency as a parameter. For Example

``` startTimer(10); ```   //Calculates the Frequency to start at 10Hz

The timer interrupt service routine is used to blink the LED and the Port interrupt service routines are used to set the new timer interrupt service value based on how long the button was pressed. Unsigned integer values were created to hold various information needed in the ISRs. 

## Differences Among Micro Processors
1. MSP430G2553    
2. MSP430FR6989
3. MSP430FR5994
4. MSP430FR2311   --The interrupt Vectors and Timer Vectors must be in reference to BClock instead of AClock.
5. MSP430F5529

For the shared differences: the button and LED bits are defined at the top of each code, and their definitions only need to be changed based on the pins for the LED outputs and the BUTTON inputs. The port resistor enables for either a pullup or pulldown resistor need to be changed to the port associated with the button in the main function. The Port IN, and Port interrupt edge select must also be changed in accordance with the port of the button.


