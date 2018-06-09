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

const std::map<SaveState::Actions , SaveState::ButtonsDesc>
	SaveState::_descs{
	{SaveState::CANCEL, {
		{985, 590,  1285, 640},
		"cancel",
		[](SaveState *self) {
			StateMachine::getInstance().pop();
		}
	}},
	{SaveState::SAVE,  {
		{635, 590,  935, 640},
		"save",
		[](SaveState *self) {
			StateMachine::getInstance().pop();
		}
	}}
};

SaveState::SaveState(AStateShare &_share) : AState(_share), AMenuSound()
{
}

SaveState::~SaveState()
{
}

void SaveState::loadButtons()
{
	//FIXME Norme
	auto gui = IrrManager::getInstance().getGuienv();
	auto &er = EventReceiver::getInstance();
	auto &ap = AssetsPool::getInstance();
	std::time_t t = std::time(0);
	auto *tm = localtime(&t);
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

	er.registerEvent(1, irr::EEVENT_TYPE::EET_GUI_EVENT,
		[this](const irr::SEvent &ev) {
			auto id = static_cast<Actions>(ev.GUIEvent.Caller->getID());
			if (SaveState::_descs.count(id) > 0)
				this->applyEventButton(ev, id);
			return true;
		});
	_name = gui->addEditBox(std::wstring(sName.begin(),
		sName.end()).c_str(), {835, 440, 1085, 540},
		true, nullptr, 600 + SAVE_BUTTON_NUMBER);
	_name->setTextAlignment(irr::gui::EGUIA_CENTER, irr::gui::EGUIA_CENTER);
}

void SaveState::unloadButtons()
{
	auto &er = EventReceiver::getInstance();
	er.unregisterEvent(1, irr::EEVENT_TYPE::EET_GUI_EVENT);
	for (auto &n : _buttons)
		n->remove();
	_buttons.clear();
	//std::cout << "Name :" << _name->getText() << std::endl;
	_name->remove();
}

void SaveState::load()
{
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
	if (getSharedResources().isKeyReleased(irr::KEY_ESCAPE))
		StateMachine::getInstance().pop();
	AState::update();
}

void SaveState::draw()
{
	auto &im = IrrManager::getInstance();
	im.getSmgr()->drawAll();
	im.getGuienv()->drawAll();
}

void SaveState::applyEventButton(const irr::SEvent &ev, SaveState::Actions id)
{
	auto b = getButton(id);
	auto hover_name = "buttons/" + _descs.at(id).name + "_hover.png";
	auto name = "buttons/" + _descs.at(id).name + ".png";
	auto &ap = AssetsPool::getInstance();

	switch (ev.GUIEvent.EventType) {
		case irr::gui::EGET_BUTTON_CLICKED:
			playSelect();
			SaveState::_descs.at(id).fct(this);
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
