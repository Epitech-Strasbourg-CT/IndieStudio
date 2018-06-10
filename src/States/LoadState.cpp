/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** LoadState.cpp
*/
#ifdef __linux__
#include <glob.h>
#elif _WIN32
	#include <windows.h>
#endif
#include "../../include/States/LoadState.hpp"
#include "../../include/Singletons/StateMachine.hpp"
#include "../../include/Singletons/IrrManager.hpp"
#include "../../include/Singletons/EventReceiver.hpp"
#include "../../include/Singletons/AssetsPool.hpp"
#include "../../include/States/TransitionToGameState.hpp"

const std::map<LoadState::Actions, LoadState::ButtonsDesc>
	LoadState::_descs {
	{LoadState::SAVE1,    {
		{610, 250, 1300, 300},
		"default",
		[](LoadState *self) {
			StateMachine::getInstance().push(
				new TransitionToGameState(self->_share,
					self->_saves[self->_idx * 4 + 0]),
				false);
			return true;
		}
	}},
	{LoadState::SAVE2,    {
		{610, 350, 1300, 400},
		"default",
		[](LoadState *self) {
			StateMachine::getInstance().push(
				new TransitionToGameState(self->_share,
					self->_saves[self->_idx * 4 + 1]),
				false);
			return true;
		}
	}},
	{LoadState::SAVE3,    {
		{610, 450, 1300, 500},
		"default",
		[](LoadState *self) {

			StateMachine::getInstance().push(
				new TransitionToGameState(self->_share,
					self->_saves[self->_idx * 4 + 2]),
				false);
			return true;
		}
	}},
	{LoadState::SAVE4,    {
		{610, 550, 1300, 600},
		"default",
		[](LoadState *self) {
			StateMachine::getInstance().push(
				new TransitionToGameState(self->_share,
					self->_saves[self->_idx * 4 + 3]),
				false);
			return true;
		}
	}},
	{LoadState::CANCEL,  {
		{1570, 850,  1870, 900},
		"cancel",
		[](LoadState *self) {
			self->externalEventsClean();
			StateMachine::getInstance().pop();
			return false;
		}
	}},
	{LoadState::PREV,    {
		{785, 850,  935, 900},
		"prev",
		[](LoadState *self) {
			self->_idx -= 1;
			self->setSaveButtons();
			return true;
		}
	}},
	{LoadState::NEXT,    {
		{985, 850,  1135, 900},
		"next",
		[](LoadState *self) {
			self->_idx += 1;
			self->setSaveButtons();
			return true;
		}
	}}
};

LoadState::LoadState(AStateShare &_share) : AState(_share),
AMenuSound(), _idx(0)
{
}

LoadState::~LoadState()
{
	eventsClean();
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
		b->setOverrideFont(_share.getFont());
		_buttons.push_back(b);
	}
	#ifdef __linux__
	glob_t glob_result;

	glob(".save/*.dat", GLOB_TILDE, NULL, &glob_result);
	for (unsigned int i = 0; i < glob_result.gl_pathc; ++i)
		_saves.emplace_back(glob_result.gl_pathv[i]);
	_idx = 0;
	#elif _WIN32
	char buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	std::string::size_type pos = std::string( buffer ).find_last_of("\\/");
	auto path =  std::string( buffer ).substr( 0, pos) + "\\.save\\*.dat";

	HANDLE hFind;
	WIN32_FIND_DATA data;

	hFind = FindFirstFile(path.c_str(), &data);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			_saves.emplace_back(".save/" + std::string(data.cFileName));
		} while (FindNextFile(hFind, &data));
		FindClose(hFind);
	}
	#endif
	setSaveButtons();
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
	eventsSetup();
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
	_share.getFunc("rotateMenu")();
	AState::update();
	AssetsPool::getInstance().cleanSound();
	if (getSharedResources().isKeyDown(irr::KEY_ESCAPE))
		StateMachine::getInstance().pop();
}

void LoadState::draw()
{
	auto &im = IrrManager::getInstance();
	im.getSmgr()->drawAll();
	im.getGuienv()->drawAll();
}

bool LoadState::applyEventButton(const irr::SEvent &ev, LoadState::Actions id)
{
	auto b = getButton(id);
	auto hover_name = "buttons/" + _descs.at(id).name + "_hover.png";
	auto name = "buttons/" + _descs.at(id).name + ".png";
	auto &ap = AssetsPool::getInstance();

	switch (ev.GUIEvent.EventType) {
		case irr::gui::EGET_BUTTON_CLICKED:
			playSelect();
			return LoadState::_descs.at(id).fct(this);
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

	for (; i < _saves.size() && (i == (_idx * 4) || i%4); ++i) {
		std::string temp(_saves[i].substr(_saves[i].rfind('/') + 1));
		_buttons[i%4]->setText(std::wstring(temp.begin(),
			temp.end()).c_str());
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

void LoadState::eventsSetup()
{
	_eventsActivate = true;
	auto &er = EventReceiver::getInstance();
	er.registerEvent(2, irr::EEVENT_TYPE::EET_GUI_EVENT,
		[this](const irr::SEvent &ev) {
			if (!this->isLoaded() || !this->isEnable())
				return true;
		auto id = static_cast<Actions >(ev.GUIEvent.Caller->getID());
			if (LoadState::_descs.count(id) > 0)
				return this->applyEventButton(ev, id);
			return true;
		});
}

void LoadState::eventsClean()
{
	if (!_eventsActivate)
		return;
	auto &er = EventReceiver::getInstance();
	er.unregisterEvent(2, irr::EEVENT_TYPE::EET_GUI_EVENT);
	_eventsActivate = false;
}

void LoadState::externalEventsClean()
{
	if (!_eventsActivate)
		return;
	_eventsActivate = false;
}


const std::string LoadState::getName() const
{
	return "load";
}
