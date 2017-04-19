/*
 * KeyBoard.cpp
 *
 *  Created on: Apr 17, 2017
 *      Author: tim
 */

#include "KeyBoard.h"

KeyBoard::KeyBoard(): EventReader("/dev/input/event3", buffer, 64 * sizeof(struct input_event)), actions()
{
}

void KeyBoard::setEventAction(int button, std::function<void(int)> & action)
{
	actions.emplace(button, action);
}
void KeyBoard::checkEvent()
{

	readEvent();
	if(actions.count(buffer[1].code) and (buffer[0].value != ' ') and (buffer[1].value == 1) and (buffer[1].type == 1))
	{
		actions[buffer[1].code](buffer[1].code);
	}
}
