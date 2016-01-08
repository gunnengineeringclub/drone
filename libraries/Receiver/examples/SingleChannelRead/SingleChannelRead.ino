#include <Receiver.h>

/* This example reads a single channel and outputs 
 * it to the serial console
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
  Serial.begin(9600);
  initializeReceiverDecoder();
}

void loop() {
  unsigned int value = getStickValue(0); //0 = Arduino pin 2
  Serial.println(value);
}
