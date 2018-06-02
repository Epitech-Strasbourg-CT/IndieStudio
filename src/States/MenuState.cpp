/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
**
*/

#include "../../include/States/MenuState.hpp"
#include "../../include/Singletons/IrrManager.hpp"
#include "../../include/Singletons/StateMachine.hpp"
#include "../../include/Singletons/EventReceiver.hpp"
#include "../../include/States/GameState.hpp"

const std::unordered_map<irr::s32, std::function<void(irr::s32, MenuState *)>>
MenuState::_assets
{
{100, [](irr::s32 type, MenuState *self) {
	if (type == irr::gui::EGET_BUTTON_CLICKED) {
		StateMachine::getInstance()
		.push(new GameState(self->getSharedResources()), false);
	}
}},
{101, [](irr::s32 type, MenuState *self) {
	if (type == irr::gui::EGET_BUTTON_CLICKED) {
		StateMachine::getInstance().pop();
	}
}},
{102, [](irr::s32 type, MenuState *self) {
	if (type == irr::gui::EGET_BUTTON_CLICKED) {
		StateMachine::getInstance().pop();
	}
}}};

MenuState::MenuState(AStateShare &_share) : AState(_share)
{
}

void MenuState::load()
{
	std::cout << "OK" << std::endl;
	auto &gm = IrrManager::getInstance();
	auto &er = EventReceiver::getInstance();
	er.registerEvent(irr::EEVENT_TYPE::EET_GUI_EVENT,
	[this](const irr::SEvent &ev) {
		auto id = ev.GUIEvent.Caller->getID();
		if (ev.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED &&
		MenuState::_assets.count(id) > 0)
			MenuState::_assets.at(id)(ev.GUIEvent.EventType, this);
	});
	_launch = gm.getGuienv()->addButton({50, 50, 750, 100}, nullptr, 100,
					    L"Launch game", L"Starts the game");
	_settings = gm.getGuienv()->addButton({50, 150, 750, 200}, nullptr,
					      101,
					      L"Settings", L"Settings menu");
	_exit = gm.getGuienv()->addButton({50, 250, 750, 300}, nullptr, 102,
					  L"Exit",
					  L"Leaves the game");
	AState::load();
	std::cout << "OK END" << std::endl;
}

void MenuState::unload()
{
	auto &er = EventReceiver::getInstance();
	er.unregisterEvent(irr::EEVENT_TYPE::EET_GUI_EVENT,
			   irr::gui::EGET_BUTTON_CLICKED);
	_launch->remove();
	_settings->remove();
	_exit->remove();
	std::cout << "Unload menu" << std::endl;
	AState::unload();
}

void MenuState::draw()
{
	std::cout << "DRAW" << std::endl;
	auto im = IrrManager::getInstance();
	im.getSmgr()->drawAll();
	im.getGuienv()->drawAll();
	std::cout << "DRAW END" << std::endl;
}
