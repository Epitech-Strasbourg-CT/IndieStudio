/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** PodiumState.hpp
*/

#ifndef BOMBERMAN_PODIUMSTATE_HPP
	#define BOMBERMAN_PODIUMSTATE_HPP

	#include "../Abstracts/AState.hpp"
	#include "../Game/Traveling.hpp"

class PodiumState : public AState {
public:
	PodiumState(AStateShare &_share);
	void update() override;
	void unload() override;

	const std::string getName() const override;

	enum MenuActions {
		RESTART = 500,
		QUIT
	};

	struct ButtonsDesc {
		irr::core::rect<irr::s32> pos;
		std::string name;
		std::function<bool(PodiumState *)> fct;
	};


private:
	Traveling _trav;
	std::vector<irr::gui::IGUIButton *> _buttons;
	static const std::map<MenuActions , ButtonsDesc> _descs;
	void setText();
	void loadButtons();
	irr::gui::IGUIButton *getButton(MenuActions id) const;

	bool _isLoad;

	void eventsSetup();

	bool applyEventButton(const irr::SEvent &ev, MenuActions id);

	void unloadButtons();
};

#endif /* !BOMBERMAN_PODIUMSTATE_HPP */
