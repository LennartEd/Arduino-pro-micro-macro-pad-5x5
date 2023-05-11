# Arduino-pro-micro-macro-pad-5x5
A 5x5 macro-pad/keyboard with two encoders using the Arduino pro micro(atmega32u4). 

![Image](https://github.com/LennartEd/Arduino-pro-micro-macro-pad-5x5/blob/main/Macropad.jpg)

PARTS:
25x Keys (I used cherry black)
25x Keycaps (I used ones from an old keyboard)
2x Rotary encoder (I used: EC11B152442D)
2x small switches for reset and mode switch
4x m2x10mm screws and nuts (2 may be enough)

STL:
https://cad.onshape.com/documents/1b7fce78df1c33e90de1d30b/w/9420eb78f7612c8ff7084709/e/ba9b328cb87ac9f7e4928cc1?renderMode=0&uiState=645965fa6356355b74e0731e
1x Bottom
1x KeyPlate
1x Case
1x wheelBig
1x wheelSmall

Note: 
This is the version so a few mistakes went unnoticed:
- My keyPlate is stiff enough so the extra support colums without holes could be removed.
- The case works but i would redesign it. 
  - The horizontal encoder housing does not work well (I fixed some issues so the STL provided should be better but are untested)
  - I couldn't get the Pro-micro to fit onto the holder. (Bad wiring by me. Fixed some dimensions in Cad but these are also untested.)
  - !! You may want to move the Pro-micro as the cable port is towards the user (I thought a 90° cable would allow me to use the keyboard in two directions)

CODE:
Library used:
Keyboard by Arduino (https://www.arduino.cc/reference/en/language/functions/usb/keyboard/)
Mouse by Arduino (https://www.arduino.cc/reference/en/language/functions/usb/mouse/)
Encoder by Paul Stoffregen (https://www.pjrc.com/teensy/td_libs_Encoder.html)
Keypad by Mark Stanley, Alexander Brevig (https://playground.arduino.cc/Code/Keypad/)

Code is a mix between: 
RetroBuildGames V2.0 Arduino code (https://youtu.be/IDlcxLQ1SbY , http://www.retrobuiltgames.com/the-build-page/macro-keyboard-v2-0/)
And the MultiKey example from the Keypad library

