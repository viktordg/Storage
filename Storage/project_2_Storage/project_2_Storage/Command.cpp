#include "stdafx.h"
#include "Command.h"


Command::Command()
{
	Date defaultDate;
	this->command = "";
	this->date = defaultDate;
}
Command::Command(const std::string command, const Date date)
{
	this->command = command;
	this->date = date;
}

std::string Command::get_command() const
{
	return this->command;
}
Date Command::get_date() const
{
	return this->date;
}
