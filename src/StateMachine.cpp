/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
**
*/
#include "../include/Singletons.hpp"
#include "../include/StateMachine.hpp"

void StateMachine::push(AState *gameState, bool keepLoaded)
{
	if (!keepLoaded && !_states.empty())
		_states.top()->unload();
	gameState->load();
	gameState->setEnable(true);
	_states.push(std::unique_ptr<AState>(gameState));
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

	while (device->run()) {
		driver->beginScene(true, true,
		irr::video::SColor(255, 100, 101, 140));
		if (!_states.empty())
			_states.top()->update();
		smgr->drawAll();
		guienv->drawAll();
		driver->endScene();
	}
	return 0;
}

AState *StateMachine::top()
{
	if (_states.empty())
		return nullptr;
	return _states.top().get();
}

void StateMachine::replaceTop(AState *gameState, bool keepLoaded)
{
	this->pop();
	this->push(gameState, keepLoaded);
}
