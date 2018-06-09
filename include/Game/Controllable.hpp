/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** Controllable.hpp
*/

#pragma once

#include "AController.hpp"
#include <functional>
#include <memory>
#include <set>
#include <unordered_map>
#include <utility>

class Controllable {
public:
	explicit Controllable();
	void callBind(ControlName c, ControlType t);
	void saveController(AController *);

protected:
	void addEvent(ControlName c, ControlType t, std::function<void()>);
	void delEvent(ControlName c, ControlType t);
	virtual void update();

	void dump(std::ostream &s) const;
	void load(std::istream &s);

	struct serialize {
	};

private:
	std::unordered_map<ControlName, std::function<void()>>
		&_getBinds(ControlType t);
	std::set<ControlPair> _actions;
	std::unordered_map<ControlName, std::function<void()>> _bindsDown;
	std::unordered_map<ControlName, std::function<void()>> _bindsPressed;
	std::unordered_map<ControlName, std::function<void()>> _bindsReleased;
	std::unique_ptr<AController> _controller;
};
