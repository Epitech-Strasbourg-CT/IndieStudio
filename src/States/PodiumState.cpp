/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** PodiumState.cpp
*/

#include "../../include/States/PodiumState.hpp"
#include "../../include/Singletons/StateMachine.hpp"
#include "../../include/States/TransitionEndGameState.hpp"
#include "../../include/Singletons/EventReceiver.hpp"
#include "../../include/States/MenuState.hpp"
#include "../../include/States/TransitionToMenuState.hpp"

const std::map<PodiumState::MenuActions, PodiumState::ButtonsDesc>
PodiumState::_descs{
{PodiumState::RESTART, {
{610, 200, 1310, 250},
"back",
[](PodiumState *self) {
	self->unloadDeadPlayer();
	auto &share = self->getSharedResources();
	StateMachine::getInstance().push(new TransitionToMenuState(share), false);
	return true;
}
}},
{PodiumState::QUIT, {
{610, 300, 1310, 350},
"exit",
[](PodiumState *self) {
	auto &sm = StateMachine::getInstance();
	auto &res = self->getSharedResources();
	sm.push(new TransitionEndGameState(res), false);
	return true;
}
}}
};

PodiumState::PodiumState(AStateShare &_share) : AState(_share),
_trav(dynamic_cast<irr::scene::ICameraSceneNode &>(_share.getSharedNode("cam")), {675, 70, 640}, 1),
_isLoad(false)
{
	_trav.setFolow(0.01);
	_trav.setEndExactitude(0.1);
	_trav.push(50, {675, 80, 655});
}

void PodiumState::update()
{
	if (_trav.isFinished() >= 1 && !_isLoad) {
		_isLoad = true;
		loadText();
		eventsSetup();
		loadButtons();
	}
	_trav.update(dynamic_cast<irr::scene::ICameraSceneNode &>(_share.getSharedNode("cam")));
	AState::update();
}

const std::string PodiumState::getName() const
{
	return "podium";
}

void PodiumState::loadText()
{
	for (auto i = 0; i < 4; i++) {
		std::wstring str = std::to_wstring(4 - i) + ((i == 3) ? L" er" : L" eme");
		auto text = IrrManager::getInstance().getSmgr()->addTextSceneNode(_share.getFont(), str.c_str());
		text->setPosition({static_cast<irr::f32>(685 + i * -6), 65, 645});
		_text.push_back(text);
	}
}

void PodiumState::loadButtons()
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

void PodiumState::eventsSetup()
{
	auto &er = EventReceiver::getInstance();
	er.registerEvent(1, irr::EEVENT_TYPE::EET_GUI_EVENT,
			 [this](const irr::SEvent &ev) {
				 if (!this->isLoaded() || !this->isEnable())
					 return true;
				 auto id = static_cast<MenuActions>(ev.GUIEvent.Caller->getID());
				 if (PodiumState::_descs.count(id) > 0)
					 return this->applyEventButton(ev, id);
				 return true;
			 });
}

irr::gui::IGUIButton *PodiumState::getButton(MenuActions id) const
{
	if (id < RESTART || id > RESTART + 2)
		return nullptr;
	return (_buttons.at(id - RESTART));
}

bool PodiumState::applyEventButton(const irr::SEvent &ev, MenuActions id)
{
	auto b = getButton(id);
	auto hover_name = "buttons/" + _descs.at(id).name + "_hover.png";
	auto name = "buttons/" + _descs.at(id).name + ".png";
	auto &ap = AssetsPool::getInstance();

	switch (ev.GUIEvent.EventType) {
		case irr::gui::EGET_BUTTON_CLICKED:
			playSelect();
			return PodiumState::_descs.at(id).fct(this);
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

void PodiumState::unload()
{
	for (auto elem : _text) {
		elem->remove();
	}
	_text.clear();
	unloadButtons();
	AState::unload();
}

void PodiumState::unloadButtons()
{
	for (auto &n : _buttons)
		n->remove();
	_buttons.clear();
}

void PodiumState::unloadDeadPlayer()
{
	for (auto i = 1; i <= 4; i++) {
		try {
			auto &n = _share.getSharedNode("deadPlayer" + std::to_string(i));
			n.remove();
			_share.delSharedNode("deadPlayer" + std::to_string(i));
		} catch (std::exception const &err) {}
	}
}
