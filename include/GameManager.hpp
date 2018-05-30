/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
**
*/

#ifndef BOMBERMAN_GAMEMANAGER_HPP
#define BOMBERMAN_GAMEMANAGER_HPP

#include <irrlicht.h>

class GameManager {
public:
	GameManager();

	virtual ~GameManager();

	irr::IrrlichtDevice *getDevice() const;
	irr::video::IVideoDriver *getDriver() const;
	irr::scene::ISceneManager *getSmgr() const;
	irr::gui::IGUIEnvironment *getGuienv() const;
	void resetCycles();
	void upCycles();
	size_t getCycles() const;

private:
	irr::IrrlichtDevice *_device;
	irr::video::IVideoDriver *_driver;
	irr::scene::ISceneManager *_smgr;
	irr::gui::IGUIEnvironment *_guienv;
	size_t _cycles;
};


#endif //BOMBERMAN_GAMEMANAGER_HPP
