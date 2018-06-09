/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** SaveState.cpp
*/

#include "../../include/States/SaveState.hpp"
#include "../../include/Singletons/StateMachine.hpp"
#include "../../include/States/SettingsState.hpp"
#include "../../include/Singletons/IrrManager.hpp"
#include "../../include/Singletons/EventReceiver.hpp"
#include "../../include/Singletons/AssetsPool.hpp"
#include "../../include/Game/SaveManager.hpp"

const std::map<SaveState::Actions , SaveState::ButtonsDesc>
	SaveState::_descs{
	{SaveState::CANCEL, {
		{985, 590,  1285, 640},
		"cancel",
		[](SaveState *self) {
			self->externalEventsClean();
			StateMachine::getInstance().pop();
			return false;
		}
	}},
	{SaveState::SAVE,  {
		{635, 590,  935, 640},
		"save",
		[](SaveState *self) {
			self->externalEventsClean();
			SaveManager sm;
			std::wstring wstr(self->_name->getText());
			std::string str(wstr.begin(), wstr.end());
			std::string final(".save/" + str + ".dat");
			sm.save(*self->_share.getMap(), final);
			StateMachine::getInstance().pop();
			return false;
		}
	}}
};

SaveState::SaveState(AStateShare &_share) : AState(_share), AMenuSound()
{
}

SaveState::~SaveState()
{
	eventsClean();
}

void SaveState::loadButtons()
{
	//FIXME Norme
	auto gui = IrrManager::getInstance().getGuienv();
	auto &er = EventReceiver::getInstance();
	auto &ap = AssetsPool::getInstance();

	std::time_t t = std::time(0);
	auto tm = localtime(&t);

	std::string sName = std::to_string(tm->tm_year + 1900)
		+ std::to_string(tm->tm_mon)
		+ std::to_string(tm->tm_mday)
		+ "_" + std::to_string(tm->tm_hour)
		+ ":" + std::to_string(tm->tm_min)
		+ ":" + std::to_string(tm->tm_sec);

	for (auto &n : _descs) {
		auto b = gui->addButton(n.second.pos, nullptr, n.first);
		auto name = n.second.name;
		b->setImage(ap.loadTexture("buttons/" + name + ".png"));
		b->setPressedImage(ap.loadTexture("buttons/" + name + "_hover.png"));
		_buttons.push_back(b);
	}

	std::wstring wname(sName.begin(), sName.end());
	_name = gui->addButton({610, 465, 1310, 515}, nullptr,
		600 + SAVE_BUTTON_NUMBER, wname.c_str());
	_name->setOverrideFont(_share.getFont());
	_name->setImage(ap.loadTexture("buttons/default.png"));
	_name->setEnabled(false);
}

void SaveState::unloadButtons()
{
	for (auto &n : _buttons)
		n->remove();
	_buttons.clear();
	_name->remove();
}

void SaveState::load()
{
	eventsSetup();
	loadButtons();
	AState::load();
}

void SaveState::unload()
{
	unloadButtons();
	AState::unload();
}

void SaveState::update()
{
	if (getSharedResources().isKeyPressed(irr::KEY_ESCAPE))
		StateMachine::getInstance().pop();
	AState::update();
	AssetsPool::getInstance().cleanSound();
}

void SaveState::draw()
{
	auto &im = IrrManager::getInstance();
	im.getSmgr()->drawAll();
	im.getGuienv()->drawAll();
}

bool SaveState::applyEventButton(const irr::SEvent &ev, SaveState::Actions id)
{
	auto b = getButton(id);
	auto hover_name = "buttons/" + _descs.at(id).name + "_hover.png";
	auto name = "buttons/" + _descs.at(id).name + ".png";
	auto &ap = AssetsPool::getInstance();

	switch (ev.GUIEvent.EventType) {
		case irr::gui::EGET_BUTTON_CLICKED:
			playSelect();
			return SaveState::_descs.at(id).fct(this);
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

irr::gui::IGUIButton *SaveState::getButton(SaveState::Actions id) const
{
	if (id < SAVE || id > SAVE + SAVE_BUTTON_NUMBER)
		return nullptr;
	return (_buttons.at(id - SAVE));
}

const std::string SaveState::getName() const
{
	return "save";
}

void SaveState::eventsSetup()
{
	_eventsActivate = true;
	auto &er = EventReceiver::getInstance();
	er.registerEvent(11, irr::EEVENT_TYPE::EET_GUI_EVENT,
			 [this](const irr::SEvent &ev) {
				 if (!this->isLoaded() || !this->isEnable())
					 return true;
				 auto id = static_cast<Actions>(ev.GUIEvent.Caller->getID());
				 if (SaveState::_descs.count(id) > 0)
					 return this->applyEventButton(ev, id);
				 return true;
			 });
}

void SaveState::eventsClean()
{
	if (!_eventsActivate)
		return;
	auto &er = EventReceiver::getInstance();
	er.unregisterEvent(11, irr::EEVENT_TYPE::EET_GUI_EVENT);
	_eventsActivate = false;
}

void SaveState::externalEventsClean()
{
	if (!_eventsActivate)
		return;
	_eventsActivate = false;
}
