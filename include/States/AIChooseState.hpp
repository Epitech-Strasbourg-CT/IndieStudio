/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** AIChooseState.hpp
*/

#ifndef BOMBERMAN_AICHOOSESTATE_HPP
	#define BOMBERMAN_AICHOOSESTATE_HPP

	#include <irrlicht.h>
	#include "../Abstracts/AState.hpp"
	#include "../Game/Traveling.hpp"
#include "../Abstracts/AMenuSound.hpp"

class AIChooseState : public AState, public AMenuSound {
public:
	AIChooseState(AStateShare &_share);
	virtual ~AIChooseState();
	void update();

	void load() override;

	enum MenuActions {
		LAUNCH = 400,
		PLY1,
		PLY2,
		PLY3,
		PLY4
	};

	struct BouttonsDesc {
		irr::core::rect<irr::s32> pos;
		std::string name;
		std::function<bool(AIChooseState *)> fct;
	};
	void unload() override;

	void eventsSetup();
	void eventsClean();
	void externalEventsClean();

private:
	void switchBtnState(irr::gui::IGUIButton *btn, int id);
	bool applyEventButton(const irr::SEvent &ev, MenuActions id);

public:
	const std::string getName() const override;

private:
	std::vector<irr::gui::IGUIButton *> _bouttons;
	static const std::map<MenuActions, BouttonsDesc> _descs;
	Traveling _trav;
	Traveling _quitAnim;
	void loadBouttons();
	irr::gui::IGUIButton *getBoutton(MenuActions id) const;
	std::vector<int> _state;

	bool _isInQuitAnim;
	bool _guiDisp;

	void unloadBouttons();

	void moveCamToStartPoint(irr::scene::ICameraSceneNode &node);
	bool _eventsActivate;
};


#endif /* !BOMBERMAN_AICHOOSESTATE_HPP */
