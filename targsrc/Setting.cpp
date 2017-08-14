//
// Created by Dean DU TOIT on 2017/08/14.
//

#include <Settings.hpp>
#include <main.hpp>

Setting::Setting(std::string cfgkey, std::string activeValue)
{
	this->cfgkey = cfgkey;
	this->activeValue = activeValue;
	push_back(activeValue.c_str());
	it = 0;
}

void    Setting::push_back(std::string *val)
{
    push_back(val->c_str());
}

void    Setting::push_back(const char *val)
{
	if (values.size() > 0)
		for (int i = 0; i < values.size(); i++)
		{

			if (case_ins_cmp(val, *values[i]))
				return;
		}
    values.push_back(new std::string(val));
}

std::string*    &Setting::next()
{
    if (it == values.size() - 1)
        it = 0;
    else
        it++;
    return (values[it]);
}

std::string*   &Setting::previous()
{
    if (it == 0)
    {
        it = values.size() > 0 ? values.size() - 1 : 0;
    }
    else
        it--;
    return (values[it]);
}

std::string*  &Setting::current()
{
    return (values[it]);
}

void                                Setting::setIterator(std::string val)
{
    for (int i = 0; i < values.size(); i++)
    {
		if (*values[i] == val)
        {
            it += i;
        }
    }
}

SettingsState::SettingsState()
{
	memset(this, 0, sizeof(SettingsState));
}

VideoSettings::VideoSettings()
{
	memset(this, 0, sizeof(VideoSettings));
}

Setting::Setting()
{
	memset(this, 0, sizeof(Setting));
}

void				loadSettingsFromDefaultConfig(SettingsState &settings)
{
	settings.video.resolution = Setting("#multiple", g_cfg["xres"].to_str() + "x" + g_cfg["yres"].to_str());
	settings.video.fullScreen = Setting("#multiple", case_ins_cmp("yes", g_cfg["fullscreen"].to_str()) ? "Yes" : "No");
}

