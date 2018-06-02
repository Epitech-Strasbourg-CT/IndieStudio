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
	bool ret = true;

	if (_binds.count(event.EventType) <= 0)
		return false;
	try {
		_binds.at(event.EventType)(event);
	} catch (std::out_of_range &e) {
		static_cast<void>(e);
		ret = false;
	}
	return ret;
}

EventReceiver::EventReceiver()
{

}

void EventReceiver::unregisterEvent(irr::EEVENT_TYPE type, size_t idx)
{
	if (_binds.count(type) > 0) {
		_binds.erase(type);
	}
}

void EventReceiver::registerEvent(irr::EEVENT_TYPE type,
std::function<void(const irr::SEvent &)> fct)
{
	_binds[type] = fct;
}

EventReceiver &EventReceiver::getInstance()
{
	return _events;
}
