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

