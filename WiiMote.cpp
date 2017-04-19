/*
 * WiiMote.cpp
 *
 *  Created on: Apr 16, 2017
 *      Author: tim
 */

#include "WiiMote.h"
namespace wii{

WiiMote::WiiMote(): EventReader("/dev/input/event2", buffer, 32), actions()
{
}

void WiiMote::setEventAction(int button, std::function<void(int)> &  action)
{
	actions[ButtonCode(button)] = action;
}
void WiiMote::checkEvent()
{
	readEvent();
	auto code = ButtonCode(buffer[10]);
	if(actions.count(code) and buffer[12])
	{
		actions[code](code);
	}
}

}
