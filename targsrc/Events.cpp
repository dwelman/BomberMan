//
// Created by Dean DU TOIT on 2017/08/11.
//

#include <GUI.hpp>

bool setExit(const CEGUI::EventArgs& /*e*/, CEGUI::NamedElement *_element, GUIFunctionCrate	&var)
{
    *var.mustQuit = true;
    //  _element->getParentElement()->setProperty("hide", "true");
    return (true);
};

bool startGameMainMenu(const CEGUI::EventArgs& /*e*/, CEGUI::NamedElement *_element, GUIFunctionCrate	&var)
{
    var.manager->SetGameStarted(true);
    return (true);
};