//
// Created by Dean DU TOIT on 2017/07/28.
//

#pragma once
#include <map>
#include <string>
#include <fstream>
#include <strstream>
#include <iostream>
#include <cctype>

struct keyref
{
    std::string &ref;
    keyref(std::string &_ref);
    keyref const   &operator=( int const &_val);
    keyref const   &operator=( std::string const &_val);
    int            to_int();
    std::string    to_str();
};

std::ostream& operator<<(std::ostream& os, const keyref& dt);

class ConfigEditor
{
private:
    std::map<std::string, std::string>  keys;
    const std::string                   filename;
    ConfigEditor();

public:
    ConfigEditor(std::string const _filename);
    ConfigEditor(ConfigEditor const &src);
    ConfigEditor const &operator=(ConfigEditor const &src);
    ~ConfigEditor();

    keyref            operator[]( std::string const &_key);

    template <typename T>
    void                setKeyVal(std::string const &key, T const &val)
    {
        (*this)[key] = val;
    }
    void              saveConfig();
};


