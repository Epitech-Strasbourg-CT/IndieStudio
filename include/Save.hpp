/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
**
*/

#ifndef BOMBERMAN_SAVE_HPP
#define BOMBERMAN_SAVE_HPP

#include <map>

#define SAVE_PATH "../.save/"
#define SAVE_NAME "HighScores"
#define SAVE_EXTENSION ".log"

#define DATA_SEP ":"

class PlayerStats
{
public:
	PlayerStats();
	~PlayerStats();
	void setScore(std::string PlayerName, long Score);
	long getScore(std::string PlayerName);
	void PrintHighScore();
private:
	std::map<std::string, long> _PlayerData;
	void getHighScore(); /* appelée par le construc */
	int setHighScore(); /* appelée par le destruct */
};

//association d'une string à toutes les données d'un joueur,
// de base juste le score

#endif //BOMBERMAN_SAVE_HPP
