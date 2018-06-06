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

#ifndef BOMBERMAN_SETTINGSSTATE_HPP
	#define BOMBERMAN_SETTINGSSTATE_HPP

	#define SETTINGS_BUTTON_NUMBER 8

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

class SettingsState : public AState {
public:

	explicit SettingsState(AStateShare &_share);
	~SettingsState();


	void loadBouttons();
	void unloadBouttons();
	void load() override;
	void unload() override;

	void draw() override;

	void applyEventBoutton(const irr::SEvent &ev, SettingsActions id);
	irr::gui::IGUIButton *getBoutton(SettingsActions) const;

	struct BouttonsDesc {
		irr::core::rect<irr::s32> pos;
		std::string name;
		std::function<void(SettingsState *)> fct;
	};

private:
	std::vector<irr::gui::IGUIButton *> _bouttons;
	static const std::map<SettingsActions , BouttonsDesc> _descs;
	irrklang::ik_f32 _master;
	irrklang::ik_f32 _music;
	irrklang::ik_f32 _sfx;
};

#endif //BOMBERMAN_SETTINGSSTATE_HPP
