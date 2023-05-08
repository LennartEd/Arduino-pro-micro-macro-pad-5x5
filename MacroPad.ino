/* @file MultiKey.ino
|| @version 1.0
|| @author Mark Stanley
|| @contact mstanley@technologist.com
||
|| @description
|| | The latest version, 3.0, of the keypad library supports up to 10
|| | active keys all being pressed at the same time. This sketch is an
|| | example of how you can get multiple key presses from a keypad or
|| | keyboard.
|| #
*/
#include "Keyboard.h"
#include <Keypad.h>
#include <Mouse.h>

#include <Encoder.h>
Encoder RotaryEncoderA(14, 15);  //the LEFT encoder (encoder A)
Encoder RotaryEncoderB(10, 16);  //the RIGHT encoder (encoder B)
long positionEncoderA = -999;    //encoderA LEFT position variable
long positionEncoderB = -999;    //encoderB RIGHT position variable

const byte ROWS = 5;  //rows
const byte COLS = 5;  //columns
char keys[ROWS][COLS] = {
  //encoB
  { '1', '2', '3', '4', '5' },  //  the keyboard hardware is  a 5x5 grid...
  { '6', '7', '8', '9', '0' },
  { 'A', 'B', 'C', 'D', 'E' },  // these values need  to be single char, so...
  { 'F', 'G', 'H', 'I', 'J' },
  { 'K', 'L', 'M', 'N', 'O' },
                      //encoA
};
byte rowPins[ROWS] = { 2, 3, 4, 5, 6 };    //connect to the row pinouts of the keypad
byte colPins[COLS] = { 7, 8, 9, A3, A2 };  //connect to the column pinouts of the keypad
Keypad kpd = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);


const int encoButton = A1;  //encoder Button
const int ModeButton = A0;  //mode Button

unsigned long loopCount;
unsigned long startTime;
String msg;
int modePushCounter = 0;  // counter for the number of button presses
int buttonState = 0;      // current state of the button
int lastButtonState = 0;  // previous state of the button
int mouseMove;


void setup() {
  Serial.begin(9600);
  Keyboard.begin();
  pinMode(ModeButton, INPUT_PULLUP);  // initialize the button pin as a input
  pinMode(encoButton, INPUT_PULLUP);  // initialize the encoder pin as a input
  loopCount = 0;
  startTime = millis();
  msg = "";
}


