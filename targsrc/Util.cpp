#include <Util.hpp>

std::string		str_to_upper(std::string const &_str)
{
	std::string	returnVal = _str;

	for (auto it = returnVal.begin(); it < returnVal.end(); it++)
		*it = std::toupper(*it);
	return (returnVal);
}

bool		case_ins_cmp(std::string const &_str1, std::string const &_str2)
{
	return (str_to_upper(_str1) == str_to_upper(_str2));
}