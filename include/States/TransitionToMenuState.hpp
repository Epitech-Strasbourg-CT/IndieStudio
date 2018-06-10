/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** TransitionToMenuState.hpp
*/

#ifndef BOMBERMAN_TRANSITIONTOMENU_HPP
	#define BOMBERMAN_TRANSITIONTOMENU_HPP

	#include "../Abstracts/AState.hpp"
	#include "../Game/Traveling.hpp"

class TransitionToMenuState : public AState {
public:
	TransitionToMenuState(AStateShare &_share);

	void update() override;
	void unloadDeadPlayer();

	const std::string getName() const override;

private:
	Traveling _trav;
};

#endif /* !BOMBERMAN_TRANSITIONTOMENU_HPP */
