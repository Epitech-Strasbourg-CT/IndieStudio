/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** AState.cpp
*/
#include <irrlicht.h>
#include <vector>
#include <chrono>
#include "../AState.hpp"

#ifndef BOMBERMAN_SPLASHSTATE_HPP
#define BOMBERMAN_SPLASHSTATE_HPP


class SplashState : public AState {
public:
	SplashState();
	virtual ~SplashState() = default;
	void update() override;
	void load() override;
	void unload() override;

private:
	std::vector<irr::scene::ISceneNode *> _nodes;
	size_t _start;
	size_t _duration;
};


#endif //BOMBERMAN_SPLASHSTATE_HPP
