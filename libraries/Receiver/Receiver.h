/*
 *
 *  Created on: 15 Dec 2013
 *  Author: Axel Ljungdahl
 *  Contact: mail@axel.pw
 *  Version 0.1
 */

#ifndef RECEIVER_DECODER_H_
#define RECEIVER_DECODER_H_
#include <inttypes.h> //Fix for Arduino

/*
 * Configuration start
 */

//This does nothing except break the code right now if you change it.
#define CHANNELS 6

//This is the minimum accepted pulse, for my 9x I read about ~980, nothing is perfect and I accept this as my 1000
#define MINIMUM_PULSEVAL 980
//Same with the maximum accepted pulse, mine reads ~1980, which gives us a range of 1000 µs anyway, still adding some for safety
#define MAXIMUM_PULSEVAL 2000

/*
 * Configuration end
 */

/*
 * Constants start
 * Do not touch this unless you are absolutely sure about what you are doing.
 */

#define NUMBER_OF_CHANNELS (CHANNELS + 2) //Used for loops, +2 because we aren't using PB0 and PB1 due to HW serial

/*
 * Constants end
 */

uint16_t getStickValue(uint8_t channel);
void initializeReceiverDecoder();


#endif /* RECEIVER_DECODER_H_ */

