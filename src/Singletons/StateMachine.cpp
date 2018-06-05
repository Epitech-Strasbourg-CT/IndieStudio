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

//	smgr->addCameraSceneNode(0, irr::core::vector3df(0,30,-40),
//				 irr::core::vector3df(0,5, 0));

	irr::SKeyMap keyMap[5];
	keyMap[0].Action = irr::EKA_MOVE_FORWARD;
	keyMap[0].KeyCode = irr::KEY_KEY_Z;
	keyMap[1].Action = irr::EKA_MOVE_BACKWARD;
	keyMap[1].KeyCode = irr::KEY_KEY_S;
	keyMap[2].Action = irr::EKA_STRAFE_LEFT;
	keyMap[2].KeyCode = irr::KEY_KEY_Q;
	keyMap[3].Action = irr::EKA_STRAFE_RIGHT;
	keyMap[3].KeyCode = irr::KEY_KEY_D;
	keyMap[4].Action = irr::EKA_JUMP_UP;
	keyMap[4].KeyCode = irr::KEY_SPACE;

	#define PI 3.14159265

	auto cam = smgr->addCameraSceneNode(0, irr::core::vector3df(-80, 900, -500),
	irr::core::vector3df(450, 0, 100));
//	irr::core::vector3df(-80, 0, -150)); //TODO Refacto camera usage

	irr::f32 rayon = 1000;
	irr::f32 inc = 0;
	irr::f32 azimuth = PI / 3;

//	smgr->addCameraSceneNodeFPS(0, 100.0f, 0.1f, -1, keyMap, 5)
//		->setPosition(irr::core::vector3df(-80, 50, -250));
//	device->getCursorControl()->setVisible(false);
	while (device->run()) {
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
