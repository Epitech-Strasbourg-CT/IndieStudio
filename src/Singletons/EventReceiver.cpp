/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** EventReceiver.cpp
*/

#include <iostream>
#include "../../include/Singletons/EventReceiver.hpp"

EventReceiver EventReceiver::_events;

const std::map<irr::EEVENT_TYPE, EventReceiver::abstract_event_fct_t>
EventReceiver::_spec_calls = {
	{irr::EET_GUI_EVENT, [](
	EventReceiver *me,
	const irr::SEvent &event){
		me->_binds.at(event.EventType)
		.at(event.GUIEvent.EventType)(event);
	}},
//	{irr::EET_MOUSE_INPUT_EVENT, [](const irr::SEvent &event){
//
//	}},
	{irr::EET_KEY_INPUT_EVENT, [](EventReceiver *me, const irr::SEvent
	&event){
		me->_binds.at(event.EventType)
		.at(event.KeyInput.Key)(event);
	}}//,
//	{irr::EET_JOYSTICK_INPUT_EVENT, [](const irr::SEvent &event){
//
//	}}//,
//	{irr::EET_LOG_TEXT_EVENT, [](const irr::SEvent &event){
//
//	}},
//	{irr::EET_USER_EVENT, [](const irr::SEvent &event){
//
//	}},
//	{irr::EGUIET_FORCE_32_BIT, [](){
//
//	}}
};

bool EventReceiver::OnEvent(const irr::SEvent &event)
{
	bool ret = true;

	if (_binds.count(event.EventType) <= 0)
		return false;
	try {
		EventReceiver::_spec_calls.at(event.EventType)(this, event);
	} catch (std::out_of_range &e) {
		static_cast<void>(e);
	}
	return ret;
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
