#pragma once

#include <Setting.hpp>

struct Setting
{
	std::vector<std::string*>           values;
	int									it;
	std::string							activeValue;
	std::string							cfgkey;

	void                                push_back(std::string *val);
	void                                push_back(const char *val);
	std::string*						&next();
	std::string*						&previous();
	std::string*						&current();
	void                                setIterator(std::string val);

	Setting(std::string cfgkey, std::string activeValue);
	Setting();

};

struct VideoSettings
{
	Setting			resolution;
	Setting			fullScreen;

	VideoSettings();
};

struct Controls
{

};

struct SettingsState
{
	VideoSettings				video;
	bool						changed;

	SettingsState();
};