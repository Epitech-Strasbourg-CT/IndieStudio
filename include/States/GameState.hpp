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

	void update() override;

private:
	irr::scene::ISceneNode *_node;
};


#endif /* !BOMBERMAN_GAMESTATE_HPP */
