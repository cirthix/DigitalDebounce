
 This is the example project for demonstrating operation of the DigitalDebounce library.
Made by cirthix (cirthix@gmail.com)
Please see https://github.com/cirthix/DigitalDebounce for more information.


#include "DigitalDebounce.h"

#define BUTTON_PIN 3
const uint32_t SERIAL_BAUD 9600;
const uint32_t DELAYMS 10;

DigitalDebounce MyButton(BUTTON_PIN);
 
void setup() {	
 Serial.begin(SERIAL_BAUD); 
}

void loop() {
	// Note that the button update function can be called at any time (eg: interrupts) and processed separately (eg: interrupts).  Updates are decoupled from handling in this mode.  
	MyButton.Update(); 
	HandleButtons();
	delay(DELAYMS);

	// Alternatively, you can use the return value of the Update() function instead.  In this style, handling and processes are lock-stepped.
	HandleButtons(MyButton.Update());	
	delay(DELAYMS);
	
}

#define BUTTON_LOW 1
#define BUTTON_HIGH 2
#define BUTTON_RELEASED 3
#define BUTTON_PRESSED 4

void HandleButtons(uint8_t ButtonInput){
	switch (ButtonInput) {
		case BUTTON_LOW : HandleButtonLow();   		return ; 
		case BUTTON_HIGH : HandleButtonHigh();	return ; 
		case BUTTON_RELEASED : HandleButtonPressed();   return ; 
		case BUTTON_PRESSED : HandleButtonReleased();   	return ; 		
		default:  return ;
	}  	
}


void HandleButtons(){
	if(Mybutton.WasLow()) { HandleButtonLow();}
	if(Mybutton.WasHigh()) { HandleButtonHigh();}
	if(Mybutton.WasPressed()) { HandleButtonPressed();}
	if(Mybutton.WasReleased()) { HandleButtonReleased();}
}

void HandleButtonLow(){Serial.print(F"_"));}
void HandleButtonHigh(){Serial.print(F"-"));}
void HandleButtonPressed(){Serial.print(F"\"));}
void HandleButtonReleased(){Serial.print(F"/"));}
	
