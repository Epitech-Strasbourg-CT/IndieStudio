/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
**
*/

#include "../../include/States/MenuState.hpp"
#include "../../include/Singletons/GameManager.hpp"
#include "../../include/Singletons/StateMachine.hpp"

const std::unordered_map<irr::s32, std::function<void(irr::s32, MenuState *)>> MenuState::_assets {
	{100, [](irr::s32 type, MenuState *me) {
		if (type == irr::gui::EGET_BUTTON_CLICKED)
			StateMachine::getInstance().pop();
	}}
};

void MenuState::update()
{
}

void MenuState::load()
{
	auto &gm = GameManager::getInstance();
	irr::core::rect<irr::s32> rect = {0, 0, 100, 100};
	gm.getGuienv()->addButton(rect, 0, 100, L"Test", L"wesh");
	AState::load();
}

void MenuState::unload()
{
	AState::unload();
}
