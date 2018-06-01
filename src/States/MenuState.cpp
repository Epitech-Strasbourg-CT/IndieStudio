/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
**
*/

#include "../../include/States/MenuState.hpp"
#include "../../include/Singletons/GameManager.hpp"
#include "../../include/Singletons/StateMachine.hpp"
#include "../../include/Singletons/EventReceiver.hpp"

const std::unordered_map<irr::s32, std::function<void(irr::s32, MenuState *)>>
MenuState::_assets
{
{100, [](irr::s32 type, MenuState *self) {
	if (type == irr::gui::EGET_BUTTON_CLICKED) {
		StateMachine::getInstance().pop();
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

void MenuState::update()
{
}

void MenuState::load()
{
	auto &gm = GameManager::getInstance();
	auto &er = EventReceiver::getInstance();
	er.registerEvent(irr::EEVENT_TYPE::EET_GUI_EVENT,
			 irr::gui::EGET_BUTTON_CLICKED,
			 [this](const irr::SEvent &ev) {
				 auto id = ev.GUIEvent.Caller->getID();
				 if (MenuState::_assets.count(id) > 0)
					 MenuState::_assets.at(id)(
					 ev.GUIEvent.EventType,
					 this);
			 }

	);
	_launch = gm.getGuienv()->addButton({50, 50, 750, 100}, nullptr, 100,
					    L"Launch game", L"Starts the game");
	_settings = gm.getGuienv()->addButton({50, 150, 750, 200}, nullptr,
					      101,
					      L"Settings", L"Settings menu");
	_exit = gm.getGuienv()->addButton({50, 250, 750, 300}, nullptr, 102,
					  L"Exit",
					  L"Leaves the game");
	er.registerEvent(irr::EEVENT_TYPE::EET_KEY_INPUT_EVENT,
			 irr::KEY_KEY_A,
			 [this](const irr::SEvent &ev) {
				if (ev.KeyInput.PressedDown)
					std::cout << "OK2" << std::endl;
			 }
	);
	AState::load();

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

MenuState::MenuState(AStateShare &_share) : AState(_share)
{
}
