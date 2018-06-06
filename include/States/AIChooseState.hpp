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
	#include "../../src/Game/Traveling.hpp"

class AIChooseState : public AState {
public:
	AIChooseState(AStateShare &_share);
	void update();

private:
	Traveling _trav;
};


#endif /* !BOMBERMAN_AICHOOSESTATE_HPP */
