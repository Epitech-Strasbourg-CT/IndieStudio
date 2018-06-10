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
#include <sys/stat.h>
#include <sys/param.h>
#include <pwd.h>
#endif
#include <iostream>
#include <algorithm>
#include "../include/PathManager.hpp"

std::string PathManager::getExecPath(std::string rpath)
{
	std::string pBuf(2048, 0);
	static std::string path;

	if (path.empty()) {
	#ifdef __linux__
		char szTmp[32];
		sprintf(szTmp, "/proc/%d/exe", getpid());
		MIN(readlink(szTmp, &pBuf[0], 2048), 2048 - 1);
		path = pBuf.substr(0, pBuf.rfind('/') + 1);
	#elif _WIN32
		GetModuleFileName(NULL, &pBuf[0], 2048);
		HMODULE hModule = GetModuleHandleW(NULL);
		WCHAR buff[MAX_PATH];
		GetModuleFileNameW(hModule, buff, MAX_PATH);
		std::wstring ws(buff);
		pBuf = std::string(ws.begin(), ws.end());
		path = pBuf.substr(0, pBuf.rfind("\\") + 1);

	#endif
	}
	#ifdef _WIN32
		std::replace(rpath.begin(), rpath.end(), '/', '\\');
	#endif
	return path + rpath;
}

std::string PathManager::getHomePath(std::string rpath)
{
	static std::string path;

	if (path.empty()) {
		#ifdef __linux__
		const char *homedir;
		homedir = getenv("HOME");
		if (!homedir)
			homedir = getpwuid(getuid())->pw_dir;
		path = std::string(homedir) + "/.bomberman/";
		mkdir(path.c_str(), 0733);
		#elif _WIN32
		WCHAR profilePath[MAX_PATH];
		HRESULT result = SHGetFolderPathW(NULL, CSIDL_PROFILE, NULL, 0, profilePath);
		std::wstring ws(buff);
		pBuf = std::string(ws.begin(), ws.end());

		if (SUCCEEDED(result)) {
			path = std::string(profilePath) + "\\.bomberman\\";
		   	CreateDirectory(path.c_str(), nullptr);
		}
		#endif
	}
	#ifdef _WIN32
	std::replace(rpath.begin(), rpath.end(), '/', '\\');
	#endif
	return path + rpath;
}
