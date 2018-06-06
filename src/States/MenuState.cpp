/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
**
*/

#include <cmath>
#include "../../include/States/MenuState.hpp"
#include "../../include/Singletons/IrrManager.hpp"
#include "../../include/Singletons/StateMachine.hpp"
#include "../../include/Singletons/EventReceiver.hpp"
#include "../../include/Singletons/AssetsPool.hpp"
#include "../../include/States/GameState.hpp"
#include "../../include/States/AIChooseState.hpp"

const std::unordered_map<irr::s32, std::function<void(irr::s32, MenuState *)>>
MenuState::_assets
{{100, [](irr::s32 type, MenuState *self) {
	std::map<irr::s32, std::function<void(MenuState *)>> events = {
		{irr::gui::EGET_BUTTON_CLICKED, [](MenuState *self) {
			StateMachine::getInstance().push(
				new AIChooseState(self->getSharedResources()),
				false
			);
//			StateMachine::getInstance()
//			.push(new GameState(self->getSharedResources()), false);
		}}, {irr::gui::EGET_ELEMENT_HOVERED, [](MenuState *self) {
			self->setButtonTexture(self->getLaunch(), "menu/launch2.png");
		}}, {irr::gui::EGET_ELEMENT_LEFT, [](MenuState *self) {
			self->setButtonTexture(self->getLaunch(), "menu/launch1.png");
	}}};
	if (events.find(type) != events.end())
			events[type](self);
}},
{101, [](irr::s32 type,MenuState *self) {
	std::map<irr::s32, std::function<void(MenuState *)>> events = {
		{irr::gui::EGET_BUTTON_CLICKED, [](MenuState *self) {
			StateMachine::getInstance().pop();
		}}, {irr::gui::EGET_ELEMENT_HOVERED, [](MenuState *self) {
			self->setButtonTexture(self->getLoad(), "menu/load2.png");
		}}, {irr::gui::EGET_ELEMENT_LEFT, [](MenuState *self) {
			self->setButtonTexture(self->getLoad(), "menu/load1.png");
	}}};
	if (events.find(type) != events.end())
			events[type](self);
}},
{102, [](irr::s32 type, MenuState *self) {
	std::map<irr::s32, std::function<void(MenuState *)>> events = {
		{irr::gui::EGET_BUTTON_CLICKED, [](MenuState *self) {
			StateMachine::getInstance().pop();
		}}, {irr::gui::EGET_ELEMENT_HOVERED, [](MenuState *self) {
			//self->setButtonTexture(self->_settings, "menu/settings2.png");
		}}, {irr::gui::EGET_ELEMENT_LEFT, [](MenuState *self) {
			//self->setButtonTexture(self->_settings, "menu/settings1.png");
	}}};
	if (events.find(type) != events.end())
			events[type](self);
}},
{103, [](irr::s32 type, MenuState *self) {
	std::map<irr::s32, std::function<void(MenuState *)>> events = {
		{irr::gui::EGET_BUTTON_CLICKED, [](MenuState *self) {
			StateMachine::getInstance().popAll();
		}}, {irr::gui::EGET_ELEMENT_HOVERED, [](MenuState *self) {
			self->setButtonTexture(self->getExit(), "menu/exit2.png");
		}}, {irr::gui::EGET_ELEMENT_LEFT, [](MenuState *self) {
			self->setButtonTexture(self->getExit(), "menu/exit1.png");
	}}};
	if (events.find(type) != events.end())
			events[type](self);
}}};

MenuState::MenuState(AStateShare &_share) : AState(_share),
_camRotate(2.3, static_cast<irr::f32>(3.14159265 / 3.0), 700, {450, 0, 100}),
_rotate(1)
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
	_launch->setImage(AssetsPool::getInstance().loadTexture("menu/launche1.png"));
	_launch->setPressedImage(AssetsPool::getInstance().loadTexture("menu/launch2.png"));

	_load = gm.getGuienv()->addButton({50, 150, 750, 200}, nullptr, 101, L"", L"Load game");
	_load->setImage(AssetsPool::getInstance().loadTexture("menu/load1.png"));
	_load->setPressedImage(AssetsPool::getInstance().loadTexture("menu/load2.png"));

	_settings = gm.getGuienv()->addButton({50, 250, 750, 300}, nullptr,102, L"", L"Settings menu");

	_exit = gm.getGuienv()->addButton({50, 350, 750, 400}, nullptr, 103, L"", L"Leaves the game");
	_exit->setImage(AssetsPool::getInstance().loadTexture("menu/exit1.png"));
	_exit->setPressedImage(AssetsPool::getInstance().loadTexture("menu/exit2.png"));
	
//	if (_engine)
//    		_engine->play2D("assets/sounds/ophelia.mp3", true); // play some mp3 file, looped
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

irr::gui::IGUIButton *MenuState::getLaunch() const
{
	return _launch;
}

irr::gui::IGUIButton *MenuState::getLoad() const
{
	return _load;
}

irr::gui::IGUIButton *MenuState::getSettings() const
{
	return _settings;
}

irr::gui::IGUIButton *MenuState::getExit() const
{
	return _exit;
}

#define TAU (2.0 * M_PI)
#define STEP (TAU / 2000.0)

void MenuState::update()
{
	irr::f32 min = 2.7;
	irr::f32 max = 4.4;
	static irr::f32 inc = 0;
	auto &cam = dynamic_cast<irr::scene::ICameraSceneNode &>(_share.getSharedNode("cam"));

	cam.setTarget({450, 0, 100});
//	2.3 < x < 4.1

	inc += STEP;
//	inc = fmodf(inc, TAU);
	std::cout << sinf(inc) << " " << _camRotate.getInc() << std::endl;
	_camRotate.setInc((sinf(inc) - -1.0) * (max - min) / (1.0 - -1.0) + min);
	cam.setPosition(_camRotate.calc());
}
