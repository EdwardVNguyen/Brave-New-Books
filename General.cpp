#include "General.h"


std::string spaceToUnderscore(std::string& text)
{
	std::replace(text.begin(), text.end(), ' ', '_');
	return text;
}