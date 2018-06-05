/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** Controllable.hpp
*/

#ifndef BOMBERMAN_CONTROLLABLE_HPP
#define BOMBERMAN_CONTROLLABLE_HPP

#include <functional>
#include <unordered_map>
#include <set>
#include <memory>
#include "AController.hpp"

class Controllable {
public:
	explicit Controllable();
	void callBind(ControlName_e c);
	void saveController(AController *);
protected:
	void addEvent(ControlName_e c, std::function<void()>);
	void delEvent(ControlName_e c);
	virtual void update();
private:
	std::set<ControlName_e> _actions;
	std::unordered_map<ControlName_e, std::function<void()>> _binds;
	std::unique_ptr<AController> _controller;
};

#endif /* !BOMBERMAN_CONTROLLABLE_HPP */
