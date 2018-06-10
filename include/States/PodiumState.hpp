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
#include "../Abstracts/AMenuSound.hpp"

class PodiumState : public AState, public AMenuSound {
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
	void loadText();
	void loadButtons();
	irr::gui::IGUIButton *getButton(MenuActions id) const;
	std::vector<irr::scene::ITextSceneNode *> _text;

	bool _isLoad;

	void eventsSetup();

	bool applyEventButton(const irr::SEvent &ev, MenuActions id);

	void unloadButtons();
	void unloadDeadPlayer();
};

#endif /* !BOMBERMAN_PODIUMSTATE_HPP */
