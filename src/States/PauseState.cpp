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
		{50, 50,  750, 100},
		"resume",
		[](PauseState *self) {
			StateMachine::getInstance().pop();
		}
	}},
	{PauseState::SETTINGS,  {
		{50, 150, 750, 200},
		"settings",
		[](PauseState *self) {
			auto &sm = StateMachine::getInstance();
			auto &res = self->getSharedResources();
			sm.push(new SettingsState(res), false);
		}
	}},
	{PauseState::SAVE, {
		{50, 250, 750, 300},
		"save",
		[](PauseState *self) {
			auto &sm = StateMachine::getInstance();
			auto &res = self->getSharedResources();
			sm.push(new SaveState(res), false);
			}
	}},
	{PauseState::EXIT_GAME, {
		{50, 350, 750, 400},
		"exit",
		[](PauseState *self) {
			StateMachine::getInstance().popAll();
		}
	}}
};

PauseState::PauseState(AStateShare &_share) : AState(_share)
{
}

PauseState::~PauseState()
{
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

	er.registerEvent(1, irr::EEVENT_TYPE::EET_GUI_EVENT,
		[this](const irr::SEvent &ev) {
			auto id = static_cast<Actions>(ev.GUIEvent.Caller->getID());
			if (PauseState::_descs.count(id) > 0)
				this->applyEventButton(ev, id);
			return true;
		});
}

void PauseState::unloadButtons()
{
	auto &er = EventReceiver::getInstance();
	er.unregisterEvent(1, irr::EEVENT_TYPE::EET_GUI_EVENT);
	for (auto &n : _buttons)
		n->remove();
	_buttons.clear();
}

void PauseState::load()
{
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
}

void PauseState::draw()
{
	auto &im = IrrManager::getInstance();
	im.getSmgr()->drawAll();
	im.getGuienv()->drawAll();
}

void PauseState::applyEventButton(const irr::SEvent &ev, PauseState::Actions id)
{
	auto b = getButton(id);
	auto hover_name = "buttons/" + _descs.at(id).name + "_hover.png";
	auto name = "buttons/" + _descs.at(id).name + ".png";
	auto &ap = AssetsPool::getInstance();

	switch (ev.GUIEvent.EventType) {
		case irr::gui::EGET_BUTTON_CLICKED:
			PauseState::_descs.at(id).fct(this);
			break;
		case irr::gui::EGET_ELEMENT_HOVERED:
			b->setImage(ap.loadTexture(hover_name));
			break;
		case irr::gui::EGET_ELEMENT_LEFT:
			b->setImage(ap.loadTexture(name));
			break;
		default:
			break;
	}
}

irr::gui::IGUIButton *PauseState::getButton(PauseState::Actions id) const
{
	if (id < RESUME || id > RESUME + PAUSE_BUTTON_NUMBER)
		return nullptr;
	return (_buttons.at(id - RESUME));
}