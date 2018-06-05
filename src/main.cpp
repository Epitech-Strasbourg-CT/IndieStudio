/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
**
*/
// #include "../include/Singletons/StateMachine.hpp"
// #include "../include/States/SplashState.hpp"
// #include "../include/Singletons/IrrManager.hpp"
// #include "../include/Singletons/EventReceiver.hpp"

// int main()
// {
// 	auto shared = AStateShare();
// 	auto splash = new SplashState(shared);
// 	StateMachine::getInstance().push(splash, false);
// 	auto device = IrrManager::getInstance().getDevice();
// 	device->setEventReceiver(&EventReceiver::getInstance());
// 	return StateMachine::getInstance().start();
// }

#include <iostream>
#include <irrKlang.h>
#include "../include/Game/SaveManager.hpp"
#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll

int main(int argc, const char **argv)
{
	// SaveManager sm;
	// EntitiesMap sixsixdouzedouze;
	// AEntity bite;
	// AEntity teub;
	// sixsixdouzedouze.insert(bite);
	// sixsixdouzedouze.insert(teub);
	// for (auto *n : sixsixdouzedouze.getList())
	// 	std::cout << *n;
	// sm.save(sixsixdouzedouze, "test.save");

	// SaveManager sm2;
	// EntitiesMap sixsixdouzedouze2;
	// sm.load(sixsixdouzedouze2, "test.save");
	// std::cout << std::endl;
	// std::cout << std::endl;
	// for (auto *n : sixsixdouzedouze2.getList())
	// 	std::cout << *n;
	
	irrklang::ISoundEngine *engine = irrklang::createIrrKlangDevice();
	if (!engine)
		return 1; // could not start engine

	engine->play2D("assets/sounds/ophelia.mp3",
		true); // play some mp3 file, looped

	std::cin.get(); // wait until user presses a key

	engine->drop(); // delete engine
	return 0;
}
