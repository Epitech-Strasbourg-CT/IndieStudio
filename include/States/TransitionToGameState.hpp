/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** TransitionToGameState.hpp
*/

#ifndef BOMBERMAN_TRANSITIONTOGAMESTATE_HPP
	#define BOMBERMAN_TRANSITIONTOGAMESTATE_HPP

	#include <irrlicht.h>
	#include "../Abstracts/AState.hpp"
	#include "../Game/Traveling.hpp"

class TransitionToGameState : public AState {
public:
	TransitionToGameState(AStateShare &_share, const std::string &str = "");
	void update() override;
	void transitionPop() override;
	void transitionPush(bool keep) override;
	void updateRender() override;

private:
	Traveling _trav;
	EntitiesMap _emap;
};

#endif /* !BOMBERMAN_TRANSITIONTOGAMESTATE_HPP */
