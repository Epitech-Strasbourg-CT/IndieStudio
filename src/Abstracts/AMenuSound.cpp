/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** AMenuSound.cpp
*/

#include "../../include/Abstracts/AMenuSound.hpp"
#include "../../include/Singletons/AssetsPool.hpp"

void AMenuSound::playSelect()
{
	AssetsPool::getInstance().loadSound(AssetsPool::SELECT, false)->setIsPaused(false);
}

void AMenuSound::playCursor()
{
	AssetsPool::getInstance().loadSound(AssetsPool::CURSOR, false)->setIsPaused(false);
}
