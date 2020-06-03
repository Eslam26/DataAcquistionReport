#include <LiquidCrystal.h>
#define K_CONSTANT 2
#define B_MAGNET 0.9
#define DISTANCE 1.524  // 60 inch
LiquidCrystal Screen(12, 11, 5, 4, 3, 2);
float voltageReading = 0;
float velocity = 0;


void setup() {
  // set up the LCD's number of columns and rows:
  Screen.begin(16, 2);
  // Print a message to the LCD.
  Screen.setCursor(3,0);
  Screen.print("Flowmeter");
  Screen.setCursor(4,1);
  Screen.print("Welcome");
  delay(1000);
  Screen.clear();
  Screen.print("Reading: ");
}


void loop() {
  voltageReading = analogRead(A0)*1.0*0.5/1023;
  velocity = (voltageReading*1000*1.0)/(K_CONSTANT*B_MAGNET*DISTANCE);
  Screen.setCursor(0,1);
  Screen.print(velocity);
  Screen.print(" ");
  Screen.print("L/sec");
}
