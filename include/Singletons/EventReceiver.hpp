/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** EventReceiver.hpp
*/
#include <functional>
#include <irrlicht.h>
#include <unordered_map>
#include "IrrManager.hpp"

#ifndef BOMBERMAN_EVENTRECEIVER_HPP
#define BOMBERMAN_EVENTRECEIVER_HPP

class EventReceiver : public irr::IEventReceiver {
public:
	static EventReceiver &getInstance();

	bool OnEvent(const irr::SEvent &event) override;
	void registerEvent(size_t id, irr::EEVENT_TYPE,
	std::function<bool(const irr::SEvent &)> fct);
	void unregisterEvent(size_t id, irr::EEVENT_TYPE);
private:
	EventReceiver();
	std::unordered_map<size_t,//irr::EEVENT_TYPE,
	std::unordered_map<size_t, std::function<bool(const irr::SEvent &)>>>
	_binds;

	static EventReceiver _events;
};

#endif /* !BOMBERMAN_EVENTRECEIVER_HPP */
