/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
**
*/
#include "../include/Singletons/StateMachine.hpp"
#include "../include/States/SplashState.hpp"
#include "../include/Singletons/IrrManager.hpp"
#include "../include/Singletons/EventReceiver.hpp"

#ifdef _WIN32
int WinMain()
#elif __linux__
int main()
#endif
{
	auto shared = AStateShare();

	srand(static_cast<unsigned int>(time(NULL)));
	shared.addSharedNode("cam", IrrManager::getInstance().getSmgr()
	->addCameraSceneNode(0, irr::core::vector3df(-80, 900, -500), irr::core::vector3df(0, 0, 0)));
	auto splash = new SplashState(shared);
	StateMachine::getInstance().push(splash, false);
	auto device = IrrManager::getInstance().getDevice();
	device->setEventReceiver(&EventReceiver::getInstance());
	auto ret = StateMachine::getInstance().start();
	shared.delSharedNode("cam");
	return ret;
}