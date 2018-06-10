/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** PathManager.cpp
*/

#ifdef _WIN32
#include <direct.h>
#define GetCurrentDir _getcwd
#elif __linux__
#include <stdio.h>
#include <unistd.h>
#define GetCurrentDir getcwd
#endif
#include<iostream>
#include "../include/PathManager.hpp"

std::string PathManager::getExecPath()
{
	char buff[FILENAME_MAX];
	GetCurrentDir( buff, FILENAME_MAX );
	std::string current_working_dir(buff);
	return current_working_dir;
}
