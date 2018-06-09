/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
**
*/

#include "../../include/Singletons/AssetsPool.hpp"
#include "../../include/Singletons/IrrManager.hpp"
#include "../../include/Singletons/StateMachine.hpp"
#include "../../include/Singletons/EventReceiver.hpp"
#include "../../include/States/SettingsState.hpp"
#include "../../include/States/MenuState.hpp"

const std::map<SettingsActions, SettingsState::ButtonsDesc>
	SettingsState::_descs{
	{MASTER_VOL_UP,    {
		{1210, 250,  1310, 300},
		"more",
		[](SettingsState *self) {
			auto &manager = IrrManager::getInstance();
			manager.setMasterVolume(manager.getMasterVolume() +
				                        static_cast<irrklang::ik_f32 >(0.1));
			self->_masterT->setText(std::wstring(L"Master: " + std::to_wstring(
				static_cast<int>(manager.getMasterVolume() * 100.0))).c_str());
			return true;
		}
	}},
	{MASTER_VOL_DOWN,    {
		{710, 250,  810, 300},
		"less",
		[](SettingsState *self) {
			auto &manager = IrrManager::getInstance();
			manager.setMasterVolume(manager.getMasterVolume() - static_cast<irrklang::ik_f32 >(0.1));
			self->_masterT->setText(std::wstring(L"Master: " + std::to_wstring(
				static_cast<int>(manager.getMasterVolume() * 100.0))).c_str());
			return true;
		}
	}},
	{MUSIC_VOL_UP,    {
		{1210, 350,  1310, 400},
		"more",
		[](SettingsState *self) {
			auto &manager = IrrManager::getInstance();
			manager.setMusicVolume(manager.getMusicVolume() + static_cast<irrklang::ik_f32 >(0.1));
			self->_musicT->setText(std::wstring(L"Music: " + std::to_wstring(
				static_cast<int>(manager.getMusicVolume() * 100.0))).c_str());
			return true;
		}
	}},
	{MUSIC_VOL_DOWN, {
		{710, 350,  810, 400},
		"less",
		[](SettingsState *self) {
			auto &manager = IrrManager::getInstance();
			manager.setMusicVolume(manager.getMusicVolume() - static_cast<irrklang::ik_f32 >(0.1));
			self->_musicT->setText(std::wstring(L"Music: " + std::to_wstring(
				static_cast<int>(manager.getMusicVolume() * 100.0))).c_str());
			return true;
		}
	}},
	{SFX_VOL_UP,	{
		{1210, 450, 1310, 500},
		"more",
		[](SettingsState *self) {
			auto &manager = IrrManager::getInstance();
			manager.setEffectsVolume(manager.getEffectsVolume() + static_cast<irrklang::ik_f32 >(0.1));
			self->_sfxT->setText(std::wstring(L"SFX: " + std::to_wstring(
				static_cast<int>(manager.getEffectsVolume() * 100.0))).c_str());
			return true;
		}
	}},
	{SFX_VOL_DOWN,    {
		{710, 450, 810, 500},
		"less",
		[](SettingsState *self) {
			auto &manager = IrrManager::getInstance();
			manager.setEffectsVolume(manager.getEffectsVolume() - static_cast<irrklang::ik_f32 >(0.1));
			self->_sfxT->setText(std::wstring(L"SFX: " + std::to_wstring(
				static_cast<int>(manager.getEffectsVolume() * 100.0))).c_str());
			return true;
		}
	}},
	{VOL_APPLY,    {
		{1370, 850,  1520, 900},
		"validate",
		[](SettingsState *self) {
			self->externalEventsClean();
			StateMachine::getInstance().pop();
			return false;
		}
	}},
	{VOL_CANCEL,    {
		{1570, 850,  1870, 900},
		"cancel",
		[](SettingsState *self) {
			auto &manager = IrrManager::getInstance();

			manager.setMasterVolume(self->_master);
			manager.setMusicVolume(self->_music);
			manager.setEffectsVolume(self->_sfx);
			self->externalEventsClean();
			StateMachine::getInstance().pop();
			return false;
		}
	}},
};

SettingsState::SettingsState(AStateShare &_share) : AState(_share), AMenuSound()
{
	auto &manager = IrrManager::getInstance();

	_master = manager.getMasterVolume();
	_music = manager.getMusicVolume();
	_sfx = manager.getEffectsVolume();
}

SettingsState::~SettingsState()
{
	eventsClean();
}

void SettingsState::load()
{
	eventsSetup();
	loadButtons();
	AState::load();
}

void SettingsState::unload()
{
	unloadButtons();
	AState::unload();
}

