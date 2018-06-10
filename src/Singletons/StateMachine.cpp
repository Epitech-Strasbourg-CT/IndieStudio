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
		_states.front()->pushing(keepLoaded);
		_states.front()->setEnable(false);
	}
	if (!keepLoaded && !_states.empty())
		_states.front()->unload();
	_states.push_front(std::unique_ptr<AState>(gameState));
	gameState->setEnable(true);
	gameState->load();
	gameState->transitionPush(keepLoaded);
}

void StateMachine::pop()
{
	if (!_states.empty()) {
		auto top = _states.front().get();
		top->popping();
		top->unload();
		_states.pop_front();
	}
	if (!_states.empty()) {
		auto top = _states.front().get();
		top->setEnable(true);
		if (!top->isLoaded()) {
			top->load();
		}
		top->transitionPop();
	}
}

void StateMachine::popUntil(std::string const &state)
{
	while (!_states.empty() && _states.front()->getName() != state)
		pop();
}

void StateMachine::popAll()
{
	while (!_states.empty())
		pop();
}

int StateMachine::start()
{
	auto device = IrrManager::getInstance().getDevice();
	auto driver = IrrManager::getInstance().getDriver();
	auto smgr = IrrManager::getInstance().getSmgr();
	auto guienv = IrrManager::getInstance().getGuienv();

	while (device->run() && !_states.empty()) {
		driver->beginScene(true, true, irr::video::SColor(255, 100, 101, 140));
		if (!_states.empty())
			_states.front()->update();
		if (!_states.empty())
			_states.front()->updateRender();
		if (!_states.empty())
			_states.front()->draw();
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
	return _states.front().get();
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

bool StateMachine::isInStack(std::string const &name)
{
	for (std::unique_ptr<AState> &elem : _states) {
		if (elem->getName() == name)
			return true;
	}
	return false;
}

StateMachine::~StateMachine()
{
	popAll();
}