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
#include <irrKlang.h>
#include <IGUIButton.h>
#include "../Abstracts/AState.hpp"

#ifndef BOMBERMAN_MENUSTATE_HPP
#define BOMBERMAN_MENUSTATE_HPP

class MenuState : public AState {
public:
	MenuState(AStateShare &_share);
	~MenuState();

	void load() override;
	void unload() override;

	void draw() override;

private:
	irr::gui::IGUIButton *_launch;
	irr::gui::IGUIButton *_settings;
	irr::gui::IGUIButton *_exit;
	irrklang::ISoundEngine *_engine;

	static const std::unordered_map<int,//irr::s32,
	std::function<void(irr::s32, MenuState *)>> _assets;
};

#endif //BOMBERMAN_MENUSTATE_HPP
