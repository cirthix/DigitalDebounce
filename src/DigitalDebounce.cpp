/*
 * DigitalDebounce, a library for simpler button use.
 * 
 * Copyright (C) 2016 cirthix@gmail.com
 * 
 * This file is part of DigitalDebounce.
 * 
 * This software is free software: you can redistribute it and/or modify it under the terms of the
 * GNU General Public License as published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.  In addition to or superseding this license, this
 * software may not be used in any form which is not completely free without the author's written 
 * consent.
 * 
 * This software is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * 
 * See the GNU General Public License for more details. You should have received a copy of the GNU
 * General Public License along with This software. If not, see <http://www.gnu.org/licenses/>.
 * 
 * Authors: cirthix@gmail.com
 */

#include <DigitalDebounce.h>

 
 

 // By default, internal pullup is disabled.  Call constructor with two arguments if desired.
DigitalDebounce::DigitalDebounce(uint8_t TargetPin)
:MyPin(TargetPin)
{
	DigitalDebounce::init(false);
}

DigitalDebounce::DigitalDebounce(uint8_t TargetPin, uint8_t InternalPullup)
:MyPin(TargetPin)
{
	DigitalDebounce::init(InternalPullup);
}

void		DigitalDebounce::init(uint8_t InternalPullup){
	if(InternalPullup==true) {	DigitalDebounce::SetPinInputPullup();}
	else {	DigitalDebounce::SetPinInput();}
	DigitalDebounce::Force(ReadPin());
	DigitalDebounce::ClearFlags();
}

// Revert the pin to it's default state 
DigitalDebounce::~DigitalDebounce(){DigitalDebounce::SetPinInput();}

uint8_t 	DigitalDebounce::Update(){return DigitalDebounce::Update(DigitalDebounce::ReadPin());}

uint8_t 	DigitalDebounce::Update(uint8_t value){
//	Serial.print("Raw: "); Serial.println(value);
	MyHistory=MyHistory<<1;
	if(value!=0){MyHistory|=0x01;}
	return DigitalDebounce::State();
}

void		DigitalDebounce::Force(uint8_t value){
	if(value!=0){MyHistory|=0xFF; MyLastStableState=0x01;} else {MyHistory=0x00; MyLastStableState=0x00;}
}

uint8_t		DigitalDebounce::State(){
	uint8_t MyState=BUTTON_UNDEFINED;
	if(MyHistory==0b00000000) {if(MyLastStableState==0x01) {DigitalDebounce::SetFlagPressed();  MyState=BUTTON_PRESSED;  } else {DigitalDebounce::SetFlagLow();  MyState=BUTTON_LOW; } MyLastStableState=0x00;}
	if(MyHistory==0b11111111) {if(MyLastStableState==0x00) {DigitalDebounce::SetFlagReleased(); MyState=BUTTON_RELEASED; } else {DigitalDebounce::SetFlagHigh(); MyState=BUTTON_HIGH;} MyLastStableState=0x01;}
	return MyState;
}
		
void	DigitalDebounce::ClearFlags(){
	ClearFlagReleased();
	ClearFlagPressed();	
	ClearFlagLow();		
	ClearFlagHigh();	
}


void		DigitalDebounce::SetFlagReleased()		{MyFlags |=(0x01<<FLAG_RELEASED);}
void		DigitalDebounce::SetFlagPressed()		{MyFlags |=(0x01<<FLAG_PRESSED);}	
void		DigitalDebounce::SetFlagLow()			{MyFlags |=(0x01<<FLAG_LOW);}		
void		DigitalDebounce::SetFlagHigh()			{MyFlags |=(0x01<<FLAG_HIGH);}	
void		DigitalDebounce::ClearFlagReleased()	{MyFlags &=~(0x01<<FLAG_RELEASED);}
void		DigitalDebounce::ClearFlagPressed()		{MyFlags &=~(0x01<<FLAG_PRESSED);}	
void		DigitalDebounce::ClearFlagLow()			{MyFlags &=~(0x01<<FLAG_LOW);}		
void		DigitalDebounce::ClearFlagHigh()		{MyFlags &=~(0x01<<FLAG_HIGH);}	


uint8_t		DigitalDebounce::WasReleased()	{uint8_t retval= MyFlags & (0x01<<FLAG_RELEASED); DigitalDebounce::ClearFlagReleased(); return retval;}
uint8_t		DigitalDebounce::WasPressed()	{uint8_t retval= MyFlags & (0x01<<FLAG_PRESSED); DigitalDebounce::ClearFlagPressed(); return retval;}	
uint8_t		DigitalDebounce::WasLow()		{uint8_t retval= MyFlags & (0x01<<FLAG_LOW); DigitalDebounce::ClearFlagLow(); return retval;}	
uint8_t		DigitalDebounce::WasHigh()		{uint8_t retval= MyFlags & (0x01<<FLAG_HIGH); DigitalDebounce::ClearFlagHigh(); return retval;}


 
 // IF PORTING TO ANOTHER MICROCONTROLLER, ONLY THE LINES BELOW TO BE CHANGED
uint8_t 	DigitalDebounce::ReadPin()				{ return digitalRead(MyPin);}
void		DigitalDebounce::SetPinInput()			{	pinMode(MyPin, INPUT);}	
void		DigitalDebounce::SetPinInputPullup()	{	pinMode(MyPin, INPUT_PULLUP); }
		
		
