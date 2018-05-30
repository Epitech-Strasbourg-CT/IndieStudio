/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
**
*/
#include "../include/Singletons.hpp"
#include "../include/StateMachine.hpp"

int StateMachine::push(AState *gameState, bool keepLoaded)
{
	if (!keepLoaded && !_states.empty())
		_states.top()->unload();
	gameState->load();
	gameState->setEnable(true);
	_states.push(std::unique_ptr<AState>(gameState));
	return 0;
}

void StateMachine::pop()
{
	if (!_states.empty()) {
		auto top = _states.top().get();
		top->unload();
		_states.pop();
	}
}

int StateMachine::start()
{
	auto device = gameManager.getDevice();
	auto driver = gameManager.getDriver();
	auto smgr = gameManager.getSmgr();
	auto guienv = gameManager.getGuienv();

	smgr->addCameraSceneNode(0, irr::core::vector3df(0,30,-40),
				 irr::core::vector3df(0,5, 0));
	while (device->run()) {
//		std::cerr << "loop1" <<std::endl;
		driver->beginScene(true, true,
		irr::video::SColor(255, 100, 101, 140));
//		std::cerr << "loop2" <<std::endl;
		if (!_states.empty())
			_states.top()->update();
//		std::cerr << "loop3" <<std::endl;
		smgr->drawAll();
//		std::cerr << "loop4" <<std::endl;
		guienv->drawAll();
//		std::cerr << "loop5" <<std::endl;
		driver->endScene();
//		std::cerr << "loop6" <<std::endl;
		gameManager.upCycles();
	}
	return 0;
}

AState *StateMachine::top()
{
	if (_states.empty())
		return nullptr;
	return _states.top().get();
}
