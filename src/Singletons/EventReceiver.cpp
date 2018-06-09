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
	auto type = event.EventType;
	if (_binds.count(event.EventType) <= 0)
		return false;
	for (auto it = _binds[type].begin(); it != _binds[type].end();) {
		if (!it->second(event)) {
			it = _binds[type].erase(it);
		} else
			it++;
	}
	if (_binds[type].empty())
		_binds.erase(type);
	return true;
}

EventReceiver::EventReceiver()
{

}

void EventReceiver::unregisterEvent(size_t id, irr::EEVENT_TYPE type)
{
	if (_binds.count(type) <= 0 || _binds[type].count(id) <= 0)
		return;
	_binds[type].erase(id);
	for (auto &n :_binds[type])
	if (_binds[type].empty())
		_binds.erase(type);
}

void EventReceiver::registerEvent(size_t id, irr::EEVENT_TYPE type,
std::function<bool(const irr::SEvent &)> fct)
{
	if (_binds.count(type) == 0) {
		std::unordered_map
		<size_t, std::function<bool(const irr::SEvent &)>> map;
		_binds.insert(std::make_pair(type, map));
	}
	_binds[type][id] = fct;
}

EventReceiver &EventReceiver::getInstance()
{
	return _events;
}
