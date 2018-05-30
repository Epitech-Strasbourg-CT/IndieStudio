/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** AState.hpp
*/

#ifndef BOMBERMAN_ASTATE_HPP
#define BOMBERMAN_ASTATE_HPP


class AState {
public:

	virtual void update() = 0;
	virtual ~AState();
	bool isEnable() const;
	void setEnable(bool _enable);
	virtual void load();
	virtual void unload();
	virtual bool isLoaded() const;
protected:
	bool _enable;
	bool _loaded;
};

#endif /* !BOMBERMAN_ASTATE_HPP */