void loop() {

  loopCount++;
  if ((millis() - startTime) > 5000) {
    Serial.print("Average loops per second = ");
    Serial.println(loopCount / 5);
    startTime = millis();
    loopCount = 0;
  }

  
  checkModeButton();
  checkRotButton();

  // Fills kpd.key[ ] array with up-to 10 active keys.
  // Returns true if there are ANY active keys.

  switch (modePushCounter) {  //checks which layer/mode you are in
    //mode0-----Desktop
    int sensetivity;
    case 0:
      sensetivity = 100; //how much the encoder moves per one click
      mouseMove = map(sensetivity, 0, 1023, 1, 124);  //remap the analog pot values fron 1 to 124
      encoderA_Mode0();
      encoderB_Mode0();
      if (kpd.getKeys()) {
        for (int i = 0; i < LIST_MAX; i++)  // Scan the whole key list.
        {
          if (kpd.key[i].stateChanged)  // Only find keys that have changed state.
          {
            switch (kpd.key[i].kstate) {  // Report active key state : IDLE, PRESSED, HOLD, or RELEASED
              case PRESSED:
                switch (kpd.key[i].kchar) {
                  case '1': Keyboard.press(177); break;//ESC
                  case '2': Keyboard.press('2'); break;
                  case '3': Keyboard.press('3'); break;
                  case '4': Keyboard.press(128);Keyboard.press('q'); break;//quit
                  case '5': Keyboard.press(128); Keyboard.press(130); Keyboard.press(212); break; //ctr+alt+del
                  case '6': Keyboard.press('6'); break;
                  case '7': Keyboard.press('7'); break;
                  case '8': Keyboard.press('8'); break;
                  case '9': Keyboard.press('9'); break;
                  case '0': Keyboard.press('0'); break;
                  case 'A': Keyboard.press('a'); break;
                  case 'B': Keyboard.press('b'); break;
                  case 'C': Keyboard.press('c'); break;
                  case 'D': Keyboard.press('d'); break;
                  case 'E': Keyboard.press('e'); break;
                  case 'F': Keyboard.press(212); break;//DELETE
                  case 'G': Keyboard.press(128);Keyboard.press('w'); break;//close tab
                  case 'H': Keyboard.press(128);Keyboard.press('t'); break;//open new tab
                  case 'I': Keyboard.press(218); break;//arrow up
                  case 'J': Keyboard.press(128);Keyboard.press(129);Keyboard.press('t'); break;//open recently closed tab
                  case 'K': Keyboard.press(128);Keyboard.press('c'); break;//copy
                  case 'L': Keyboard.press(128);Keyboard.press('v'); break;//paste
                  case 'M': Keyboard.press(130);Keyboard.press(216); break;//alt left arrow(back browser)
                  case 'N': Keyboard.press(217); break;//arrow down
                  case 'O': Keyboard.press(130);Keyboard.press(215); break;//alt right arrow(forwards browser)
                }
                msg = " PRESSED.";
              break;
              case HOLD:
                msg = " HOLD.";
              break;
              case RELEASED:
                switch (kpd.key[i].kchar) {
                  case '1': Keyboard.release(177); break;//ESC
                  case '2': Keyboard.release('2'); break;
                  case '3': Keyboard.release('3'); break;
                  case '4': Keyboard.release(128);Keyboard.release('q'); break;
                  case '5': Keyboard.release(128); Keyboard.release(130); Keyboard.release(212); delay(500); Keyboard.write(218); delay(500); Keyboard.write(176); delay(500); Keyboard.write(176); delay(2000); break; //ctr+alt+del+arrowup2x+enter (sleep)
                  case '6': Keyboard.release('6'); break;
                  case '7': Keyboard.release('7'); break;
                  case '8': Keyboard.release('8'); break;
                  case '9': Keyboard.release('9'); break;
                  case '0': Keyboard.release('0'); break;
                  case 'A': Keyboard.release('a'); break;
                  case 'B': Keyboard.release('b'); break;
                  case 'C': Keyboard.release('c'); break;
                  case 'D': Keyboard.release('d'); break;
                  case 'E': Keyboard.release('e'); break;
                  case 'F': Keyboard.release(212); break;//DELETE
                  case 'G': Keyboard.release(128);Keyboard.release('w'); break;//close tab
                  case 'H': Keyboard.release(128);Keyboard.release('t'); break;//open new tab
                  case 'I': Keyboard.release(218); break;//arrow up
                  case 'J': Keyboard.release(128);Keyboard.release(129);Keyboard.release('t'); break;//open recently closed tab
                  case 'K': Keyboard.release(128);Keyboard.release('c'); break;//copy
                  case 'L': Keyboard.release(128);Keyboard.release('v'); break;//paste
                  case 'M': Keyboard.release(130);Keyboard.release(216); break;//alt left arrow(back browser)
                  case 'N': Keyboard.release(217); break;//arrow down
                  case 'O': Keyboard.release(130);Keyboard.release(215); break;//alt right arrow(forwards browser)
                }
                msg = " RELEASED.";
              break;
              case IDLE:
                msg = " IDLE.";
              break;
            }  //switch keystate
            Serial.print("Key ");
            Serial.print(kpd.key[i].kchar);
            Serial.println(msg);
          }  //switch state changed
        }    //forloop
      }      //getkeys
    break;

//mode1-----Gaming
    case 1:
      sensetivity = 100;
      mouseMove = map(sensetivity, 0, 1023, 1, 124);  //remap the analog pot values fron 1 to 124
      encoderA_Mode0();
      encoderB_Mode0();
      if (kpd.getKeys()) {
        for (int i = 0; i < LIST_MAX; i++)  // Scan the whole key list.
        {
          if (kpd.key[i].stateChanged)  // Only find keys that have changed state.
          {
            switch (kpd.key[i].kstate) {  // Report active key state : IDLE, PRESSED, HOLD, or RELEASED
              case PRESSED:
                switch (kpd.key[i].kchar) {
                  case '1': Keyboard.press(177); break;//esc
                  case '2': Keyboard.press('1'); break;
                  case '3': Keyboard.press('2'); break;
                  case '4': Keyboard.press('3'); break;
                  case '5': Keyboard.press('e'); delay(1000); Keyboard.release('e'); delay(100); Mouse.move(-127, 127); delay(100); Mouse.move(-127, 0); Mouse.move(0, 0); delay(100); delay(100); Mouse.click(MOUSE_LEFT); Keyboard.write(177); break; //makro
                  case '6': Keyboard.press(179); break;//tab
                  case '7': Keyboard.press('q'); break;//q
                  case '8': Keyboard.press('w'); break;//w
                  case '9': Keyboard.press('e'); break;//e
                  case '0': Keyboard.press('r'); break;//r
                  case 'A': Keyboard.press('2'); break;//2
                  case 'B': Keyboard.press('a'); break;//a
                  case 'C': Keyboard.press('s'); break;//s
                  case 'D': Keyboard.press('d'); break;//d
                  case 'E': Keyboard.press('f'); break;
                  case 'F': Keyboard.press(129); break;//shift
                  case 'G': Keyboard.press('g'); break;
                  case 'H': Keyboard.press('h'); break;
                  case 'I': Keyboard.press('m'); break;
                  case 'J': Keyboard.press('v'); break;//v
                  case 'K': Keyboard.press(128); break;//ctr
                  case 'L': Keyboard.press('l'); break;
                  case 'M': Keyboard.press('m'); break;
                  case 'N': Keyboard.press('c'); break;//c
                  case 'O': Keyboard.press(32); break;//space
                }
                msg = " PRESSED.";
              break;
              case HOLD:
                msg = " HOLD.";
              break;
              case RELEASED:
                switch (kpd.key[i].kchar) {
                  case '1': Keyboard.release(177); break;//esc
                  case '2': Keyboard.release('1'); break;
                  case '3': Keyboard.release('2'); break;
                  case '4': Keyboard.release('3'); break;
                  case '5': break; //makro
                  case '6': Keyboard.release(179); break;//tab
                  case '7': Keyboard.release('q'); break;//q
                  case '8': Keyboard.release('w'); break;//w
                  case '9': Keyboard.release('e'); break;//e
                  case '0': Keyboard.release('r'); break;//z
                  case 'A': Keyboard.release('2'); break;//2
                  case 'B': Keyboard.release('a'); break;//a
                  case 'C': Keyboard.release('s'); break;//s
                  case 'D': Keyboard.release('d'); break;//d
                  case 'E': Keyboard.release('f'); break;
                  case 'F': Keyboard.release(129); break;//shift
                  case 'G': Keyboard.release('g'); break;
                  case 'H': Keyboard.release('h'); break;
                  case 'I': Keyboard.release('m'); break;
                  case 'J': Keyboard.release('v'); break;//v
                  case 'K': Keyboard.release(128); break;//ctr
                  case 'L': Keyboard.release('l'); break;
                  case 'M': Keyboard.release('m'); break;
                  case 'N': Keyboard.release('c'); break;//c
                  case 'O': Keyboard.release(32); break;//space
                }
                msg = " RELEASED.";
              break;
              case IDLE:
                msg = " IDLE.";
              break;
            }  //switch keystate
            Serial.print("Key ");
            Serial.print(kpd.key[i].kchar);
            Serial.println(msg);
          }  //switch state changed
        }    //forloop
      }      //getkeys
    break;
//mode2-----photoshop/blender
    case 2:
      sensetivity = 200;
      mouseMove = map(sensetivity, 0, 1023, 1, 124);  //remap the analog pot values fron 1 to 124
      encoderA_Mode1();
      encoderB_Mode1();
      if (kpd.getKeys()) {
        for (int i = 0; i < LIST_MAX; i++)  // Scan the whole key list.
        {
          if (kpd.key[i].stateChanged)  // Only find keys that have changed state.
          {
            switch (kpd.key[i].kstate) {  // Report active key state : IDLE, PRESSED, HOLD, or RELEASED
              case PRESSED:
                switch (kpd.key[i].kchar) {
                  case '1': Keyboard.write('blender'); break;
                  case '2': Keyboard.write('2'); break;
                  case '3': Keyboard.press('3'); break;
                  case '4': Keyboard.press('4'); break;
                  case '5': Keyboard.press('5'); break;
                  case '6': Keyboard.press('6'); break;
                  case '7': Keyboard.press('7'); break;
                  case '8': Keyboard.press('8'); break;
                  case '9': Keyboard.press('9'); break;
                  case '0': Keyboard.press('0'); break;
                  case 'A': Keyboard.press('a'); break;
                  case 'B': Keyboard.press('b'); break;
                  case 'C': Keyboard.press('c'); break;
                  case 'D': Keyboard.press('d'); break;
                  case 'E': Keyboard.press('e'); break;
                  case 'F': Keyboard.press('f'); break;
                  case 'G': Keyboard.press('g'); break;
                  case 'H': Keyboard.press('h'); break;
                  case 'I': Keyboard.press('i'); break;
                  case 'J': Keyboard.press('j'); break;
                  case 'K': Keyboard.press('k'); break;
                  case 'L': Keyboard.press('l'); break;
                  case 'M': Keyboard.press('m'); break;
                  case 'N': Keyboard.press('n'); break;
                  case 'O': Keyboard.press('o'); break;//
                }
                msg = " PRESSED.";
              break;
              case HOLD:
                msg = " HOLD.";
              break;
              case RELEASED:
                switch (kpd.key[i].kchar) {
                  case '1': Keyboard.release('2'); break;
                  case '2': Keyboard.release('2'); break;
                  case '3': Keyboard.release('3'); break;
                  case '4': Keyboard.release('4'); break;
                  case '5': Keyboard.release('5'); break;
                  case '6': Keyboard.release('6'); break;
                  case '7': Keyboard.release('7'); break;
                  case '8': Keyboard.release('8'); break;
                  case '9': Keyboard.release('9'); break;
                  case '0': Keyboard.release('0'); break;
                  case 'A': Keyboard.release('a'); break;
                  case 'B': Keyboard.release('b'); break;
                  case 'C': Keyboard.release('c'); break;
                  case 'D': Keyboard.release('d'); break;
                  case 'E': Keyboard.release('e'); break;
                  case 'F': Keyboard.release('f'); break;
                  case 'G': Keyboard.release('g'); break;
                  case 'H': Keyboard.release('h'); break;
                  case 'I': Keyboard.release('i'); break;
                  case 'J': Keyboard.release('j'); break;
                  case 'K': Keyboard.release('k'); break;
                  case 'L': Keyboard.release('l'); break;
                  case 'M': Keyboard.release('m'); break;
                  case 'N': Keyboard.release('n'); break;
                  case 'O': Keyboard.release('o'); break;//
                }
                msg = " RELEASED.";
              break;
              case IDLE:
                msg = " IDLE.";
              break;
            }  //switch keystate
            Serial.print("Key ");
            Serial.print(kpd.key[i].kchar);
            Serial.println(msg);
          }  //switch state changed
        }    //forloop
      }      //getkeys
    break;
  }  //mode switch
}  // End loop

