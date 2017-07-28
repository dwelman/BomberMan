//
// Created by Dean DU TOIT on 2017/07/28.
//

#include "ConfigEditor.hpp"

ConfigEditor::ConfigEditor(std::string const _filename) : filename(_filename)
{
    std::ifstream stream;
    stream.open (filename);
    std::string line;
    size_t      find;
    std::string key;
    std::string val;

    if (stream.is_open())
    {
        while (getline (stream, line))
        {
            if (line.find("#") != std::string::npos)
                line = line.substr(0, line.find("#"));
            find = line.find("=");
            if (find != std::string::npos)
            {
                key = line.substr(0, find);
                val =  line.substr(find + 1, line.size() - find);
                if (key.size() && val.size())
                {
                    for (auto it = key.begin(); it < key.end(); it++)
                        *it = std::toupper(*it);
                    keys[key] = val;
                }
            }
        }
    }
}

ConfigEditor::ConfigEditor(ConfigEditor const &src)
{
    *this = src;
}

ConfigEditor const &ConfigEditor::operator=(ConfigEditor const &src)
{
    this->keys = src.keys;
    return (*this);
}

ConfigEditor::~ConfigEditor()
{
}

keyref       ConfigEditor::operator[]( std::string const &_key)
{
    std::string keyUpper = _key;

    for (auto it = keyUpper.begin(); it < keyUpper.end(); it++)
        *it = std::toupper(*it);
    return (keyref(keys[keyUpper]));
}

void              ConfigEditor::saveConfig()
{
    std::ofstream stream;

    stream.open(filename);
    for (auto it = keys.begin(), end = keys.end(); it != end; it++ )
    {
        stream << it->first << "=" << it->second << "\n";
    }
};

keyref::keyref(std::string &_ref) : ref(_ref)
{
}

keyref const   &keyref::operator=( int const &_val)
{
    ref = std::to_string(_val);
}

keyref const   &keyref::operator=( std::string const &_val)
{
    ref = _val;
}

int                   keyref::to_int()
{
    return (std::stoi(ref));
}

std::string           keyref::to_str()
{
    return (ref);
}


std::ostream& operator<<(std::ostream& os, const keyref& dt)
{
    os << dt.ref;
    return os;
}