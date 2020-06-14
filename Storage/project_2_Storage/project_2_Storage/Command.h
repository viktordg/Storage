#pragma once
#include"Date.h"
#include<string>
/*! \class Command
	\brief Class which defines a Command
*/
class Command
{
private:
	std::string command;
	Date date;
public:
	Command();
	Command(const std::string command, const Date date);

	std::string get_command() const;
	Date get_date() const;
};

