/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** AIChooseState.cpp
*/

#include <iostream>
#include <algorithm>
#include "../../include/States/AIChooseState.hpp"
#include "../../include/Singletons/StateMachine.hpp"
#include "../../include/Singletons/IrrManager.hpp"
#include "../../include/Singletons/EventReceiver.hpp"
#include "../../include/Singletons/AssetsPool.hpp"
#include "../../include/States/TransitionToGameState.hpp"
#include "../../include/States/MenuState.hpp"

const std::map<AIChooseState::MenuActions, AIChooseState::BouttonsDesc>
AIChooseState::_descs {
{LAUNCH, {
	 {610, 900,  1310, 950},
	 "launch",
	 [](AIChooseState *self) {
	 	self->getSharedResources().setIAState(self->_state);
	 	auto &sm = StateMachine::getInstance();
	 	sm.push(new TransitionToGameState(self->getSharedResources()), false);
	 	return true;
	 }
	 }},
{PLY1,   {
	 {350, 400, 500, 450},
	 "player",
	 [](AIChooseState *self) {
		 return true;
	 }
	 }},
{PLY2,   {
	 {700, 400, 850, 450},
	 "ia",
	 [](AIChooseState *self) {
		 return true;
	 }
	 }},
{PLY3,   {
	 {1025, 400, 1175, 450},
	 "ia",
	 [](AIChooseState *self) {
		 return true;
	 }
	 }},
{PLY4,   {
	 {1350, 400, 1500, 450},
	 "ia",
	 [](AIChooseState *self) {
		 return true;
	 }
	 }},
};

AIChooseState::AIChooseState(AStateShare &_share) : AState(_share), AMenuSound(),
_trav(static_cast<irr::scene::ICameraSceneNode &>(_share.getSharedNode("cam")), irr::core::vector3df(170, 52, -300), static_cast<irr::f32>(0.1)),
_quitAnim(static_cast<irr::scene::ICameraSceneNode &>(_share.getSharedNode("cam")), {450, 0, 100}, 0.5),
_state({1, 0, 0, 0}), _isInQuitAnim(false), _guiDisp(false), _eventsActivate(false)
{
	_trav.setFinalTime(60);
	_trav.setFolow(static_cast<irr::f32>(0.04));
	_trav.setEndFollow(static_cast<irr::f32>(0.04));
	_trav.setEndExactitude(5);
	_trav.setAccelEndFollow(static_cast<irr::f32>(0.01));
	_trav.push(50, {100, 40, -400});
	eventsSetup();
}

void AIChooseState::load()
{
	AState::load();
}

void AIChooseState::update()
{
	auto &cam = static_cast<irr::scene::ICameraSceneNode &>(_share.getSharedNode("cam"));

	if (_isInQuitAnim) {
		_quitAnim.update(cam);
		if (_quitAnim.isFinished() == 2)
			StateMachine::getInstance().pop();
		return;
	}
	if (_share.isKeyReleased(irr::KEY_ESCAPE))
		moveCamToStartPoint(cam);
	if (_trav.isFinished() != 2)
		_trav.update(cam);
	if (_trav.isFinished() >= 1 && !_guiDisp) {
		loadBouttons();
		_guiDisp = true;
	}
	AState::update();
	AssetsPool::getInstance().cleanSound();
}

void AIChooseState::loadBouttons()
{
	auto gui = IrrManager::getInstance().getGuienv();
	auto &er = EventReceiver::getInstance();
	auto &ap = AssetsPool::getInstance();

	for (auto &n : _descs) {
		auto b = gui->addButton(n.second.pos, nullptr, n.first);
		auto name = n.second.name;
		b->setImage(ap.loadTexture("buttons/" + name + ".png"));
		b->setPressedImage(ap.loadTexture("buttons/" + name + "_hover.png"));
		_bouttons.push_back(b);
	}
}


