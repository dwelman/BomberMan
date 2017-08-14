#pragma once

#include <Setting.hpp>

struct Setting
{
	std::vector<std::string*>            values;
	std::vector<std::string*>::iterator  it;

	void                                push_back(std::string *val);
	void                                push_back(const char *val);
	std::vector<std::string*>::iterator &next();
	std::vector<std::string*>::iterator &previous();
	std::vector<std::string*>::iterator &current();
	void                                setIterator(std::string val);
};


struct VideoSettings
{
	Setting			resolution;
	Setting			fullScreen;
};

struct SettingsState
{
	VideoSettings	video;
};