/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** PauseState.hpp
*/

#ifndef BOMBERMAN_PAUSESTATE_HPP
#define BOMBERMAN_PAUSESTATE_HPP

#include <IGUIButton.h>
#include <vector>
#include "../Abstracts/AState.hpp"

#define PAUSE_BUTTON_NUMBER 3

enum PauseActions {
	RESUME = 300,
	SETTINGS,
	EXIT_GAME
};

class PauseState : public AState {
public:
	explicit PauseState(AStateShare &_share);
	~PauseState();


	void loadButtons();
	void unloadButtons();
	void load() override;
	void unload() override;

	void update() override;

	void draw() override;

	void applyEventButton(const irr::SEvent &ev, PauseActions id);
	irr::gui::IGUIButton *getButton(PauseActions) const;

	struct ButtonsDesc {
		irr::core::rect<irr::s32> pos;
		std::string name;
		std::function<void(PauseState *)> fct;
	};

private:
	std::vector<irr::gui::IGUIButton *> _buttons;
	static const std::map<PauseActions , ButtonsDesc> _descs;
	irr::gui::IGUIButton *_resume;
	irr::gui::IGUIButton *_settings;
	irr::gui::IGUIButton *_exit;
};

#endif /* !BOMBERMAN_PAUSESTATE_HPP */
