/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
**
*/
#include "../../include/Singletons/StateMachine.hpp"
#include "../../include/Singletons/IrrManager.hpp"

StateMachine StateMachine::_instance;

void StateMachine::push(AState *gameState, bool keepLoaded)
{
	if (!_states.empty()) {
		_states.top()->pushing();
		_states.top()->setEnable(false);
	}
	if (!keepLoaded && !_states.empty())
		_states.top()->unload();
	_states.push(std::unique_ptr<AState>(gameState));
	gameState->setEnable(true);
	gameState->load();
	gameState->transitionPush();
}

void StateMachine::pop()
{
	if (!_states.empty()) {
		auto top = _states.top().get();
		top->popping();
		top->unload();
		_states.pop();
	}
	if (!_states.empty()) {
		auto top = _states.top().get();
		top->setEnable(true);
		if (!top->isLoaded()) {
			top->load();
		}
		top->transitionPop();
	}
}

int StateMachine::start()
{
	auto device = IrrManager::getInstance().getDevice();
	auto driver = IrrManager::getInstance().getDriver();

	while (device->run()) {
		driver->beginScene(true, true,
		irr::video::SColor(255, 100, 101, 140));
		if (!_states.empty())
			_states.top()->update();
		if (!_states.empty())
			_states.top()->updateRender();
		if (!_states.empty())
			_states.top()->draw();
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

StateMachine &StateMachine::getInstance()
{
	return _instance;
}
