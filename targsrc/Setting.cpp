//
// Created by Dean DU TOIT on 2017/08/14.
//
#include <Setting.hpp>

void    Setting::push_back(std::string *val)
{
    values.push_back(val);
    if (values.size() == 1)
        it = values.begin();
}

#include <iostream>
void    Setting::push_back(const char *val)
{
    values.push_back(new std::string(val));
    std::cout << *values[0] << std::endl;
    it = values.begin();
}

std::vector<std::string*>::iterator    &Setting::next()
{
    if (it + 1 == values.end())
        it = values.begin();
    else
        it++;
    return (it);
}

std::vector<std::string*>::iterator   &Setting::previous()
{
    if (it == values.begin())
    {
        it = values.end();
        it--;
    }
    else
        it--;
    return (it);
}

std::vector<std::string*>::iterator  &Setting::current()
{
    return (it);
}

void                                Setting::setIterator(std::string val)
{
    for (auto itr = values.begin(); itr != values.end(); itr++)
    {
        if (**itr == val)
        {
            it = itr;
        }
    }
}
