#include <Receiver.h>

/* This example reads a single channel and lights 
 * the built-in LED on pin13 if the received value is
 * bigger than 1900 (about 90% stick)
 * 
 * Please do note, that at present time, the library always 
 * reads 6 channels, and pin 2 to 7 will therefor
 * be unable to use even when only using a single channel.
 * +-------------+------------------------+
 * | Arduino pin | getStickValue argument |
 * +-------------+------------------------+
 * |           2 |                      0 |
 * |           3 |                      1 |
 * |           4 |                      2 |
 * |           5 |                      3 |
 * |           6 |                      4 |
 * |           7 |                      5 |
 * +-------------+------------------------+
 *
 */

void setup() {
  initializeReceiverDecoder();
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  
}

void loop() {
  unsigned int value = getStickValue(0); //0 = Arduino pin 2
  if(value > 1900) {
    digitalWrite(13, HIGH);
  } else {
    digitalWrite(13, LOW);
  }
}
