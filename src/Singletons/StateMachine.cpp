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
		_states.top()->pushing(keepLoaded);
		_states.top()->setEnable(false);
	}
	if (!keepLoaded && !_states.empty())
		_states.top()->unload();
	_states.push(std::unique_ptr<AState>(gameState));
	gameState->setEnable(true);
	gameState->load();
	gameState->transitionPush(keepLoaded);
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
		driver->beginScene(true, true,
		                   irr::video::SColor(255, 100, 101, 140));
		if (!_states.empty())
			_states.top()->update();
		if (!_states.empty())
			_states.top()->updateRender();
		if (!_states.empty())
			_states.top()->draw();
		irr::core::vector3df pos = {rayon * sinf(azimuth) * sin(inc), rayon * cosf(azimuth), rayon * sinf(azimuth) * cosf(inc)};
		pos.X += 450;
		pos.Z += 100;
//		std::cout << "X: " << pos.X << " Y: " << pos.Y << " Z: " << pos.Z << std::endl;
		inc += 0.005;
//		inc = fmodf(inc, 2 * M_PI);
		cam->setPosition(pos);
		smgr->drawAll();
//		irr::core::vector3df pos = cam->getPosition();
//		if (pos.Y >= 180)
//			pos.Y -= 5;
//		if (pos.Z <= -200)
//			pos.Z += 5;
//		cam->setPosition(pos);
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

StateMachine &StateMachine::getInstance()
{
	return _instance;
}
