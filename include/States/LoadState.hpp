/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** LoadState.hpp
*/

#ifndef BOMBERMAN_LOADSTATE_HPP
#define BOMBERMAN_LOADSTATE_HPP

#include <vector>
#include "../Abstracts/AState.hpp"
#include "../Abstracts/AMenuSound.hpp"

#define LOAD_BUTTON_NUMBER 7

class LoadState : public AState, public AMenuSound{
public:
	explicit LoadState(AStateShare &_share);
	~LoadState() override;

	enum Actions {
		SAVE1 = 500,
		SAVE2,
		SAVE3,
		SAVE4,
		CANCEL,
		PREV,
		NEXT
	};

	void loadButtons();
	void unloadButtons();

	void load() override;
	void unload() override;
	void update() override;
	void draw() override;

	bool applyEventButton(const irr::SEvent &ev, LoadState::Actions id);
	irr::gui::IGUIButton *getButton(LoadState::Actions) const;

	const std::string getName() const override;

	struct ButtonsDesc {
		irr::core::rect<irr::s32> pos;
		std::string name;
		std::function<bool(LoadState *)> fct;
	};

	void eventsSetup();
	void externalEventsClean();

private:
	void setSaveButtons();

	std::vector<irr::gui::IGUIButton *> _buttons;
	static const std::map<LoadState::Actions, ButtonsDesc> _descs;
	std::vector<std::string> _saves;
	size_t _idx;
	bool _eventsActivate;
	void eventsClean();
};

#endif /* !BOMBERMAN_LOADSTATE_HPP */
