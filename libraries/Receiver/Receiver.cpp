/*
 *
 *  Created on: 15 Dec 2013
 *  Author: Axel Ljungdahl
 *  Contact: mail@axel.pw
 *  Version 0.1
 *
 *  Timer help from http://eleccelerator.com/avr-timer-calculator/
 *  Very nice site!
 *
 *	One TCNT1 tick equals 0,5 µs, divide by two (bitshift 1 step right)
 *	Equals microseconds. Overflows at 2^15 µs (32768 µs, 2^16 ticks).
 *	Overflows every 32.77 milliseconds.
 *	1 second is 30 overflows + ca 34k ticks.
 *
 *	These overflows can cause problems if you require super high update rate on the values,
 *	however you lose a bit of speed if you add something to keep track of overflows.
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "Receiver.h"

volatile uint8_t previousState = 0b00000000;
volatile uint16_t firstPulseValue[6];
volatile uint16_t currentStickValue[6];

void initializeReceiverDecoder() {
	// TIMER START
	TCCR1A = 0; // Normal mode, no compare outputs
	TCCR1B = (TCCR1B & 0xFC) | (1 << CS11); // Set 8 prescaler
	// TIMER END

	// PINCHANGE INTERRUPT START
	PCICR |= (1 << PCIE2); //Enable pin change interrupt 2
	//Here we enable 18-23, change later for custom number of pins
	PCMSK2 |= 0xFC;
	// PINCHANGE INTERRUPT END

	//Enable global interrupts
	sei();
}

uint16_t getStickValue(uint8_t channel) {
	if(channel >= 0 && channel <= 5) {
		return currentStickValue[channel];
	}
	return 1200; //If you give it an incorrect channel value, it returns 1200 to not accidently arm something
}

/*
 * First we check which pin that has changed of the 6 pins on PORTD we are watching.
 * Secondly, if the pin is HIGH, the change is the FIRST of the pulse.
 * If the pin is LOW, it is the END of the pulse.
 * (END - FIRST) should give us a value from 1000 to 2000, which is our value.
 *
 * If the change detected is the first pulse, we simply store the timer value in firstPulseValue
 *
 * If the detected is the second pulse, we subtract the timestamp stored in firstPulse Value,
 * and as a result we should have our value.
 *
 * Due to overflow, some readings are lost because they do not fit into the limits, this
 * should not be a problem.
 */

ISR(PCINT2_vect) {
	//First we check which pins that has changed.
	uint8_t changedPins = ((PIND ^ previousState) & 0xFC);
	for (uint8_t i = 2; i < NUMBER_OF_CHANNELS; i++) {
		if ((1 << i) & changedPins) { //Loop trough all pins, see what pin has changed.
			//If the pin is HIGH, we write the value to firstPulseValue, because it is the first change of the pulse
			if ((PIND & _BV(i))) {
				firstPulseValue[i-2] = TCNT1 >> 1; //Stores the timer1 value/2 in the variable.
			} else { //If it isn't HIGH, it has got to be LOW! Checking it anyway.
				uint16_t timerVal = (TCNT1 >> 1) - firstPulseValue[i-2];
				if(timerVal <= MAXIMUM_PULSEVAL && timerVal >= MINIMUM_PULSEVAL) {
					//If the value we calculated is witin limits we write it to the currentValue
					currentStickValue[i-2] = timerVal;
				}
			}
		}
	}
	previousState = PIND; //Set current state as previousState as we exit the interrupt.
}
