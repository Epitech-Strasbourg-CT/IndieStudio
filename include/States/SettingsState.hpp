/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
**
*/

#include <unordered_map>
#include <irrTypes.h>
#include <irrKlang.h>
#include <IGUIButton.h>
#include <vector>
#include "../Abstracts/AState.hpp"
#include "../Abstracts/AMenuSound.hpp"

#ifndef BOMBERMAN_SETTINGSSTATE_HPP
	#define BOMBERMAN_SETTINGSSTATE_HPP

	#define SETTINGS_BOUTON_NUMBER 8

enum SettingsActions {
	MASTER_VOL_UP = 200,
	MASTER_VOL_DOWN,
	MUSIC_VOL_UP,
	MUSIC_VOL_DOWN,
	SFX_VOL_UP,
	SFX_VOL_DOWN,
	VOL_APPLY,
	VOL_CANCEL
};

class SettingsState : public AState, public AMenuSound {
public:

	explicit SettingsState(AStateShare &_share);
	~SettingsState();


	void loadButtons();
	void unloadButtons();
	void load() override;
	void unload() override;

	void update() override;
	void draw() override;

	bool applyEventButton(const irr::SEvent &ev, SettingsActions id);
	irr::gui::IGUIButton *getButton(SettingsActions) const;

	struct ButtonsDesc {
		irr::core::rect<irr::s32> pos;
		std::string name;
		std::function<bool(SettingsState *)> fct;
	};
	void eventsSetup();
	void eventsClean();
	void externalEventsClean();
private:
	std::vector<irr::gui::IGUIButton *> _buttons;
	static const std::map<SettingsActions , ButtonsDesc> _descs;
	irrklang::ik_f32 _master;
	irrklang::ik_f32 _music;
	irrklang::ik_f32 _sfx;
	bool _eventsActivate;
};

#endif //BOMBERMAN_SETTINGSSTATE_HPP
