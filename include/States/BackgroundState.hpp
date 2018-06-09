/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** BackgroundState.hpp
*/

#include <irrlicht.h>
#include <vector>
#include <chrono>
#include "../Abstracts/AState.hpp"

#ifndef BOMBERMAN_BACKGROUNDSTATE_HPP
#define BOMBERMAN_BACKGROUNDSTATE_HPP

class BackgroundState : public AState {
public:
	BackgroundState(AStateShare &_share);

	void load() override;
	void unload() override;

	const std::string getName() const override;

	void transitionPop() override;
	void transitionPush(bool keep) override;

private:
	irr::scene::ISceneNode *_node;
	void loadMapMenu();
	void loadCharacter();
	void loadSkyBox();
	void loadMap();
	void loadCamRotate();

	SphericalCoordinate _camRotate;
	irr::f32 _inc;
};

#endif /* !BOMBERMAN_BACKGROUNDSTATE_HPP */
