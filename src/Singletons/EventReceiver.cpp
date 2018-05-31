/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** EventReceiver.cpp
*/

#include "../../include/Singletons/EventReceiver.hpp"



bool EventReceiver::OnEvent(const irr::SEvent &event)
{
	return false;
}

EventReceiver::EventReceiver()
{

}

void EventReceiver::unregisterEvent(irr::gui::EGUI_EVENT_TYPE type)
{
	if (_binds.count(type) > 0)
		_binds.erase(type);
}

void EventReceiver::registerEvent(irr::gui::EGUI_EVENT_TYPE type,
	std::function<void(const irr::SEvent &)> fct
)
{
	_binds[type] = fct;
}

EventReceiver &EventReceiver::getInstance()
{
	return _events;
}
