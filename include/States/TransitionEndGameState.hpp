/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** TransitionEndGameState.hpp
*/

#ifndef BOMBERMAN_TRANSITIONENDGAMESTATE_HPP
	#define BOMBERMAN_TRANSITIONENDGAMESTATE_HPP

	#include <irrlicht.h>
	#include "../Abstracts/AState.hpp"
#include "../Game/Traveling.hpp"


class TransitionEndGameState : public AState {
public:
	TransitionEndGameState(AStateShare &_share);

	void update() override;

private:
	Traveling _trav;
};

#endif /* !BOMBERMAN_TRANSITIONENDGAMESTATE_HPP */
