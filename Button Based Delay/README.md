# Button Based Delay
Previously the delays were already set in the code when the MSP430s were programmed. In this lab, a button is used to set the rate at which the LED toggles based on how long the button was held. 

## Specifications
The initial LED frequency should be at the rate of 10Hz upon first starting up. Then with the use of a button, the frequency should be overwritten basesd on how long the Button was pressed. Using an additional function allows a particular start up frequency to be chosen. T

## The Code Key Concepts
As discussed in specififications, the initial Frequency should be 10Hz. To do this an additional method was written that divides the clock by the desired frequency, stores this frequency in the Timer Capture Comper register, and this allows the desired frequency to be chosen by calling the function with the desired frequency as a parameter. For Example

``` startTimer(10); ```

The timer interrupt service routine is used to blink the Leand the Port interrupt service routines are used to


Setup your microcontroller to initially blink and LED at a rate of 10Hz upon restarting or powering up. Then utilizing one of the buttons on board, a user should be able to set the delay or blinking rate of the LED by holding down a button. The duration in which the button is depressed should then become the new rate at which the LED blinks. As previously stated, you most likely will want to take advantage of the fact that TIMER modules exist and see if you can let them do a bulk of the work for you. 

### Extra Work
## Reset Button
What is a piece of electronics without a reset button? Instead of relying on resetting your processor using the built in reset circuitry, why not instead use another button to reset the rate back to 10Hz.

## Button Based Hertz
Most likely using two buttons, what if instead of making a delay loop based on the time, the user could instead enter a mode where the number of times they pressed the button would become the number in Hz of the blinking rate? How do you think you would implement that with just one button?
