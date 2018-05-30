/*
** EPITECH PROJECT, 2018
** Project
** File description:
** Time.cpp
*/

#include <chrono>
#include "../include/Time.hpp"

size_t Time::timestamp()
{
	return static_cast<size_t>(
	std::chrono::duration_cast<std::chrono::milliseconds>
	(std::chrono::system_clock::now().time_since_epoch()).count());
}
