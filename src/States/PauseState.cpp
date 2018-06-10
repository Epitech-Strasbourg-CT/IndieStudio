/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** PauseState.cpp
*/

#include "../../include/States/PauseState.hpp"
#include "../../include/Singletons/IrrManager.hpp"
#include "../../include/Singletons/EventReceiver.hpp"
#include "../../include/Singletons/AssetsPool.hpp"
#include "../../include/Singletons/StateMachine.hpp"
#include "../../include/States/SettingsState.hpp"
#include "../../include/Game/SaveManager.hpp"
#include "../../include/Time.hpp"
#include "../../include/States/SaveState.hpp"

const std::map<PauseState::Actions , PauseState::ButtonsDesc>
	PauseState::_descs{
	{PauseState::RESUME,    {
		{610, 340,  1310, 390},
		"resume",
		[](PauseState *self) {
			self->externalEventsClean();
			StateMachine::getInstance().pop();
			return true;
		}
	}},
	{PauseState::SETTINGS,  {
		{610, 440, 1310, 490},
		"settings",
		[](PauseState *self) {
			auto &sm = StateMachine::getInstance();
			auto &res = self->getSharedResources();
			sm.push(new SettingsState(res), false);
			return true;
		}
	}},
	{PauseState::SAVE, {
		{610, 540, 1310, 590},
		"save",
		[](PauseState *self) {
			auto &sm = StateMachine::getInstance();
			auto &res = self->getSharedResources();
			sm.push(new SaveState(res), false);
			return true;
			}
	}},
	{PauseState::EXIT_GAME, {
		{610, 640, 1310, 690},
		"exit",
		[](PauseState *self) {
			self->externalEventsClean();
			StateMachine::getInstance().popAll();
			return false;
		}
	}}
};

PauseState::PauseState(AStateShare &_share) : AState(_share), AMenuSound()
{
}

PauseState::~PauseState()
{
	eventsClean();
}

void PauseState::loadButtons()
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
}

void PauseState::unloadButtons()
{
	for (auto &n : _buttons)
		n->remove();
	_buttons.clear();
}

void PauseState::load()
{
	eventsSetup();
	loadButtons();
	AState::load();
}

void PauseState::unload()
{
	unloadButtons();
	AState::unload();
}

void PauseState::update()
{
	if (getSharedResources().isKeyPressed(irr::KEY_ESCAPE))
		StateMachine::getInstance().pop();
	AState::update();
	AssetsPool::getInstance().cleanSound();
}

void PauseState::draw()
{
	auto &im = IrrManager::getInstance();
	im.getSmgr()->drawAll();
	im.getGuienv()->drawAll();
}

bool PauseState::applyEventButton(const irr::SEvent &ev, PauseState::Actions id)
{
	auto b = getButton(id);
	auto hover_name = "buttons/" + _descs.at(id).name + "_hover.png";
	auto name = "buttons/" + _descs.at(id).name + ".png";
	auto &ap = AssetsPool::getInstance();

	switch (ev.GUIEvent.EventType) {
		case irr::gui::EGET_BUTTON_CLICKED:
			playSelect();
			return PauseState::_descs.at(id).fct(this);
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
	return true;
}

irr::gui::IGUIButton *PauseState::getButton(PauseState::Actions id) const
{
	if (id < RESUME || id > RESUME + PAUSE_BUTTON_NUMBER)
		return nullptr;
	return (_buttons.at(id - RESUME));
}

const std::string PauseState::getName() const
{
	return "pause";
}

void PauseState::eventsSetup()
{
	_eventsActivate = true;
	auto &er = EventReceiver::getInstance();
	er.registerEvent(10, irr::EEVENT_TYPE::EET_GUI_EVENT,
			 [this](const irr::SEvent &ev) {
				 if (!this->isLoaded() || !this->isEnable())
					 return true;
				 auto id = static_cast<Actions>(ev.GUIEvent.Caller->getID());
				 if (PauseState::_descs.count(id) > 0)
					 return this->applyEventButton(ev, id);
				 return true;
			 });
}

void PauseState::eventsClean()
{
	if (!_eventsActivate)
		return;
	auto &er = EventReceiver::getInstance();
	er.unregisterEvent(10, irr::EEVENT_TYPE::EET_GUI_EVENT);
	_eventsActivate = false;
}

void PauseState::externalEventsClean()
{
	if (!_eventsActivate)
		return;
	_eventsActivate = false;
}
