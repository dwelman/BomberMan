//
// Created by Dean DU TOIT on 2017/08/11.
//

#include <GUI.hpp>

void		setupEvents(GUICrate &crate)
{
	//Main menu
	CEGUI::NamedElement *start = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->getChildElementRecursive("StartGame");
	crate.MenuFunctions.push_back(new MenuFunction(start, CEGUI::PushButton::EventClicked, &startGameMainMenu, crate));

	CEGUI::NamedElement *settings = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->getChildElementRecursive("Settings");
	crate.MenuFunctions.push_back(new MenuFunction(settings, CEGUI::PushButton::EventClicked, &openSettingsMenu, crate));

	CEGUI::NamedElement *exit = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->getChildElementRecursive("Exit");
	crate.MenuFunctions.push_back(new MenuFunction(exit, CEGUI::PushButton::EventClicked, &setExit, crate));

	//Settings
	CEGUI::NamedElement *videoSettingsBtn = crate.settings->getChildElementRecursive("VideoSettingsBtn");
	crate.MenuFunctions.push_back(new MenuFunction(videoSettingsBtn, CEGUI::PushButton::EventClicked, &showVideoSettingsPane, crate));
	crate.settingPanes->Add(crate.settings->getChildElementRecursive("VideoSettingsPane"), "VideoSettings");

	CEGUI::NamedElement *audioSettingsBtn = crate.settings->getChildElementRecursive("AudioSettingsBtn");
	crate.MenuFunctions.push_back(new MenuFunction(audioSettingsBtn, CEGUI::PushButton::EventClicked, &showAudioSettingsPane, crate));
	crate.settingPanes->Add(crate.settings->getChildElementRecursive("AudioSettingsPane"), "AudioSettings");

	CEGUI::NamedElement *controlsBtn = crate.settings->getChildElementRecursive("ControlsBtn");
	crate.MenuFunctions.push_back(new MenuFunction(controlsBtn, CEGUI::PushButton::EventClicked, &showControlsPane, crate));
	crate.settingPanes->Add(crate.settings->getChildElementRecursive("ControlsPane"), "Controls");

	CEGUI::NamedElement *closeSettings = crate.settings->getChildElementRecursive("Close");
	crate.MenuFunctions.push_back(new MenuFunction(closeSettings, CEGUI::PushButton::EventClicked, &openMainMenu, crate));

	CEGUI::NamedElement *resolutionNext = crate.settings->getChildElementRecursive("ResolutionNext");
	crate.MenuFunctions.push_back(new MenuFunction(resolutionNext, CEGUI::PushButton::EventClicked, &resolutionNextClick, crate));

	CEGUI::NamedElement *resolutionPrev = crate.settings->getChildElementRecursive("ResolutionPrevious");
	crate.MenuFunctions.push_back(new MenuFunction(resolutionPrev, CEGUI::PushButton::EventClicked, &resolutionPreviousClick, crate));

	CEGUI::NamedElement *fullscreenNext = crate.settings->getChildElementRecursive("FullscreenNext");
	crate.MenuFunctions.push_back(new MenuFunction(fullscreenNext, CEGUI::PushButton::EventClicked, &fullscreenNextClick, crate));

	CEGUI::NamedElement *fullscreenPrev = crate.settings->getChildElementRecursive("FullscreenPrevious");
	crate.MenuFunctions.push_back(new MenuFunction(fullscreenPrev, CEGUI::PushButton::EventClicked, &fullscreenPreviousClick, crate));

	CEGUI::NamedElement *apply = crate.settings->getChildElementRecursive("Apply");
	crate.MenuFunctions.push_back(new MenuFunction(apply, CEGUI::PushButton::EventClicked, &applyClick, crate));

	CEGUI::NamedElement *moveUpVal = crate.settings->getChildElementRecursive("MoveUpVal");
	crate.MenuFunctions.push_back(new MenuFunction(moveUpVal, CEGUI::Editbox::EventTextSelectionChanged, &keyBindActiveUp, crate));
	crate.MenuFunctions.push_back(new MenuFunction(moveUpVal, CEGUI::Editbox::EventCaretMoved, &keyBindActiveUp, crate));
	crate.MenuFunctions.push_back(new MenuFunction(moveUpVal, CEGUI::Editbox::EventTextAccepted, &keyBindActiveUp, crate));
	crate.MenuFunctions.push_back(new MenuFunction(moveUpVal, CEGUI::Editbox::EventKeyDown, &keyBindActiveUp, crate));




}

void	switchLayouts(CEGUI::Window *from, CEGUI::Window *to)
{
	if (from && to)
	{
		to->setVisible(true);
		from->setVisible(false);
		CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(to);
	}
}

bool startGameMainMenu(const CEGUI::EventArgs& e, CEGUI::NamedElement *_element, GUICrate &var)
{
	var.audio->PlayMusic(0);
	var.audio->PlaySFX(0);
	var.manager->SetGameStarted(true);
	return (true);
};

