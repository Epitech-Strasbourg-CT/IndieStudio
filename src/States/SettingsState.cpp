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

const std::map<SettingsActions, SettingsState::ButtonsDesc>
	SettingsState::_descs{
	{MASTER_VOL_UP,    {
		            {700, 50,  750, 100},
		            "masterVolUp",
		            [](SettingsState *self) {
				    auto &manager = IrrManager::getInstance();
				    manager.setMasterVolume(manager.getMasterVolume() + (irrklang::ik_f32 )0.1);
		}
	            }},
	{MASTER_VOL_DOWN,    {
		            {50, 50,  100, 100},
		            "masterVolDown",
		            [](SettingsState *self) {
				    auto &manager = IrrManager::getInstance();
				    manager.setMasterVolume(manager.getMasterVolume() - (irrklang::ik_f32 )0.1);
		            }
	}},
	{MUSIC_VOL_UP,    {
			{700, 150,  750, 200},
			"musicVolDown",
			[](SettingsState *self) {
				auto &manager = IrrManager::getInstance();
				manager.setMusicVolume(manager.getMusicVolume() + (irrklang::ik_f32 )0.1);
			}
	}},
	{MUSIC_VOL_DOWN, {
			{50, 150,  100, 200},
			"musicVolDown",
			[](SettingsState *self) {
				auto &manager = IrrManager::getInstance();
				manager.setMusicVolume(manager.getMusicVolume() - (irrklang::ik_f32 )0.1);
			}
	}},
	{SFX_VOL_UP,	{
		{700, 250,  750, 300},
		"musicVolDown",
		[](SettingsState *self) {
			auto &manager = IrrManager::getInstance();
			manager.setEffectsVolume(manager.getEffectsVolume() + (irrklang::ik_f32 )0.1);
		}
	}},
	{SFX_VOL_DOWN,    {
		{50, 250,  100, 300},
		"musicVolDown",
		[](SettingsState *self) {
			auto &manager = IrrManager::getInstance();
			manager.setEffectsVolume(manager.getEffectsVolume() - (irrklang::ik_f32 )0.1);
		}
	}},
	{VOL_APPLY,    {
		{525, 500,  625, 550},
		"volApply",
		[](SettingsState *self) {
			StateMachine::getInstance().pop();
		}
	}},
	{VOL_CANCEL,    {
		{650, 500,  750, 550},
		"volCancel",
		[](SettingsState *self) {
			auto &manager = IrrManager::getInstance();

			manager.setMasterVolume(self->_master);
			manager.setMusicVolume(self->_music);
			manager.setEffectsVolume(self->_sfx);
			StateMachine::getInstance().pop();
		}
	}},
};

SettingsState::SettingsState(AStateShare &_share) : AState(_share)
{
	auto &manager = IrrManager::getInstance();

	_master = manager.getMasterVolume();
	_music = manager.getMusicVolume();
	_sfx = manager.getEffectsVolume();
}

SettingsState::~SettingsState()
{
}

void SettingsState::load()
{
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
	auto &er = EventReceiver::getInstance();
	er.unregisterEvent(1, irr::EEVENT_TYPE::EET_GUI_EVENT);
	for (auto &n : _buttons)
		n->remove();
}

void SettingsState::loadButtons()
{
	auto gui = IrrManager::getInstance().getGuienv();
	auto &er = EventReceiver::getInstance();
	auto &ap = AssetsPool::getInstance();

	for (auto &n : _descs) {
		auto b = gui->addButton(n.second.pos, nullptr, n.first);
		auto name = n.second.name;
		//b->setImage(ap.loadTexture("buttons/" + name + ".png"));
		//b->setPressedImage(ap.loadTexture("buttons/" + name + "_hover.png"));
		_buttons.push_back(b);
	}

	er.registerEvent(1, irr::EEVENT_TYPE::EET_GUI_EVENT,
	                 [this](const irr::SEvent &ev) {
		                 auto id = static_cast<SettingsActions>(ev.GUIEvent.Caller->getID());
		                 if (SettingsState::_descs.count(id) > 0)
			                 this->applyEventButton(ev, id);
		                 return true;
	                 });
}

void SettingsState::applyEventButton(const irr::SEvent &ev, SettingsActions id)
{
	auto b = getButton(id);
	//auto hover_name = "buttons/" + _descs.at(id).name + "_hover.png";
	//auto name = "buttons/" + _descs.at(id).name + ".png";
	auto &ap = AssetsPool::getInstance();

	switch (ev.GUIEvent.EventType) {
		case irr::gui::EGET_BUTTON_CLICKED:
			SettingsState::_descs.at(id).fct(this);
			break;
		default:
			break;
	}
}