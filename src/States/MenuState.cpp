/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
**
*/
#define _USE_MATH_DEFINES
#include <cmath>
#include "../../include/States/SettingsState.hpp"
#include <cmath>
#include "../../include/States/MenuState.hpp"
#include "../../include/Singletons/IrrManager.hpp"
#include "../../include/Singletons/StateMachine.hpp"
#include "../../include/Singletons/EventReceiver.hpp"
#include "../../include/Singletons/AssetsPool.hpp"
#include "../../include/States/GameState.hpp"
#include "../../include/States/AIChooseState.hpp"
#include "../../include/States/PauseState.hpp"
#include "../../include/States/LoadState.hpp"

const std::map<MenuActions, MenuState::ButtonsDesc>
	MenuState::_descs{
	{LAUNCH,    {
		            {610, 340,  1310, 390},
		            "launch",
		            [](MenuState *self) {
		            	auto &sm = StateMachine::getInstance();
		            	auto &res = self->getSharedResources();
		            	self->getSharedResources().addCoor("menu", self->_share.getSphereCoor("camRotateMenu")->calc());
		            	sm.push(new AIChooseState(res), false);
		            }
	            }},
	{LOAD,      {
		            {610, 440, 1310, 490},
		            "load",
		            [](MenuState *self) {
				    auto &sm = StateMachine::getInstance();
				    auto &res = self->getSharedResources();
				    sm.push(new LoadState(res), false);
		            }
	            }},
	{SETTINGS,  {
		            {610, 540, 1310, 590},
		            "settings",
		            [](MenuState *self) {
				    auto &sm = StateMachine::getInstance();
				    auto &res = self->getSharedResources();
			            sm.push(new SettingsState(res), false);
		            }
	            }},
	{EXIT_GAME, {
		            {610, 640, 1310, 690},
		            "exit",
		            [](MenuState *self) {
			            StateMachine::getInstance().popAll();
		            }
	            }},
};

MenuState::MenuState(AStateShare &_share) : AState(_share), AMenuSound()
{
	_share.pushMusic(AssetsPool::getInstance().loadSound(AssetsPool::MENU, true));
}

MenuState::~MenuState()
{
	_share.popMusic(AssetsPool::MENU);
}

void MenuState::load()
{
	loadButtons();
	AState::load();
}

void MenuState::unload()
{
	unloadButtons();
	AState::unload();
}

void MenuState::draw()
{
	auto &im = IrrManager::getInstance();
	im.getSmgr()->drawAll();
	im.getGuienv()->drawAll();
}

irr::gui::IGUIButton *MenuState::getButton(MenuActions id) const
{
	if (id < LAUNCH || id > LAUNCH + BOUTON_NUMBER)
		return nullptr;
	return (_buttons.at(id - LAUNCH));
}

void MenuState::unloadButtons()
{
	auto &er = EventReceiver::getInstance();
	er.unregisterEvent(1, irr::EEVENT_TYPE::EET_GUI_EVENT);
	for (auto &n : _buttons)
		n->remove();
	_buttons.clear();
}

void MenuState::loadButtons()
{
	auto gui = IrrManager::getInstance().getGuienv();
	auto &er = EventReceiver::getInstance();
	auto &ap = AssetsPool::getInstance();

	for (auto &n : _descs) {
		auto b = gui->addButton(n.second.pos, nullptr, n.first);
		auto name = n.second.name;
		b->setImage(ap.loadTexture("buttons/" + name + ".png"));
		b->setPressedImage(ap.loadTexture("buttons/" + name + "_hover.png"));
		_buttons.push_back(b);
	}

	er.registerEvent(1, irr::EEVENT_TYPE::EET_GUI_EVENT,
	                 [this](const irr::SEvent &ev) {
		                 auto id = static_cast<MenuActions>(ev.GUIEvent.Caller->getID());
		                 if (MenuState::_descs.count(id) > 0)
			                 this->applyEventButton(ev, id);
		                 return true;
	                 });
}

void MenuState::applyEventButton(const irr::SEvent &ev, MenuActions id)
{
	auto b = getButton(id);
	auto hover_name = "buttons/" + _descs.at(id).name + "_hover.png";
	auto name = "buttons/" + _descs.at(id).name + ".png";
	auto &ap = AssetsPool::getInstance();

	switch (ev.GUIEvent.EventType) {
		case irr::gui::EGET_BUTTON_CLICKED:
			playSelect();
			MenuState::_descs.at(id).fct(this);
			break;
		case irr::gui::EGET_ELEMENT_HOVERED:
			playCursor();
			b->setImage(ap.loadTexture(hover_name));
			break;
		case irr::gui::EGET_ELEMENT_LEFT:
			b->setImage(ap.loadTexture(name));
			break;
		default:
			break;
	}
}

void MenuState::update()
{
	_share.getFunc("rotateMenu")();
}

const std::string MenuState::getName() const
{
	return "menu";
}