void SettingsState::update()
{
	_share.getFunc("rotateMenu")();
	AssetsPool::getInstance().cleanSound();
	if (getSharedResources().isKeyPressed(irr::KEY_ESCAPE))
		StateMachine::getInstance().pop();
}

void SettingsState::draw()
{
	auto &im = IrrManager::getInstance();
	im.getSmgr()->drawAll();
	im.getGuienv()->drawAll();
}

irr::gui::IGUIButton *SettingsState::getButton(SettingsActions id) const
{
	if (id < MASTER_VOL_UP || id > MASTER_VOL_UP + SETTINGS_BOUTON_NUMBER)
		return nullptr;
	return (_buttons.at(id - MASTER_VOL_UP));
}

void SettingsState::unloadButtons()
{
	for (auto &n : _buttons)
		n->remove();
	_masterT->remove();
	_musicT->remove();
	_sfxT->remove();
}

void SettingsState::loadButtons()
{
	auto gui = IrrManager::getInstance().getGuienv();
	auto &manager = IrrManager::getInstance();
	auto &er = EventReceiver::getInstance();
	auto &ap = AssetsPool::getInstance();

	for (auto &n : _descs) {
		auto b = gui->addButton(n.second.pos, nullptr, n.first);
		auto name = n.second.name;
		b->setImage(ap.loadTexture("buttons/" + name + ".png"));
		b->setPressedImage(ap.loadTexture("buttons/" + name + "_hover.png"));
		_buttons.push_back(b);
	}
	_masterT = manager.getGuienv()->addStaticText(std::wstring(L"Master: " + std::to_wstring(
		static_cast<int>(manager.getMasterVolume() * 100.0))).c_str(), {860, 250, 1160, 300}, false,true,
	                                              nullptr, -1, true);
	_musicT = manager.getGuienv()->addStaticText(std::wstring(L"Music: " + std::to_wstring(
		static_cast<int>(manager.getMusicVolume() * 100.0))).c_str(), {860, 350, 1160, 400}, false,true,
	                                             nullptr, -1, true);
	_sfxT = manager.getGuienv()->addStaticText(std::wstring(L"SFX: " + std::to_wstring(
		static_cast<int>(manager.getEffectsVolume() * 100.0))).c_str(), {860, 450, 1160, 500}, false,true,
	                                           nullptr, -1, true);

	_masterT->setBackgroundColor({190, 127, 127, 127});
	_musicT->setBackgroundColor({190, 127, 127, 127});
	_sfxT->setBackgroundColor({190, 127, 127, 127});
	_masterT->setTextAlignment(irr::gui::EGUIA_CENTER, irr::gui::EGUIA_CENTER);
	_musicT->setTextAlignment(irr::gui::EGUIA_CENTER, irr::gui::EGUIA_CENTER);
	_sfxT->setTextAlignment(irr::gui::EGUIA_CENTER, irr::gui::EGUIA_CENTER);
	_masterT->setOverrideFont(_share.getFont());
	_musicT->setOverrideFont(_share.getFont());
	_sfxT->setOverrideFont(_share.getFont());
}

bool SettingsState::applyEventButton(const irr::SEvent &ev, SettingsActions id)
{
	auto b = getButton(id);
	auto hover_name = "buttons/" + _descs.at(id).name + "_hover.png";
	auto name = "buttons/" + _descs.at(id).name + ".png";
	auto &ap = AssetsPool::getInstance();

	switch (ev.GUIEvent.EventType) {
		case irr::gui::EGET_BUTTON_CLICKED:
			playSelect();
			return SettingsState::_descs.at(id).fct(this);
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

void SettingsState::eventsSetup()
{
	_eventsActivate = true;
	auto &er = EventReceiver::getInstance();
	er.registerEvent(2, irr::EEVENT_TYPE::EET_GUI_EVENT,
	                 [this](const irr::SEvent &ev) {
		                 if (!this->isLoaded() || !this->isEnable())
			                 return true;
		                 auto id = static_cast<SettingsActions >(ev.GUIEvent.Caller->getID());
		                 if (SettingsState::_descs.count(id) > 0)
			                 return this->applyEventButton(ev, id);
		                 return true;
	                 });
}

void SettingsState::eventsClean()
{
	if (!_eventsActivate)
		return;
	auto &er = EventReceiver::getInstance();
	er.unregisterEvent(2, irr::EEVENT_TYPE::EET_GUI_EVENT);
	_eventsActivate = false;
}

void SettingsState::externalEventsClean()
{
	if (!_eventsActivate)
		return;
	_eventsActivate = false;
}


const std::string SettingsState::getName() const
{
	return "settings";
}
