/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
**
*/

#include "../../include/States/MenuState.hpp"
#include "../../include/Singletons/IrrManager.hpp"
#include "../../include/Singletons/StateMachine.hpp"
#include "../../include/Singletons/EventReceiver.hpp"
#include "../../include/Singletons/AssetsPool.hpp"
#include "../../include/States/GameState.hpp"

const std::map<MenuActions, MenuState::BouttonsDesc>
	MenuState::_descs{
	{LAUNCH,    {
		            {50, 50,  750, 100},
		            "launch",
		            [](MenuState *self) {
		            	auto &sm = StateMachine::getInstance();
		            	auto &res = self->getSharedResources();
		            	sm.push(new GameState(res), false);
		            }
	            }},
	{LOAD,      {
		            {50, 150, 750, 200},
		            "load",
		            [](MenuState *self) {
			            StateMachine::getInstance().pop();
		            }
	            }},
	{SETTINGS,  {
		            {50, 250, 750, 300},
		            "settings",
		            [](MenuState *self) {
			            StateMachine::getInstance().pop();
		            }
	            }},
	{EXIT_GAME, {
		            {50, 350, 750, 400},
		            "exit",
		            [](MenuState *self) {
			            StateMachine::getInstance().popAll();
		            }
	            }},
};

MenuState::MenuState(AStateShare &_share) : AState(_share), _sound()
{
}

MenuState::~MenuState()
{
}

void MenuState::load()
{
	loadBouttons();
	auto engine = IrrManager::getInstance().getEngine();
	if (IrrManager::getInstance().getEngine())
		_sound =
			engine->play2D("assets/sounds/ophelia.mp3", false, false, true);
	AState::load();
}

void MenuState::unload()
{
	unloadBouttons();
	if (_sound) {
		_sound->stop();
		_sound->drop();
	}
	AState::unload();
}

void MenuState::draw()
{
	auto &im = IrrManager::getInstance();
	im.getSmgr()->drawAll();
	im.getGuienv()->drawAll();
}

irr::gui::IGUIButton *MenuState::getBoutton(MenuActions id) const
{
	if (id < LAUNCH || id > LAUNCH + BOUTON_NUMBER)
		return nullptr;
	return (_bouttons.at(id - LAUNCH));
}

void MenuState::unloadBouttons()
{
	auto &er = EventReceiver::getInstance();
	er.unregisterEvent(1, irr::EEVENT_TYPE::EET_GUI_EVENT);
	for (auto &n : _bouttons)
		n->remove();
}

void MenuState::loadBouttons()
{
	auto gui = IrrManager::getInstance().getGuienv();
	auto &er = EventReceiver::getInstance();
	auto &ap = AssetsPool::getInstance();

	for (auto &n : _descs) {
		auto b = gui->addButton(n.second.pos, nullptr, n.first);
		auto name = n.second.name;
		b->setImage(ap.loadTexture("bouttons/" + name + ".png"));
		b->setPressedImage(ap.loadTexture("bouttons/" + name + "_hover.png"));
		_bouttons.push_back(b);
	}

	er.registerEvent(1, irr::EEVENT_TYPE::EET_GUI_EVENT,
	                 [this](const irr::SEvent &ev) {
		                 auto id = static_cast<MenuActions>(ev.GUIEvent.Caller->getID());
		                 if (MenuState::_descs.count(id) > 0)
			                 this->applyEventBoutton(ev, id);
		                 return true;
	                 });
}

void MenuState::applyEventBoutton(const irr::SEvent &ev, MenuActions id)
{
	auto b = getBoutton(id);
	auto hover_name = "bouttons/" + _descs.at(id).name + "_hover.png";
	auto name = "bouttons/" + _descs.at(id).name + ".png";
	auto &ap = AssetsPool::getInstance();

	switch (ev.GUIEvent.EventType) {
		case irr::gui::EGET_BUTTON_CLICKED:
			MenuState::_descs.at(id).fct(this);
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
