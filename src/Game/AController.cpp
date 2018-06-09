/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** AController.cpp
*/

#include "../../include/Game/Controllable.hpp"

AController::~AController()
{
}

void AController::registerControllable(Controllable *controllable)
{
	_controllable = controllable;

}

void AController::updateInputs(EntitiesMap *)
{

}

void AController::bindEntityToController(AController &con, Controllable &ent)
{
	con.registerControllable(&ent);
	ent.saveController(&con);
}
