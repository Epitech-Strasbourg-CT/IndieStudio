/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** EndGameState.cpp
*/

#include "../../include/States/EndGameState.hpp"
#include "../../include/Singletons/StateMachine.hpp"
#include "../../include/Singletons/EventReceiver.hpp"
#include "../../include/States/TransitionEndGameState.hpp"

const std::map<EndGameState::Actions , EndGameState::ButtonsDesc>
	EndGameState::_descs{
	{EndGameState::RESTART,    {
		{610, 415,  1310, 465},
		"resume",
		[](EndGameState *self) {
		        }
	        }},
	{EndGameState::EXIT,  {
		{610, 515, 1310, 565},
		"exit",
		[](EndGameState *self) {
			StateMachine::getInstance().popAll();
			}
		}}
};

EndGameState::EndGameState(AStateShare &_share) : AState(_share), AMenuSound()
{
}

EndGameState::~EndGameState()
{
}

void EndGameState::loadButtons()
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
		                 if (EndGameState::_descs.count(id) > 0)
			                 this->applyEventButton(ev, id);
		                 return true;
	                 });
}

void EndGameState::unloadButtons()
{
	auto &er = EventReceiver::getInstance();
	er.unregisterEvent(1, irr::EEVENT_TYPE::EET_GUI_EVENT);
	for (auto &n : _buttons)
		n->remove();
	_buttons.clear();
}

void EndGameState::load()
{
	loadButtons();
	AState::load();
}

void EndGameState::unload()
{
	unloadButtons();
	AState::unload();
}

void EndGameState::update()
{
	AState::update();
	AssetsPool::getInstance().cleanSound();
}

void EndGameState::draw()
{
	auto &im = IrrManager::getInstance();
	im.getSmgr()->drawAll();
	im.getGuienv()->drawAll();
}

void
EndGameState::applyEventButton(const irr::SEvent &ev, EndGameState::Actions id)
{
	auto b = getButton(id);
	auto hover_name = "buttons/" + _descs.at(id).name + "_hover.png";
	auto name = "buttons/" + _descs.at(id).name + ".png";
	auto &ap = AssetsPool::getInstance();

	switch (ev.GUIEvent.EventType) {
		case irr::gui::EGET_BUTTON_CLICKED:
			playSelect();
			EndGameState::_descs.at(id).fct(this);
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

irr::gui::IGUIButton *EndGameState::getButton(EndGameState::Actions id) const
{
	if (id < RESTART || id > RESTART + ENDGAME_BUTTON_NUMBER)
		return nullptr;
	return (_buttons.at(id - RESTART));
}

const std::string EndGameState::getName() const
{
	return "endGame";
}
