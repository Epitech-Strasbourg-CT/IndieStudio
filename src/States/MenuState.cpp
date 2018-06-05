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

const std::unordered_map<irr::s32, std::function<void(irr::s32, MenuState *)>>
MenuState::_assets
{{100, [](irr::s32 type, MenuState *self) {
	std::map<irr::s32, std::function<void(MenuState *)>> events = {
		{irr::gui::EGET_BUTTON_CLICKED, [](MenuState *self) {
			StateMachine::getInstance()
			.push(new GameState(self->getSharedResources()), false);
		}}, {irr::gui::EGET_ELEMENT_HOVERED, [](MenuState *self) {
			self->setButtonTexture(self->_launch, "launche2.png");
		}}, {irr::gui::EGET_ELEMENT_LEFT, [](MenuState *self) {
			self->setButtonTexture(self->_launch, "launche1.png");
	}}};
	if (events.find(type) != events.end())
			events[type](self);
}},
{101, [](irr::s32 type,MenuState *self) {
	std::map<irr::s32, std::function<void(MenuState *)>> events = {
		{irr::gui::EGET_BUTTON_CLICKED, [](MenuState *self) {
			StateMachine::getInstance().pop();
		}}, {irr::gui::EGET_ELEMENT_HOVERED, [](MenuState *self) {
			self->setButtonTexture(self->_load, "load2.png");
		}}, {irr::gui::EGET_ELEMENT_LEFT, [](MenuState *self) {
			self->setButtonTexture(self->_load, "load1.png");
	}}};
	if (events.find(type) != events.end())
			events[type](self);
}},
{102, [](irr::s32 type, MenuState *self) {
	std::map<irr::s32, std::function<void(MenuState *)>> events = {
		{irr::gui::EGET_BUTTON_CLICKED, [](MenuState *self) {
			StateMachine::getInstance().pop();
		}}, {irr::gui::EGET_ELEMENT_HOVERED, [](MenuState *self) {
			//self->setButtonTexture(self->_settings, "settings2.png");
		}}, {irr::gui::EGET_ELEMENT_LEFT, [](MenuState *self) {
			//self->setButtonTexture(self->_settings, "settings1.png");
	}}};
	if (events.find(type) != events.end())
			events[type](self);
}},
{103, [](irr::s32 type, MenuState *self) {
	std::map<irr::s32, std::function<void(MenuState *)>> events = {
		{irr::gui::EGET_BUTTON_CLICKED, [](MenuState *self) {
			StateMachine::getInstance().pop();
		}}, {irr::gui::EGET_ELEMENT_HOVERED, [](MenuState *self) {
			self->setButtonTexture(self->_exit, "exit2.png");
		}}, {irr::gui::EGET_ELEMENT_LEFT, [](MenuState *self) {
			self->setButtonTexture(self->_exit, "exit1.png");
	}}};
	if (events.find(type) != events.end())
			events[type](self);
}}};

MenuState::MenuState(AStateShare &_share) : AState(_share)
{
	 _engine = irrklang::createIrrKlangDevice();
}

MenuState::~MenuState()
{
	_engine->drop();
}

void MenuState::load()
{
	auto &gm = IrrManager::getInstance();
	auto &er = EventReceiver::getInstance();
	er.registerEvent(1, irr::EEVENT_TYPE::EET_GUI_EVENT,
	[this](const irr::SEvent &ev) {
		auto id = ev.GUIEvent.Caller->getID();
		if ((ev.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED 
		|| ev.GUIEvent.EventType == irr::gui::EGET_ELEMENT_HOVERED 
		|| ev.GUIEvent.EventType == irr::gui::EGET_ELEMENT_LEFT) &&
		MenuState::_assets.count(id) > 0)
			MenuState::_assets.at(id)(ev.GUIEvent.EventType, this);
		return true;
	});
	
	_launch = gm.getGuienv()->addButton({50, 50, 750, 100}, nullptr, 100, L"", L"Starts the game");
	_launch->setImage(AssetsPool::getInstance().loadTexture("launche1.png"));

	_load = gm.getGuienv()->addButton({50, 150, 750, 200}, nullptr, 101, L"", L"Load game");
	_load->setImage(AssetsPool::getInstance().loadTexture("load1.png"));
	_load->setPressedImage(AssetsPool::getInstance().loadTexture("load2.png"));

	_settings = gm.getGuienv()->addButton({50, 250, 750, 300}, nullptr,102, L"", L"Settings menu");

	_exit = gm.getGuienv()->addButton({50, 350, 750, 400}, nullptr, 103, L"", L"Leaves the game");
	_exit->setImage(AssetsPool::getInstance().loadTexture("exit1.png"));
	_exit->setPressedImage(AssetsPool::getInstance().loadTexture("exit2.png"));
	
	if (_engine)
    	_engine->play2D("assets/sounds/ophelia.mp3", true); // play some mp3 file, looped
	AState::load();
}


void MenuState::unload()
{
	auto &er = EventReceiver::getInstance();
	er.unregisterEvent(1, irr::EEVENT_TYPE::EET_GUI_EVENT);
	_launch->remove();
	_settings->remove();
	_exit->remove();
	std::cout << "Unload menu" << std::endl;
	AState::unload();
}

void MenuState::draw()
{
	auto &im = IrrManager::getInstance();
	im.getSmgr()->drawAll();
	im.getGuienv()->drawAll();
}

void MenuState::setButtonTexture(irr::gui::IGUIButton *button, std::string filename) {
	button->setImage(AssetsPool::getInstance().loadTexture(filename));
}