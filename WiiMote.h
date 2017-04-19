/*
 * WiiMote.h
 *
 *  Created on: Apr 16, 2017
 *      Author: tim
 */

#ifndef WIIMOTE_H_
#define WIIMOTE_H_

#include <map>
#include <functional>
#include <queue>
#include "EventReader.h"
#include <iostream>

namespace wii{
enum ButtonCode
{
	NONE = 0,
	ONE = 1,     // esc on keyboard
	TWO = 2,     // number '1' on keyboard (not numpad)
	A = 48,      // b on keyboard
	B = 49,      // n on keyboard
	HOME = 60,   // f2 on keyboard
	UP = 103,    // up arrow on keyboard
	LEFT = 105,  // left arrow on keyboard
	RIGHT = 106, // right arrow on keyboard
	DOWN = 108,  // down arrow on keyboard
	PLUS = 151,  // not available on keyboard
	MINUS = 156  // not available on keyboard
};
class WiiMote: public EventReader
{
private:
	std::map<ButtonCode, std::function<void(ButtonCode)>> actions;
	char buffer[32];
public:
	WiiMote();
	void setEventAction(int button, std::function<void(int)> &  action);
	void checkEvent();
};

}
#endif /* WIIMOTE_H_ */
