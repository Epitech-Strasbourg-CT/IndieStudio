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
	TransitionToGameState(AStateShare &_share);
	void update() override;

private:
	Traveling _trav;
};

#endif /* !BOMBERMAN_TRANSITIONTOGAMESTATE_HPP */
