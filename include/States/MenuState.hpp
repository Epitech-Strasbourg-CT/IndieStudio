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
#include <vector>
#include "../Abstracts/AState.hpp"
#include "../Game/SphericalCoordinate.hpp"

#ifndef BOMBERMAN_MENUSTATE_HPP
	#define BOMBERMAN_MENUSTATE_HPP

	#define BOUTON_NUMBER 4

enum MenuActions {
	LAUNCH = 100,
	LOAD,
	SETTINGS,
	EXIT_GAME
};

class MenuState : public AState {
public:

	explicit MenuState(AStateShare &_share);
	~MenuState();


	void loadButtons();
	void unloadButtons();
	void load() override;
	void unload() override;

	void update() override;

	void draw() override;

	void applyEventButton(const irr::SEvent &ev, MenuActions id);
	irr::gui::IGUIButton *getButton(MenuActions) const;

	struct ButtonsDesc {
		irr::core::rect<irr::s32> pos;
		std::string name;
		std::function<void(MenuState *)> fct;
	};

private:
	std::vector<irr::gui::IGUIButton *> _buttons;
	static const std::map<MenuActions , ButtonsDesc> _descs;
	irrklang::ISound *_sound;
	irr::gui::IGUIButton *_launch;
	irr::gui::IGUIButton *_load;
	irr::gui::IGUIButton *_settings;
	irr::gui::IGUIButton *_exit;
	irrklang::ISoundEngine *_engine;

	SphericalCoordinate _camRotate;

//	static const std::unordered_map<int,//irr::s32,
//	std::function<void(irr::s32, MenuState *)>> _assets;
//	std::vector<irr::gui::IGUIButton *> _buttons;
//	static const std::map<MenuActions , ButtonsDesc> _descs;
//	irrklang::ISound *_sound;
};

#endif //BOMBERMAN_MENUSTATE_HPP
