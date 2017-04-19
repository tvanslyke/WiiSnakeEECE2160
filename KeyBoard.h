/*
 * KeyBoard.h
 *
 *  Created on: Apr 17, 2017
 *      Author: tim
 */

#ifndef KEYBOARD_H_
#define KEYBOARD_H_
#include <linux/input.h>
#include "EventReader.h"
#include <map>
class KeyBoard: public EventReader
{
private:
	std::map<int, std::function<void(int)>> actions;
	input_event buffer[64];
public:
	KeyBoard();
	void setEventAction(int button, std::function<void(int)> &  action);
	void checkEvent();
};

#endif /* KEYBOARD_H_ */