irr::gui::IGUIButton *AIChooseState::getBoutton(MenuActions id) const
{
	if (id < LAUNCH || id > LAUNCH + 5)
		return nullptr;
	return (_bouttons.at(id - LAUNCH));
}

bool AIChooseState::applyEventButton(const irr::SEvent &ev,
	AIChooseState::MenuActions id)
{
	auto b = getBoutton(id);
	std::string hover_name;
	std::string name;
	auto &ap = AssetsPool::getInstance();

	if (id > 400) {
		hover_name = "buttons/" + std::string(((_state[id - 401] == 0) ? "ia" : "player")) + "_hover.png";
		name = "buttons/" + std::string(((_state[id - 401] == 0) ? "ia" : "player")) + ".png";
	}
	switch (ev.GUIEvent.EventType) {
		case irr::gui::EGET_BUTTON_CLICKED:
			playSelect();
			if (id == 400)
				return AIChooseState::_descs.at(id).fct(this);
			switchBtnState(b, id - 401);
			break;
		case irr::gui::EGET_ELEMENT_HOVERED:
			playCursor();
			if (id == 400)
				b->setImage(ap.loadTexture("buttons/launch_hover.png"));
			else
				b->setImage(ap.loadTexture(hover_name));
			break;
		case irr::gui::EGET_ELEMENT_LEFT:
			if (id == 400)
				b->setImage(ap.loadTexture("buttons/launch.png"));
			else
				b->setImage(ap.loadTexture(name));
			break;
		default:
			break;
	}
	return true;
}

void AIChooseState::switchBtnState(irr::gui::IGUIButton *btn, int id)
{
	if (_state[id] == 0) {
		btn->setImage(AssetsPool::getInstance().loadTexture("buttons/player.png"));
		btn->setPressedImage(AssetsPool::getInstance().loadTexture("buttons/player_hover.png"));
		_state[id] = 1;
	} else {
		btn->setImage(AssetsPool::getInstance().loadTexture("buttons/ia.png"));
		btn->setPressedImage(AssetsPool::getInstance().loadTexture("buttons/ia_hover.png"));
		_state[id] = 0;
	}
}

void AIChooseState::unloadBouttons()
{
	for (auto &n : _bouttons)
		n->remove();
	_bouttons.clear();
}

void AIChooseState::unload()
{
	unloadBouttons();
	AState::unload();
}

void AIChooseState::moveCamToStartPoint(irr::scene::ICameraSceneNode &cam)
{
	_quitAnim.resetStartPoint(cam, 1);
	_quitAnim.setAccelEndFollow(0.01);
	_quitAnim.setEndExactitude(0.1);
	_quitAnim.setFixedLookPoint({450, 0, 100});
	_quitAnim.push(70, _share.getCoor("menu"));
	_share.delCoor("menu");
	_isInQuitAnim = true;
	unloadBouttons();
}

const std::string AIChooseState::getName() const
{
	return "AIChoose";
}

void AIChooseState::eventsSetup()
{
	_eventsActivate = true;
	auto &er = EventReceiver::getInstance();
	er.registerEvent(3, irr::EEVENT_TYPE::EET_GUI_EVENT,
	                 [this](const irr::SEvent &ev) {
		                 if (!this->isLoaded() || !this->isEnable()
		                 || !this->_guiDisp)
			                 return true;
		                 auto id = static_cast<MenuActions>(ev.GUIEvent.Caller->getID());
		                 if (AIChooseState::_descs.count(id) > 0)
			                 return this->applyEventButton(ev, id);
		                 return true;
	                 });
}

void AIChooseState::eventsClean()
{
	if (!_eventsActivate)
		return;
	auto &er = EventReceiver::getInstance();
	er.unregisterEvent(3, irr::EEVENT_TYPE::EET_GUI_EVENT);
	_eventsActivate = false;
}

void AIChooseState::externalEventsClean()
{
	if (!_eventsActivate)
		return;
	_eventsActivate = false;
}

AIChooseState::~AIChooseState()
{
	eventsClean();
}
