/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** GameState.cpp
*/

#include "../../include/States/GameState.hpp"
#include "../../include/Singletons/GameManager.hpp"
#include "../../include/Singletons/EventReceiver.hpp"
#include "../../include/Singletons/StateMachine.hpp"

void GameState::update()
{

}

GameState::GameState(AStateShare &_share) : AState(_share)
{
}

void GameState::load()
{
	auto er = EventReceiver::getInstance();

	er.registerEvent(irr::EEVENT_TYPE::EET_KEY_INPUT_EVENT,
			 irr::KEY_KEY_A,
			 [this](const irr::SEvent &ev) {
				 std::cout << "POP" << std::endl;
			 }
	);
	auto &n = _share.getSharedNode("tree");
	n.remove();
	addAlteredNode(&n, [](irr::scene::ISceneNode *n) {
		std::cout << "restore" << std::endl;
	//	n->render();
	});
	AState::load();
}

void GameState::unload()
{
	AState::unload();
}

void GameState::transitionPop()
{
	AState::transitionPop();
}

void GameState::transitionPush()
{
	std::cout << "PUSHING GAMESTATE" << std::endl;
	AState::transitionPush();
}
