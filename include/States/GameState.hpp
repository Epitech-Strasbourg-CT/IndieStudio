/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** GameState.hpp
*/

#ifndef BOMBERMAN_GAMESTATE_HPP
	#define BOMBERMAN_GAMESTATE_HPP


#include "../Abstracts/AState.hpp"

class GameState : public AState {
public:
	GameState(AStateShare &_share);
	void load() override;
	void unload() override;
	void transitionPop() override;
	void transitionPush() override;
	void update() override;
};


#endif /* !BOMBERMAN_GAMESTATE_HPP */
