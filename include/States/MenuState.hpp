/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
**
*/
#include <cstdio>
#include <unordered_map>
#include <functional>
#include <irrTypes.h>
#include <IGUIButton.h>
#include "AState.hpp"

#ifndef BOMBERMAN_MENUSTATE_HPP
#define BOMBERMAN_MENUSTATE_HPP

class MenuState : public AState {
public:
	void load() override;
	void unload() override;
	void update() override;
	static const std::unordered_map<irr::s32, std::function<void(irr::s32, MenuState *)>> _assets;
	irr::gui::IGUIButton *_boutton;
};

#endif //BOMBERMAN_MENUSTATE_HPP
