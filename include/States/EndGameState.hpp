/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** EndGameState.hpp
*/

#ifndef BOMBERMAN_ENDGAMESTATE_HPP
#define BOMBERMAN_ENDGAMESTATE_HPP

#include "../Abstracts/AState.hpp"
#include "../Abstracts/AMenuSound.hpp"

#define ENDGAME_BUTTON_NUMBER 2

class EndGameState : public AState, public AMenuSound {
public:
	explicit EndGameState(AStateShare &_share);
	~EndGameState();

	enum Actions {
		RESTART = 700,
		EXIT
	};

	void loadButtons();
	void unloadButtons();
	void load() override;
	void unload() override;

	void update() override;

	void draw() override;

	const std::string getName() const override;

	void applyEventButton(const irr::SEvent &ev, EndGameState::Actions id);
	irr::gui::IGUIButton *getButton(EndGameState::Actions) const;

	struct ButtonsDesc {
		irr::core::rect<irr::s32> pos;
		std::string name;
		std::function<void(EndGameState *)> fct;
	};

private:
	//bool _escLock = true;
	std::vector<irr::gui::IGUIButton *> _buttons;
	static const std::map<EndGameState::Actions, ButtonsDesc> _descs;
};


#endif /* !BOMBERMAN_ENDGAMESTATE_HPP */
