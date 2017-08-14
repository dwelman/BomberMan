//
// Created by Dean DU TOIT on 2017/08/11.
//

#include <GUI.hpp>
void	switchLayouts(CEGUI::Window *from, CEGUI::Window *to)
{
	if (from && to)
	{
		to->setVisible(true);
		from->setVisible(false);
		CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(to);
	}
}


bool startGameMainMenu(const CEGUI::EventArgs& e, CEGUI::NamedElement *_element, GUIFunctionCrate &var)
{
	var.manager->SetGameStarted(true);
	return (true);
};

bool openSettingsMenu(const CEGUI::EventArgs& e, CEGUI::NamedElement *_element, GUIFunctionCrate &var)
{
	switchLayouts(var.main, var.settings);
	return (true);
};

bool openMainMenu(const CEGUI::EventArgs& e, CEGUI::NamedElement *_element, GUIFunctionCrate &var)
{
	switchLayouts(var.settings, var.main);
	return (true);
};

bool setExit(const CEGUI::EventArgs& e, CEGUI::NamedElement *_element, GUIFunctionCrate	&var)
{
    *var.mustQuit = true;
    return (true);
};

bool resolutionNextClick(const CEGUI::EventArgs& e, CEGUI::NamedElement *_element, GUIFunctionCrate	&var)
{
    std::string newVal = *(*var.settingContainer.resolution.next());
    std::string xres = newVal.substr(0, newVal.find("x"));
    std::string yres = newVal.substr(newVal.find("x") + 1,  newVal.size() - newVal.find("x"));

    var.settings->getChildElementRecursive("ResolutionValue")->setProperty("Text", newVal );
    g_cfg["xres"] = xres;
    g_cfg["yres"] = yres;
	return (true);
};

bool resolutionPreviousClick(const CEGUI::EventArgs& e, CEGUI::NamedElement *_element, GUIFunctionCrate	&var)
{
    std::string newVal = *(*var.settingContainer.resolution.previous());
    std::string xres = newVal.substr(0, newVal.find("x"));
    std::string yres = newVal.substr(newVal.find("x") + 1,  newVal.size() - newVal.find("x"));

    var.settings->getChildElementRecursive("ResolutionValue")->setProperty("Text", newVal);
    g_cfg["xres"] = xres;
    g_cfg["yres"] = yres;
    return (true);
};

bool fullscreenNextClick(const CEGUI::EventArgs& e, CEGUI::NamedElement *_element, GUIFunctionCrate	&var)
{
    std::string newVal = *(*var.settingContainer.fullScreen.next());

    var.settings->getChildElementRecursive("FullscreenValue")->setProperty("Text", newVal);
    return (true);
};

bool fullscreenPreviousClick(const CEGUI::EventArgs& e, CEGUI::NamedElement *_element, GUIFunctionCrate	&var)
{
    std::string newVal = *(*var.settingContainer.fullScreen.previous());

    var.settings->getChildElementRecursive("FullscreenValue")->setProperty("Text", newVal);
    return (true);
};

bool applyClick(const CEGUI::EventArgs& e, CEGUI::NamedElement *_element, GUIFunctionCrate	&var)
{
    g_cfg.saveConfig();
    return (true);
};