void checkModeButton() {
  buttonState = digitalRead(ModeButton);
  if (buttonState != lastButtonState) {  // compare the buttonState to its previous state
    if (buttonState == LOW) {            // if the state has changed, increment the counter
      // if the current state is LOW then the button cycled:
      modePushCounter++;
      //Serial.println("pressed");
      //Serial.print("number of button pushes: ");
      Serial.println(modePushCounter);
    }
    delay(200);  // Delay a little bit to avoid bouncing
  }
  lastButtonState = buttonState;  // save the current state as the last state, for next time through the loop
  if (modePushCounter > 2) {      //reset the counter after 4 presses CHANGE THIS FOR MORE MODES
    modePushCounter = 0;
  }
}
void checkRotButton() {
  buttonState = digitalRead(encoButton);
  if (buttonState != lastButtonState) {  // compare the buttonState to its previous state
    if (buttonState == LOW) {            // if the state has changed, increment the counter
      switch (modePushCounter) {
      case 0: Keyboard.write('z'); break;
      case 1: break;
      case 2: Keyboard.press(128); Keyboard.write('0'); delay(100); Keyboard.release(128); break; //ctr+0 (fit on screen)
      }
    }
    delay(200);  // Delay a little bit to avoid bouncing
  }
  lastButtonState = buttonState;  // save the current state as the last state, for next time through the loop
}