bool openSettingsMenu(const CEGUI::EventArgs& e, CEGUI::NamedElement *_element, GUICrate &var)
{
	switchLayouts(var.main, var.settings);
	var.pendingSettings = var.activeSettings;
	return (true);
};

bool openMainMenu(const CEGUI::EventArgs& e, CEGUI::NamedElement *_element, GUICrate &var)
{
	switchLayouts(var.settings, var.main);
	return (true);
};

bool setExit(const CEGUI::EventArgs& e, CEGUI::NamedElement *_element, GUICrate	&var)
{
    *var.mustQuit = true;
    return (true);
};

bool resolutionNextClick(const CEGUI::EventArgs& e, CEGUI::NamedElement *_element, GUICrate	&var)
{
    std::string newVal = *var.pendingSettings.video.resolution.next();
    std::string xres = newVal.substr(0, newVal.find("x"));
    std::string yres = newVal.substr(newVal.find("x") + 1,  newVal.size() - newVal.find("x"));

    var.settings->getChildElementRecursive("ResolutionValue")->setProperty("Text", newVal );
	var.pendingSettings.video.resolution.activeValue = newVal;
	var.pendingSettings.changed = true;

	return (true);
};

bool resolutionPreviousClick(const CEGUI::EventArgs& e, CEGUI::NamedElement *_element, GUICrate	&var)
{
    std::string newVal = *var.pendingSettings.video.resolution.previous();
    std::string xres = newVal.substr(0, newVal.find("x"));
    std::string yres = newVal.substr(newVal.find("x") + 1,  newVal.size() - newVal.find("x"));

    var.settings->getChildElementRecursive("ResolutionValue")->setProperty("Text", newVal);
	var.pendingSettings.video.resolution.activeValue = newVal;
	var.pendingSettings.changed = true;

    return (true);
};

bool fullscreenNextClick(const CEGUI::EventArgs& e, CEGUI::NamedElement *_element, GUICrate	&var)
{
    std::string newVal = *var.pendingSettings.video.fullScreen.next();

    var.settings->getChildElementRecursive("FullscreenValue")->setProperty("Text", newVal);
	var.pendingSettings.video.fullScreen.activeValue = newVal;
	var.pendingSettings.changed = true;
    return (true);
};

bool fullscreenPreviousClick(const CEGUI::EventArgs& e, CEGUI::NamedElement *_element, GUICrate	&var)
{
    std::string newVal = *var.pendingSettings.video.fullScreen.previous();

    var.settings->getChildElementRecursive("FullscreenValue")->setProperty("Text", newVal);
	var.pendingSettings.video.fullScreen.activeValue = newVal;
	var.pendingSettings.changed = true;
    return (true);
};

bool applyClick(const CEGUI::EventArgs& e, CEGUI::NamedElement *_element, GUICrate	&var)
{
	if (var.pendingSettings.changed)
	{
		std::string newres = var.pendingSettings.video.resolution.activeValue;
		std::string xres = newres.substr(0, newres.find("x"));
		std::string yres = newres.substr(newres.find("x") + 1, newres.size() - newres.find("x"));

		if (!(xres == g_cfg["xres"].to_str() && yres == g_cfg["yres"].to_str())
			|| g_cfg["fullscreen"].to_str() != var.pendingSettings.video.fullScreen.activeValue)
		{
			g_cfg["fullscreen"] = var.pendingSettings.video.fullScreen.activeValue;
			g_cfg["xres"] = xres;
			g_cfg["yres"] = yres;
			var.displayChanged = true;
		}
		var.activeSettings = var.pendingSettings;
		auto vals = var.keybindings.keyMapVals.begin();
		for  (auto it = var.keybindings.keyMapChanges.begin(); it != var.keybindings.keyMapChanges.end(); it++, vals++)
		{
			g_cfg[(*it).c_str()] = *vals;
			//var.keybindings.actionToKeyCode[var.keybindings.]
			//(*keybindings.actionToKeyCode)[keybindings.actionToMap] = e.key.keysym.sym;
			vals++;
		}
		g_cfg.saveConfig();
	}
    return (true);
};

bool showVideoSettingsPane(const CEGUI::EventArgs& e, CEGUI::NamedElement *_element, GUICrate	&var)
{
	var.settingPanes->SetActive("VideoSettings");
	return (true);
}

bool showAudioSettingsPane(const CEGUI::EventArgs& e, CEGUI::NamedElement *_element, GUICrate	&var)
{
	var.settingPanes->SetActive("AudioSettings");
	return (true);
}

bool showControlsPane(const CEGUI::EventArgs& e, CEGUI::NamedElement *_element, GUICrate	&var)
{
	var.settingPanes->SetActive("Controls");
	return (true);
}

bool keyBindActiveUp(const CEGUI::EventArgs& e, CEGUI::NamedElement *_element, GUICrate	&var)
{
	var.keybindings.catchNext = true;
	var.keybindings.actionToMap = P_MOVE_UP;
	var.keybindings.actionToMapKey = "P_MOVE_UP";
	var.pendingSettings.changed = true;
}