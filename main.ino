#include <Servo.h>
#include <Receiver.h>

#define MAX_SIGNAL 2000
#define MIN_SIGNAL 700

Servo m1;
Servo m2;
Servo m3;
Servo m4;
//Servo m9;

int attached = 0;
int m1speed = 1000;
int m2speed = 1000;
int m3speed = 1000;
int m4speed = 1000;

int throttle = 0;
int side = 0;
int forward = 0;
int throttleside = 0;


void setup() {
  initializeReceiverDecoder();
  Serial.begin(9600);
  Serial.println("Program begin...");
  Serial.println("This program will calibrate the ESC.");

  m1.attach(9);
  m2.attach(10);
  m3.attach(11);
  m4.attach(12);

  Serial.println("Now writing maximum output.");
  Serial.println("Turn on power source, then wait 2 seconds and press any key.");
  m1.writeMicroseconds(MAX_SIGNAL);
  m2.writeMicroseconds(MAX_SIGNAL);
  m3.writeMicroseconds(MAX_SIGNAL);
  m4.writeMicroseconds(MAX_SIGNAL);

  // Wait for input
  while (!Serial.available());
  Serial.read();

  // Send min output
  Serial.println("Sending minimum output");
  m1.writeMicroseconds(MIN_SIGNAL);
  m2.writeMicroseconds(MIN_SIGNAL);
  m3.writeMicroseconds(MIN_SIGNAL);
  m4.writeMicroseconds(MIN_SIGNAL);



  while (!Serial.available());
  Serial.println("Got a new thing");
  attached = 1;

}

void loop() {  
  if(attached == 1)
  {
    m1.writeMicroseconds(m1speed);
    m2.writeMicroseconds(m2speed);
    m3.writeMicroseconds(m3speed);
    m4.writeMicroseconds(m4speed);
    
 
//    if(Serial.available()) 
//      value = Serial.parseInt();    // Parse an Integer from Serial

    side = getStickValue(0);
    forward = getStickValue(1);
//    throttle = getStickValue(2);
    throttleside = getStickValue(3);

//    throttle = 1300;

    if(Serial.available()) 
      throttle = Serial.parseInt(); 
  

    float sp = ((throttle - 1150) / 1000.0)*1400 + 700;
    if(sp < 700)
    {
      sp = 700;
    }
    Serial.print(throttle);
    Serial.print(" : ");
    Serial.print(sp);
    Serial.println();
    m1speed = sp;
    m2speed = sp;
    m3speed = sp;
    m4speed = sp;

    
  }
}