//ENCODERMODES------------------------------------------------------------------------------------------------
//mode0-----
void encoderA_Mode0() { //move mouse left right
  long newPos = RotaryEncoderA.read() / 2;
  if (newPos != positionEncoderA && newPos > positionEncoderA) {
    positionEncoderA = newPos;
    //Serial.println(mouseMove);
    Mouse.move(-mouseMove, 0, 0);  //moves mouse right... Mouse.move(x, y, wheel) range is -128 to +127
  }
  if (newPos != positionEncoderA && newPos < positionEncoderA) {
    positionEncoderA = newPos;
    Mouse.move(mouseMove, 0, 0);  //moves mouse left... Mouse.move(x, y, wheel) range is -128 to +127
  }
}
void encoderB_Mode0() { //Move mouse up down
  long newPos = RotaryEncoderB.read() / 2;  //When the encoder lands on a valley, this is an increment of 2.
  if (newPos != positionEncoderB && newPos < positionEncoderB) {
    positionEncoderB = newPos;
    Mouse.move(0, -mouseMove, 0);
  }
  if (newPos != positionEncoderB && newPos > positionEncoderB) {
    positionEncoderB = newPos;
    Mouse.move(0, mouseMove, 0);
  }
}

//MODE1-------
void encoderA_Mode1() { //scroll wheel
  long newPos = RotaryEncoderA.read() / 2;
  if (newPos != positionEncoderA && newPos > positionEncoderA) {
    positionEncoderA = newPos;
    //Serial.println(mouseMove);
    Mouse.move(0, 0, 1);
  }
  if (newPos != positionEncoderA && newPos < positionEncoderA) {
    positionEncoderA = newPos;
    Mouse.move(0, 0, -1);
  }
}
void encoderB_Mode1() { //ctr+right-click+drag (photoshop brush size)
  long newPos = RotaryEncoderB.read() / 2;  
  if (newPos != positionEncoderB && newPos < positionEncoderB) {
    positionEncoderB = newPos;
    Keyboard.press(130);  //ctr
    Mouse.press(MOUSE_RIGHT); //right mouse
    Mouse.move(2, 0); //amount of pixel change
    delay(50);  //delay
    Keyboard.release(130);
    Mouse.release(MOUSE_RIGHT);
  }
  if (newPos != positionEncoderB && newPos > positionEncoderB) {
    positionEncoderB = newPos;
    Keyboard.press(130);
    Mouse.press(MOUSE_RIGHT);
    Mouse.move(-2, 0);
    delay(50);
    Keyboard.release(130);
    Mouse.release(MOUSE_RIGHT);
  }
}
