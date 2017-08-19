#include <main.hpp>
#include <GUI.hpp>


PaneGroup::PaneGroup(){}
PaneGroup::~PaneGroup() {}

PaneGroup::PaneGroup(PaneGroup &src)
{
	*this = src;
}


PaneGroup							&PaneGroup::operator=(PaneGroup const &c)
{
	panes = c.panes;
	active = c.active;
	return (*this);
}

void								PaneGroup::Add(CEGUI::NamedElement *elem, std::string const & name)
{
	panes[name] = elem;
}

std::string const					&PaneGroup::GetActiveName()
{
	return (active);
}

void								PaneGroup::SetActive(std::string const &active)
{
	if (panes.find(active) != panes.end())
	{
		this->active = active;
		for (auto it = panes.begin(); it != panes.end(); it++)
		{
			(*it).second->setProperty("Visible", "False");
		}
		panes[this->active]->setProperty("Visible", "True");
	}
}
