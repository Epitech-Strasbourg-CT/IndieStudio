/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** SaveState.hpp
*/

#ifndef BOMBERMAN_SAVESTATE_HPP
#define BOMBERMAN_SAVESTATE_HPP

#include <time.h>
#include "../Abstracts/AState.hpp"
#include "../Abstracts/AMenuSound.hpp"

#define SAVE_BUTTON_NUMBER 2

class SaveState : public AState, public AMenuSound {
public:
	explicit SaveState(AStateShare &_share);
	~SaveState();

	enum Actions {
		SAVE = 800,
		CANCEL
	};

	const std::string getName() const override;

	void loadButtons();
	void unloadButtons();
	void load() override;
	void unload() override;

	void update() override;

	void draw() override;

	bool applyEventButton(const irr::SEvent &ev, SaveState::Actions id);
	irr::gui::IGUIButton *getButton(SaveState::Actions) const;

	struct ButtonsDesc {
		irr::core::rect<irr::s32> pos;
		std::string name;
		std::function<bool(SaveState *)> fct;
	};

	void eventsSetup();
	void eventsClean();
	void externalEventsClean();

private:
	std::vector<irr::gui::IGUIButton *> _buttons;
	static const std::map<SaveState::Actions, ButtonsDesc> _descs;
	irr::gui::IGUIButton *_name;
	bool _eventsActivate;
};

#endif /* !BOMBERMAN_SAVESTATE_HPP */
