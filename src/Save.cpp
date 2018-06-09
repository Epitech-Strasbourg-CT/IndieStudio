/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
**
*/

#include "../include/Save.hpp"
#include <regex>
#include <iostream>
#include <fstream>
#include <sys/stat.h>

PlayerStats::PlayerStats()
{
	std::string save_path(SAVE_PATH);
	std::ifstream mydir(SAVE_PATH);

	if (mydir.good())
		PlayerStats::getHighScore();
	else
		mkdir(save_path.c_str(), S_IRWXU | S_IRWXG | S_IROTH |
					S_IXOTH);
}

PlayerStats::~PlayerStats()
{
	PlayerStats::setHighScore();
}

void PlayerStats::PrintHighScore()
{
	std::cout << "Highscores:" << std::endl;
	for (auto &it : _PlayerData)
		std::cout << it.first << ": " << it.second << std::endl;
}

long PlayerStats::getScore(std::string PlayerName)
{
	return (_PlayerData[PlayerName]);
}

void PlayerStats::setScore(std::string PlayerName, long Score)
{
	if (_PlayerData.find(PlayerName) != _PlayerData.end())
		_PlayerData[PlayerName] = Score;
	else
		_PlayerData.insert(std::pair<std::string, long>
					(PlayerName, Score));
}

int PlayerStats::setHighScore()
{
	std::string savepath(SAVE_PATH SAVE_NAME SAVE_EXTENSION);
	std::ofstream myfile(savepath);

	for (auto &i : _PlayerData) {
		myfile << i.first << DATA_SEP << i.second << std::endl;
	}
	myfile.close();
	return (0);
}

void PlayerStats::getHighScore()
{
	std::string path(SAVE_PATH SAVE_NAME SAVE_EXTENSION);
	std::ifstream myfile(path);
	std::string line;
	std::regex reg("^(\\w+):(\\w*)$");
	std::smatch match;

	if (!myfile) {
		std::ofstream outfile(SAVE_PATH SAVE_NAME SAVE_EXTENSION);
		outfile.close();
	} else {
		while (getline(myfile, line)) {
			if (std::regex_match(line, match, reg)) {
				_PlayerData[match[1].str()] =
					strtol(match[2].str().c_str(),
					nullptr, 10);
			}
		}
		myfile.close();
	}
}
