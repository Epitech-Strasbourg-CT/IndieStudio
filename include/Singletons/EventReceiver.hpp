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
	static EventReceiver &getInstance();

	bool OnEvent(const irr::SEvent &event) override;
	void registerEvent(irr::gui::EGUI_EVENT_TYPE,
		std::function<void(const irr::SEvent &)> fct
	);
	void unregisterEvent(irr::gui::EGUI_EVENT_TYPE);
private:
	EventReceiver();
	std::map<irr::gui::EGUI_EVENT_TYPE, std::function<void(const irr::SEvent &event)>> _binds;
	static EventReceiver _events;

};


#endif /* !BOMBERMAN_EVENTRECEIVER_HPP */
