/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** LoadState.cpp
*/
#ifdef  UNIX
#include <glob.h>
#endif
#include "../../include/States/LoadState.hpp"
#include "../../include/Singletons/StateMachine.hpp"
#include "../../include/Singletons/IrrManager.hpp"
#include "../../include/Singletons/EventReceiver.hpp"
#include "../../include/Singletons/AssetsPool.hpp"

const std::map<LoadState::Actions , LoadState::ButtonsDesc>
	LoadState::_descs{
	{LoadState::SAVE1,    {
		{610, 250, 1300, 300},
		"save",
		[](LoadState *self) {
			StateMachine::getInstance().pop();
		}
	}},
	{LoadState::SAVE2,    {
		{610, 350, 1300, 400},
		"save",
		[](LoadState *self) {
			StateMachine::getInstance().pop();
		}
	}},
	{LoadState::SAVE3,    {
		{610, 450, 1300, 500},
		"save",
		[](LoadState *self) {
			StateMachine::getInstance().pop();
		}
	}},
	{LoadState::SAVE4,    {
		{610, 550, 1300, 600},
		"save",
		[](LoadState *self) {
			StateMachine::getInstance().pop();
		}
	}},
	{LoadState::CANCEL,  {
		{1570, 850,  1870, 900},
		"cancel",
		[](LoadState *self) {
			StateMachine::getInstance().pop();
		}
	}},
	{LoadState::PREV,    {
		{835, 850,  935, 900},
		"save",
		[](LoadState *self) {
			//TODO secure
			self->_idx -= 1;
			self->setSaveButtons();
		}
	}},
	{LoadState::NEXT,    {
		{985, 850,  1085, 900},
		"save",
		[](LoadState *self) {
			//TODO secure
			self->_idx += 1;
			self->setSaveButtons();
		}
	}}
};

LoadState::LoadState(AStateShare &_share) : AState(_share), AMenuSound(), _idx(0)
{
}

LoadState::~LoadState()
{
}

void LoadState::loadButtons()
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
	setSaveButtons();
	er.registerEvent(1, irr::EEVENT_TYPE::EET_GUI_EVENT,
		[this](const irr::SEvent &ev) {
			auto id = static_cast<Actions>(ev.GUIEvent.Caller->getID());
			if (LoadState::_descs.count(id) > 0)
				this->applyEventButton(ev, id);
			return true;
		});
	#ifdef UNIX
		glob_t glob_result;
		glob("../.save/*", GLOB_TILDE, NULL, &glob_result);
		for (unsigned int i = 0; i < glob_result.gl_pathc; ++i)
			_saves.emplace_back(glob_result.gl_pathv[i]);
	#endif
}

void LoadState::unloadButtons()
{
	auto &er = EventReceiver::getInstance();
	er.unregisterEvent(1, irr::EEVENT_TYPE::EET_GUI_EVENT);
	for (auto &n : _buttons)
		n->remove();
	_buttons.clear();
}

void LoadState::load()
{
	loadButtons();
	AState::load();
}

void LoadState::unload()
{
	unloadButtons();
	AState::unload();
}

void LoadState::update()
{
	if (getSharedResources().isKeyDown(irr::KEY_ESCAPE))
		StateMachine::getInstance().pop();
	AState::update();
}

void LoadState::draw()
{
	auto &im = IrrManager::getInstance();
	im.getSmgr()->drawAll();
	im.getGuienv()->drawAll();
}

void LoadState::applyEventButton(const irr::SEvent &ev, LoadState::Actions id)
{
	auto b = getButton(id);
	auto hover_name = "buttons/" + _descs.at(id).name + "_hover.png";
	auto name = "buttons/" + _descs.at(id).name + ".png";
	auto &ap = AssetsPool::getInstance();

	switch (ev.GUIEvent.EventType) {
		case irr::gui::EGET_BUTTON_CLICKED:
			LoadState::_descs.at(id).fct(this);
			playSelect();
			break;
		case irr::gui::EGET_ELEMENT_HOVERED:
			b->setImage(ap.loadTexture(hover_name));
			playCursor();
			break;
		case irr::gui::EGET_ELEMENT_LEFT:
			b->setImage(ap.loadTexture(name));
			break;
		default:
			break;
	}
}

irr::gui::IGUIButton *LoadState::getButton(LoadState::Actions id) const
{
	if (id < SAVE1 || id > SAVE1 + LOAD_BUTTON_NUMBER)
		return nullptr;
	return (_buttons.at(id - SAVE1));
}

void LoadState::setSaveButtons()
{
	size_t i = _idx * 4;
	std::string empty = "- Empty Slot -";

	for (; i < _saves.size() && (i == _idx * 4 || i%4); ++i) {
		_buttons[i%4]->setText(std::wstring(_saves[i].begin(),
			_saves[i].end()).c_str());
		_buttons[i%4]->setEnabled(true);
	}
	for (; i == _idx * 4 || i%4; ++i) {
		_buttons[i%4]->setEnabled(false);
		_buttons[i%4]->setText(std::wstring(empty.begin(),
			empty.end()).c_str());
	}
	_buttons[PREV - SAVE1]->setEnabled(_idx > 0);
	_buttons[NEXT - SAVE1]->setEnabled((_idx + 1) * 4 < _saves.size());
}
