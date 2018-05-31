/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** EventReceiver.hpp
*/
#include <functional>
#include <irrlicht.h>
#include <map>
#include "GameManager.hpp"

#ifndef BOMBERMAN_EVENTRECEIVER_HPP
#define BOMBERMAN_EVENTRECEIVER_HPP

class EventReceiver : public irr::IEventReceiver {
public:
	using binds_map_t =
	std::map<size_t, std::function<void(const irr::SEvent &event)>>;
	using abstract_event_fct_t =
	std::function<void(EventReceiver *me, const irr::SEvent &)>;

	static EventReceiver &getInstance();

	bool OnEvent(const irr::SEvent &event) override;
	void registerEvent(irr::EEVENT_TYPE, size_t,
		std::function<void(const irr::SEvent &)> fct
	);
	void unregisterEvent(irr::EEVENT_TYPE, size_t);
private:

	EventReceiver();
	std::map<irr::EEVENT_TYPE, binds_map_t> _binds;
	static EventReceiver _events;
	static const std::map<irr::EEVENT_TYPE, abstract_event_fct_t>
	_spec_calls;

};

#endif /* !BOMBERMAN_EVENTRECEIVER_HPP */
