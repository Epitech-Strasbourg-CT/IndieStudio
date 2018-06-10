/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** PathManager.cpp
*/

#ifdef _WIN32
#include <windows.h>
#elif __linux__
#include <stdio.h>
#include <unistd.h>
#include <sys/param.h>
#endif
#include <iostream>
#include "../include/PathManager.hpp"

std::string PathManager::getExecPath(std::string rpath)
{
	char szTmp[32];
	std::string pBuf(2048, 0);
	static std::string path;

	if (path.empty()) {
	#ifdef __linux__
		sprintf(szTmp, "/proc/%d/exe", getpid());
		MIN(readlink(szTmp, &pBuf[0], 2048), 2048 - 1);
	#elif _WIN32
		GetModuleFileName(NULL, &pBuf[0], 2048);
	#endif
		path = pBuf.substr(0, pBuf.rfind('/') + 1);
	}
	return path + rpath;
}
