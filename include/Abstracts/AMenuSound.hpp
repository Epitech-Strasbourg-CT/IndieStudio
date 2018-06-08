/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** AMenuSound.hpp
*/

#ifndef BOMBERMAN_AMENUSOUND_HPP
#define BOMBERMAN_AMENUSOUND_HPP

#include <ik_ISound.h>

class AMenuSound {
public:
	AMenuSound();
	~AMenuSound();

	void playSelect();
	void playCursor();
protected:
	irrklang::ISound *_cursor;
	irrklang::ISound *_select;
};

#endif /* !BOMBERMAN_AMENUSOUND_HPP */
