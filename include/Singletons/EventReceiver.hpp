/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** EventReceiver.hpp
*/
#include <functional>
#include <irrlicht.h>
#include <map>

#ifndef BOMBERMAN_EVENTRECEIVER_HPP
#define BOMBERMAN_EVENTRECEIVER_HPP

class EventReceiver : public irr::IEventReceiver {
public:
	EventReceiver();
	bool OnEvent(const irr::SEvent &event) override;
	void registerEvent(irr::gui::EGUI_EVENT_TYPE, const std::function<void
	(const irr::SEvent &event)> &fct);
	void unregisterEvent(irr::gui::EGUI_EVENT_TYPE);
private:
	std::map<irr::gui::EGUI_EVENT_TYPE, std::function<void(const irr::SEvent &event)>> _binds;
};


#endif /* !BOMBERMAN_EVENTRECEIVER_HPP */
