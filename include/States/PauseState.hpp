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
#include "../Abstracts/AMenuSound.hpp"

#define PAUSE_BUTTON_NUMBER 4

class PauseState : public AState, public AMenuSound {
public:
	explicit PauseState(AStateShare &_share);
	~PauseState();

	enum Actions {
		RESUME = 300,
		SETTINGS,
		SAVE,
		EXIT_GAME
	};

	void loadButtons();
	void unloadButtons();
	void load() override;
	void unload() override;

	void update() override;

	void draw() override;

	void applyEventButton(const irr::SEvent &ev, PauseState::Actions id);
	irr::gui::IGUIButton *getButton(PauseState::Actions) const;

	struct ButtonsDesc {
		irr::core::rect<irr::s32> pos;
		std::string name;
		std::function<void(PauseState *)> fct;
	};

private:
	bool _escLock = true;
	std::vector<irr::gui::IGUIButton *> _buttons;

	static const std::map<PauseState::Actions, ButtonsDesc> _descs;
};

#endif /* !BOMBERMAN_PAUSESTATE_HPP */
