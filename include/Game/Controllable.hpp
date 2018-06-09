/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** Controllable.hpp
*/

#pragma once

#include "AController.hpp"
#include "EntitiesMap.hpp"
#include <functional>
#include <memory>
#include <set>
#include <unordered_map>
#include <utility>
#include <iostream>

class Controllable {
public:
	explicit Controllable();
	void callBind(ControlName c, ControlType t);
	void saveController(AController *);

	protected:
	void addEvent(ControlName c, ControlType t, std::function<void()>);
	void delEvent(ControlName c, ControlType t);
	virtual void update(EntitiesMap *map);

	void dump(std::ostream &s) const;
	void load(std::istream &s);

	std::unique_ptr<AController> _controller;

	private:
	struct serialize {
	};

	std::unordered_map<ControlName, std::function<void()>>
		&_getBinds(ControlType t);
	std::set<ControlPair> _actions;
	std::unordered_map<ControlName, std::function<void()>> _bindsDown;
	std::unordered_map<ControlName, std::function<void()>> _bindsPressed;
	std::unordered_map<ControlName, std::function<void()>> _bindsReleased;
};
