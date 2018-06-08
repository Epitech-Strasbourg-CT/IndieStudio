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

const std::map<AIChooseState::MenuActions, AIChooseState::BouttonsDesc>
AIChooseState::_descs{
{LAUNCH, {
	 {610, 900,  1310, 950},
	 "launch",
	 [](AIChooseState *self) {
	 	if(std::find(self->_state.begin(), self->_state.end(), 1) == self->_state.end())
			return;
	 	self->getSharedResources().setIAState(self->_state);
	 	auto &sm = StateMachine::getInstance();
	 	sm.push(new TransitionToGameState(self->getSharedResources()), false);
	 }
	 }},
{PLY1,   {
	 {350, 400, 500, 450},
	 "player",
	 [](AIChooseState *self) {
		 StateMachine::getInstance().pop();
	 }
	 }},
{PLY2,   {
	 {700, 400, 850, 450},
	 "ia",
	 [](AIChooseState *self) {
//		    StateMachine::getInstance().push(new SettingsState(self->_share), false);
	 }
	 }},
{PLY3,   {
	 {1025, 400, 1175, 450},
	 "ia",
	 [](AIChooseState *self) {

	 }
	 }},
{PLY4,   {
	 {1350, 400, 1500, 450},
	 "ia",
	 [](AIChooseState *self) {

	 }
	 }},
};

AIChooseState::AIChooseState(AStateShare &_share) : AState(_share),
_trav(dynamic_cast<irr::scene::ICameraSceneNode &>(_share.getSharedNode
("cam")), irr::core::vector3df(170, 52, -300), static_cast<irr::f32>(0.1)),
_state({1, 0, 0, 0}), _guiDisp(false)
{
	_trav.setFinalTime(60);
	_trav.setFolow(static_cast<irr::f32>(0.04));
	_trav.setEndFollow(static_cast<irr::f32>(0.04));
	_trav.setEndExactitude(5);
	_trav.setAccelEndFollow(static_cast<irr::f32>(0.01));
//	_trav.push(50, {0, 0, 0});
//	_trav.push(50, {130, 70, -500});
//	_trav.push(50, {100, 120, -400});
	_trav.push(50, {100, 40, -400});
}

void AIChooseState::load()
{
//	loadBouttons();
	AState::load();
}

void AIChooseState::update()
{
	auto &cam = dynamic_cast<irr::scene::ICameraSceneNode &>(_share.getSharedNode(
	"cam"));

	_trav.update(cam);
	if (_trav.isFinished() >= 1 && !_guiDisp) {
		loadBouttons();
		_guiDisp = true;
	}
	AState::update();
}

void AIChooseState::loadBouttons()
{
	auto gui = IrrManager::getInstance().getGuienv();
	auto &er = EventReceiver::getInstance();
	auto &ap = AssetsPool::getInstance();
//	irr::video::SColor col = gui->getSkin()->
//	col.setAlpha(255);

	for (auto &n : _descs) {
		auto b = gui->addButton(n.second.pos, nullptr, n.first);
		auto name = n.second.name;
		b->setImage(ap.loadTexture("buttons/" + name + ".png"));
		b->setPressedImage(ap.loadTexture("buttons/" + name + "_hover.png"));
		_bouttons.push_back(b);
	}

	er.registerEvent(2, irr::EEVENT_TYPE::EET_GUI_EVENT,
			 [this](const irr::SEvent &ev) {
				 auto id = static_cast<MenuActions>(ev.GUIEvent.Caller->getID());
				 if (AIChooseState::_descs.count(id) > 0)
					 this->applyEventBoutton(ev, id);
				 return true;
			 });
	for (irr::s32 i = 0; i < irr::gui::EGDC_COUNT; ++i) {
		irr::video::SColor col = gui->getSkin()->getColor((irr::gui::EGUI_DEFAULT_COLOR) i);
		col.setAlpha(50);
		gui->getSkin()->setColor((irr::gui::EGUI_DEFAULT_COLOR) i, col);
	}
}


irr::gui::IGUIButton *AIChooseState::getBoutton(MenuActions id) const
{
	if (id < LAUNCH || id > LAUNCH + 5)
		return nullptr;
	return (_bouttons.at(id - LAUNCH));
}

void AIChooseState::applyEventBoutton(const irr::SEvent &ev,
AIChooseState::MenuActions id) //TODO Coding Style
{
	auto b = getBoutton(id);
	auto hover_name = "buttons/" + std::string(((_state[id - 401] == 0) ? "ia" : "player")) + "_hover.png";
	auto name = "buttons/" + std::string(((_state[id - 401] == 0) ? "ia" : "player")) + ".png";
	auto &ap = AssetsPool::getInstance();

	switch (ev.GUIEvent.EventType) {
		case irr::gui::EGET_BUTTON_CLICKED:
			if (id == 400)
				AIChooseState::_descs.at(id).fct(this);
			else
				switchBtnState(b, id - 401);
			break;
		case irr::gui::EGET_ELEMENT_HOVERED:
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
	auto &er = EventReceiver::getInstance();
	er.unregisterEvent(2, irr::EEVENT_TYPE::EET_GUI_EVENT);
	for (auto &n : _bouttons)
		n->remove();
	_bouttons.clear();
}

void AIChooseState::unload()
{
	unloadBouttons();
	AState::unload();
}
