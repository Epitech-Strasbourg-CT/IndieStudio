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

class Controllable {
public:
	explicit Controllable();
	void callBind(ControlName_e c);
	void saveController(AController *);

protected:
	void addEvent(ControlName_e c, std::function<void()>);
	void delEvent(ControlName_e c);
	virtual void update();

	void dump(std::ostream &s) const;
	void load(std::istream &s);

	struct serialize {
	};

private:
	std::set<ControlName_e> _actions;
	std::unordered_map<ControlName_e, std::function<void()>> _binds;
	std::unique_ptr<AController> _controller;
};
