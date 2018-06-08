/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** AMenuSound.cpp
*/

#include "../../include/Abstracts/AMenuSound.hpp"
#include "../../include/Singletons/AssetsPool.hpp"

AMenuSound::~AMenuSound()
{
	if (_select)
		AssetsPool::getInstance().unloadSound(AssetsPool::Assets::SELECT, _select);
	if (_cursor)
		AssetsPool::getInstance().unloadSound(AssetsPool::Assets::CURSOR, _cursor);
}

void AMenuSound::playSelect()
{
	if (_select)
		AssetsPool::getInstance().unloadSound(AssetsPool::SELECT, _select);
	_select = AssetsPool::getInstance().loadSound(AssetsPool::SELECT, false);
	_select->setIsPaused(false);
}

void AMenuSound::playCursor()
{
	if (_cursor)
		AssetsPool::getInstance().unloadSound(AssetsPool::CURSOR, _cursor);
	_cursor = AssetsPool::getInstance().loadSound(AssetsPool::CURSOR, false);
	_cursor->setIsPaused(false);
}

AMenuSound::AMenuSound()
{
	_select = nullptr;
	_cursor = nullptr;
}
