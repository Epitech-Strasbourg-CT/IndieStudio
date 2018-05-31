/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
**
*/
#include "../../include/Singletons/StateMachine.hpp"
#include "../../include/Singletons/GameManager.hpp"

StateMachine StateMachine::_instance;

void StateMachine::push(AState *gameState, bool keepLoaded)
{
	if (!keepLoaded && !_states.empty())
		_states.top()->unload();
	if (!_states.empty())
		_states.top()->setEnable(false);
	_states.push(std::unique_ptr<AState>(gameState));
	gameState->setEnable(true);
	gameState->load();
}

void StateMachine::pop(bool chainedPop)
{
	if (!_states.empty()) {
		auto top = _states.top().get();
		top->unload();
		_states.pop();
		std::cout << "pop 1" << std::endl;
	}
	if (!_states.empty()) {
		auto top = _states.top().get();
		top->setEnable(true);
		if (top->isLoaded() && chainedPop) {
			pop(chainedPop);
			std::cout << "pop 2" << std::endl;
		} else if (!top->isLoaded()) {
			std::cout << "load 1" << std::endl;
			top->load();
		}
	}
}

int StateMachine::start()
{
	auto device = GameManager::getInstance().getDevice();
	auto driver = GameManager::getInstance().getDriver();
	auto smgr = GameManager::getInstance().getSmgr();
	auto guienv = GameManager::getInstance().getGuienv();

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

void StateMachine::replaceTop(AState *gameState, bool keepLoaded, bool chainedPop)
{
	this->pop(chainedPop);
	this->push(gameState, keepLoaded);
}

StateMachine &StateMachine::getInstance()
{
	return _instance;
}
