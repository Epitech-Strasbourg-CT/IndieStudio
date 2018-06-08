/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** SaveState.hpp
*/

#ifndef BOMBERMAN_SAVESTATE_HPP
#define BOMBERMAN_SAVESTATE_HPP

#include "../Abstracts/AState.hpp"

#define SAVE_BUTTON_NUMBER 2

class SaveState : public AState {
public:
	explicit SaveState(AStateShare &_share);
	~SaveState();

	enum Actions {
		SAVE = 600,
		CANCEL
	};

	void loadButtons();
	void unloadButtons();
	void load() override;
	void unload() override;

	void update() override;

	void draw() override;

	void applyEventButton(const irr::SEvent &ev, SaveState::Actions id);
	irr::gui::IGUIButton *getButton(SaveState::Actions) const;

	struct ButtonsDesc {
		irr::core::rect<irr::s32> pos;
		std::string name;
		std::function<void(SaveState *)> fct;
	};

private:
	std::vector<irr::gui::IGUIButton *> _buttons;
	static const std::map<SaveState::Actions, ButtonsDesc> _descs;
	irr::gui::IGUIEditBox *_name;
};

#endif /* !BOMBERMAN_SAVESTATE_HPP */
