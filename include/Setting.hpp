//
// Created by Dean DU TOIT on 2017/08/14.
//

#ifndef BOMBERMAN_SETTING_HPP
#define BOMBERMAN_SETTING_HPP

#include<string>
#include<vector>

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

#endif //BOMBERMAN_SETTING_HPP
