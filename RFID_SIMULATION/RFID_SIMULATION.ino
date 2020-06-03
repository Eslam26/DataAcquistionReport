/*--------------------INCLUDES---------------------*/
#include <LiquidCrystal.h>

/*--------------------DEFINES----------------------*/
#define ID_CHARACTER_LENGTH 12

/*----Create an object from LiquidCrystal Class----*/
LiquidCrystal Screen(13, 12, 5, 4, 3, 2);


/*---array of length 12 bytes to store enteredID---*/
char RFID_data[12];

/*-----2D-Array to story only three correct IDs----*/
//  30009ABC93AB
//  300092EA2CB4
//  3000935B3F9C
char  Saved_Tags[3][12] = {
  {'3', '0', '0', '0', '9', 'A', 'B', 'C', '9', '3', 'A', 'B'},

  {'3', '0', '0', '0', '9', '2', 'E', 'A', '2', 'C', 'B', '4'},

  {'3', '0', '0', '0', '9', '3', '5', 'B', '3', 'F', '9', 'C'}
};
boolean tag_check, tag_status, entry_control;
void setup()
{
  Screen.begin(16, 2);
  Serial.begin(9600);
  Screen.clear();
  Screen.setCursor(0, 0);
  Screen.print("RFID CARD READER");
  Screen.setCursor(4, 1);
  Screen.print("Welcome");
  delay(1000);
  Screen.clear();
}
void loop()
{
  Getting_ID();
  Checking_ID();
  AccessFunction();
}
void Getting_ID()
{
  char counter = 0;
  char data = 0;
  while (counter != ID_CHARACTER_LENGTH)
  {
    counter = 0; // set counter variable to zero
    Screen.clear();
    Screen.setCursor(0, 0); // set cursor to (0,0)
    Screen.print("ENTER THE CARD"); // display "ENTER THE CARD" statement
    delay(500); // delay 500 milliseconds
    while (Serial.available()) // while serial connection is opened 
    {
      data = Serial.read(); // get first byte of data sent
      RFID_data[counter] = data; // store in the array
      counter++; // increment counter by one 
    }
  }
  counter = 0; // set counter to zero 
  Screen.clear();
  Screen.print("Checking..."); // display "Checking..." statement 
  delay(1000); // wait 1000 milliseconds 
}
void Checking_ID() {
  char i, j; // declare counter variables
  for (i = 0; i < 3; i++) // looping over 3 correct IDs
  {
    // check each byte in correct ID by the corresponding one in enteredID 
    for (j = 0; j < 12; j++) 
    {
      /* if they are correct go to next byte */
      if (Saved_Tags[i][j] == RFID_data[j])
      {
        tag_check = true;
      }
      /* if not, break the loop and check the next correct ID */
      else
      {
        tag_check = false;
        break;
      }
    }
    /* if the enteredID is correct */
    if (tag_check == true)
    {
      /* set tag_status to be true */
      tag_status = true;
    }

  }
}
void AccessFunction() {

  Screen.clear();
  /* if tag_status variable is true */
  if (tag_status == true)

  {
    /* display 
     * "ACCESS GRANTED" and "VERIFIED" statements 
     */
    Screen.setCursor(1, 0);
    Screen.print("ACCESS GRANTED");
    Screen.setCursor(4, 1);
    Screen.print("VERIFIED");
  }
  /* if tag_status variable is not true */
  else
  {
    /* display 
     * "ACCESS DENIED" and "NOT VERIFIED" statements 
     */
    Screen.setCursor(2, 0);
    Screen.print("ACCESS DENIED");
    Screen.setCursor(2, 1);
    Screen.print("NOT VERIFIED");
  }
  /* set tag_status variable to be false, waiting for next ID verification */
  tag_status = false;
  delay(1000);
}
