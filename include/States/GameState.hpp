/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** GameState.hpp
*/

#ifndef BOMBERMAN_GAMESTATE_HPP
	#define BOMBERMAN_GAMESTATE_HPP


	#include "../Abstracts/AState.hpp"
	#include "../Game/EntitiesMap.hpp"
	#include "../Game/Entities/PlayerEntity.hpp"

class GameState : public AState {
public:
	GameState(AStateShare &_share);

	const std::string getName() const override;

	GameState(AStateShare &_share, std::string &);
	void load() override;
	void update() override;
	void updateRender() override;
	void animCam();
private:
	void addDeadPlayer(int idPlayer, int rank);
	void addLastPlayerDead(std::vector<int> podium);
	bool _canPause;
	irr::f32 _inc;
	size_t _nbPlayerTot;
};


#endif /* !BOMBERMAN_GAMESTATE_HPP */
