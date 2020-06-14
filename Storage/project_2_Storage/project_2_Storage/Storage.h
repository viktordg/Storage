#pragma once
#include<iostream>
#include"Date.h"
#include"Product.h"
#include"Place.h"
#include"Command.h"
#include<ctime>
#include<vector>

/*! \class Storage
\brief Class which defines a Storage
*/
class Storage
{
private:
	int volume;
	std::vector<Place> places;
	std::vector<Command> commands;

	//! used to coutn leap years - it is used in daysBetweenTwoDates method
	int countLeapYears(Date d)
	{
		int years = d.get_year();

		if (d.get_month() <= 2)
		{
			years--;
		}

		return years / 4 - years / 100 + years / 400;
	}
	//! count days between two dates
	int daysBetweenTwoDates(Date firstDate, Date secondDate)
	{
		const int monthDays[12] = { 31, 28, 31, 30, 31, 30,
			31, 31, 30, 31, 30, 31 };

		long int n1 = firstDate.get_year() * 365 + firstDate.get_day();
		for (int i = 0; i < firstDate.get_month() - 1; i++)
		{
			n1 += monthDays[i];
		}
		n1 += countLeapYears(firstDate);

		long int n2 = secondDate.get_year() * 365 + secondDate.get_day();
		for (int i = 0; i < secondDate.get_month() - 1; i++)
		{
			n2 += monthDays[i];
		}
		n2 += countLeapYears(secondDate);

		return (n2 - n1);
	}
	//! gets current date
	Date get_currentDate()
	{
		struct tm newtime;
		time_t now = time(0);
		localtime_s(&newtime, &now);
		int year = 1900 + newtime.tm_year;
		int month = 1 + newtime.tm_mon;
		int day = newtime.tm_mday;

		Date date(day, month, year);

		return date;
	}
	//! creates al places in a storage
	void generate_places()
	{
		int section = 1;
		int shelf = 1;
		int number = 1;

		int current_volume = 0;
		const int place_volume = 20;
		while ((current_volume + place_volume) <= this->volume)
		{
			current_volume += place_volume;

			Place current_place;
			if (number <= 10)
			{			
				current_place.set_number(number);
				current_place.set_shelf(shelf);
				current_place.set_section(section);

				number++;
			}
			else if (number > 10 && shelf <= 5)
			{
				number = 1;

				shelf++;

				current_place.set_number(number);
				current_place.set_shelf(shelf);
				current_place.set_section(section);

				
			}
			else
			{
				number = 1;
				shelf = 1;

				section++;

				current_place.set_number(number);
				current_place.set_shelf(shelf);
				current_place.set_section(section);

			}

			this->places.push_back(current_place);
		}
	}
public:
	Storage();

	void set_volume(int volume);

	void print();
	void add(const Product &product);
	void remove(const std::string &name, int quantity);
	void log(const Date &from, const Date &to);
	void clean(const Date &date);

	void print_on_file(std::ofstream &file);
};

