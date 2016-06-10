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

#ifndef DIGITALDEBOUNCE_h
#define DIGITALDEBOUNCE_h

#include <Arduino.h>
#define BUTTON_UNDEFINED 0
#define BUTTON_LOW 1
#define BUTTON_HIGH 2
#define BUTTON_RELEASED 3
#define BUTTON_PRESSED 4
 
#pragma GCC optimize("O3")
 									// Saves the targeted pin number
class DigitalDebounce
{
	public:  
					DigitalDebounce(uint8_t TargetPin);								// Constructor stub.
					DigitalDebounce(uint8_t TargetPin, uint8_t InternalPullup);		// Constructor stub.
					~DigitalDebounce();							// Destroys the object, reverts clock speed and serial speed to stock speeds.
		uint8_t		Update();									// Reads the pin, saving and filtering the input.  Returns the current button state.
		uint8_t		Update(uint8_t value);						// Updates the saved value manually.  Returns the current button state.
		void		Force(uint8_t value);						// Updates the saved value manually and erases history.
		uint8_t		State();									// Returns the current button state.
		void		ClearFlags();								// Clears all flags.
		uint8_t		WasReleased();								// Returns 0 if the button has been released.  Clears the 'released' flag.
		uint8_t		WasPressed();								// Returns 0 if the button has been pressed.  Clears the 'pressed' flag.
		uint8_t		WasLow();									// Returns 0 if the button has been held low.  Clears the 'low' flag.
		uint8_t		WasHigh();									// Returns 0 if the button has been held high.  Clears the 'high' flag.
	private:  			                                        // 
		void		init(uint8_t InternalPullup);				// The real constructor which creates the object and saves the targeted pin.
		uint8_t		ReadPin();									// Returns the current pin state.
		void		SetPinInput();								// Sets the pin to input mode.
		void		SetPinInputPullup();						// Sets the pin to input mode with internal pullup resistor.
		void		SetFlagReleased();							// Sets the 'released' flag.
		void		SetFlagPressed();							// Sets the 'pressed' flag.
		void		SetFlagLow();								// Sets the 'low' flag.
		void		SetFlagHigh();								// Sets the 'high' flag.
		void		ClearFlagReleased();						// Clears the 'released' flag.
		void		ClearFlagPressed();							// Clears the 'pressed' flag.
		void		ClearFlagLow();								// Clears the 'low' flag.
		void		ClearFlagHigh();							// Clears the 'high' flag.
		const uint8_t 	MyPin;	
		uint8_t		MyLastStableState;							// Holds previous stable button reading
		uint8_t		MyHistory;									// Holds previous button readings
		uint8_t 	MyFlags;									// Saves the targeted pin number
		static const uint8_t FLAG_RELEASED 	= 0;
		static const uint8_t FLAG_PRESSED 	= 1;
		static const uint8_t FLAG_HIGH 		= 2;
		static const uint8_t FLAG_LOW 		= 3;
		
};		
#endif
