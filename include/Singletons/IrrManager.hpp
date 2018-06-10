/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
**
*/

#ifndef BOMBERMAN_GAMEMANAGER_HPP
#define BOMBERMAN_GAMEMANAGER_HPP

#include <irrlicht.h>
#include <memory>
#include <irrKlang.h>

class IrrManager {
public:
	static IrrManager &getInstance();
	virtual ~IrrManager();

	irr::IrrlichtDevice *getDevice() const;
	irr::video::IVideoDriver *getDriver() const;
	irr::scene::ISceneManager *getSmgr() const;
	irr::gui::IGUIEnvironment *getGuienv() const;
	irrklang::ISoundEngine *getEngine() const;
	irr::core::vector2di getSize() const;

	irrklang::ik_f32 getMasterVolume() const;
	irrklang::ik_f32 getEffectsVolume() const;
	irrklang::ik_f32 getMusicVolume() const;

	void setMasterVolume(irrklang::ik_f32);
	void setEffectsVolume(irrklang::ik_f32);
	void setMusicVolume(irrklang::ik_f32);
private:
	IrrManager();

	irr::IrrlichtDevice *_device;
	irr::video::IVideoDriver *_driver;
	irr::scene::ISceneManager *_smgr;
	irr::gui::IGUIEnvironment *_guienv;
	irrklang::ISoundEngine *_engine;
	irr::u32 _width;
	irr::u32 _height;

	irrklang::ik_f32 _master;
	irrklang::ik_f32 _effects;
	irrklang::ik_f32 _musics;

	static IrrManager _instance;
};


#endif //BOMBERMAN_GAMEMANAGER_HPP
