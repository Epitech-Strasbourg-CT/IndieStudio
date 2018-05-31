/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** EventReceiver.cpp
*/

#include <iostream>
#include "../../include/Singletons/EventReceiver.hpp"

EventReceiver EventReceiver::_events;

bool EventReceiver::OnEvent(const irr::SEvent &event)
{
	if (_binds.count(event.EventType) > 0) {
		switch (event.EventType) {
			case irr::EET_GUI_EVENT :
				std::cout << "GUI" << std::endl;
				_binds.at(event.EventType).
				at(event.GUIEvent.EventType)(event);
				break;
			case irr::EET_MOUSE_INPUT_EVENT:break;
			case irr::EET_KEY_INPUT_EVENT:break;
			case irr::EET_JOYSTICK_INPUT_EVENT:break;
			case irr::EET_LOG_TEXT_EVENT:break;
			case irr::EET_USER_EVENT:break;
			case irr::EGUIET_FORCE_32_BIT:break;
			default:
				break;
		}
		return true;
	}
	return false;
}

EventReceiver::EventReceiver()
{

}

void EventReceiver::unregisterEvent(irr::EEVENT_TYPE type, size_t idx)
{
	if (_binds.count(type) > 0 && _binds.at(type).count(idx) > 0) {
		_binds.at(type).erase(idx);
		if (_binds.count(type) == 0)
			_binds.erase(type);
	}
}

void EventReceiver::registerEvent(irr::EEVENT_TYPE type,
size_t size, std::function<void(const irr::SEvent &)> fct)
{
	_binds[type][size] = fct;
}

EventReceiver &EventReceiver::getInstance()
{
	return _events;
}
