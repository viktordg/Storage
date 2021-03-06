#include "stdafx.h"
#include<iostream>
#include"Date.h"
#include"Storage.h"
#include<fstream>

int main()
{
	Storage storage;
	
	//! Test
	/*Date date;
	Date date1(14, 6, 2020);	
	storage.set_volume(60);
	Product product1("peach", date, date, "gradinata na selo", true, 5, "eko", 15);
	Product product2("aubergine", date, date, "gradinata na selo", true, 5, "eko", 10);
	Product product3("tiger", date, date, "jungle", true, 300, "dangerous", 1);
	Product product4("peach", date, date, "gradinata na drugoto selo", true, 5, "eko", 10);
	Product product5("peach", date1, date1, "gradinata na drugoto selo", true, 5, "eko", 10);
	storage.add(product1);
	storage.add(product2);
	storage.add(product3);
	storage.add(product4);
	storage.add(product5);
	storage.print();
	storage.print();
	storage.log(date1, date1);
	storage.remove("peach", 15);
	storage.remove("aubergine", 3);
	storage.print();
	storage.clean(date);
	storage.print();*/

	
	std::string input;

	std::string path;

	bool isOpen = false;

	bool flag = true;

	do
	{
		getline(std::cin, input);
		if (input.length() > 5)
		{
			int index = 0;
			for (size_t i = 0; input[i] != ' '; i++)
			{
				index++;
			}
			std::string command = input.substr(0, index);
			index++;

			if (command == "open")
			{
				isOpen = true;

				Storage temp;

				path = input.substr(index, input.length() - index);
				std::ifstream read(path);

				if (read.is_open())
				{
					std::string line; 
					std::getline(read, line);
					int volume = stoi(line);
					temp.set_volume(volume);
					storage = temp;

					read.close();
				}
				else
				{
					std::cout << "Unable to open!" << std::endl;
				}
			}
			else if (command == "saveas" && isOpen)
			{
				std::string newPath = input.substr(index, input.length() - index);
				std::ofstream saveasFile(newPath);

				std::ofstream saveas_file;
				saveas_file.open(newPath);

				if (saveasFile.is_open())
				{
					storage.print_on_file(saveas_file);
				}
				else
				{
					std::cout << "Unable to open!" << std::endl;
				}

				saveas_file.close();
			}
			else if (command == "print" && isOpen)
			{
				storage.print();
			}
			else if (command == "add" && isOpen)
			{
				int nameIndex = index;
				for (int i = index; input[i] != ' '; i++)
				{
					nameIndex++;
				}
				std::string name = input.substr(index, nameIndex - index);
				nameIndex++;

				int firstDateIndex = nameIndex;
				for (int i = nameIndex; input[i] != ' '; i++)
				{
					firstDateIndex++;
				}
				std::string firstDateToken = input.substr(nameIndex, firstDateIndex - nameIndex);
				int firstDay = stoi(firstDateToken.substr(0, 2));
				int firstMonth = stoi(firstDateToken.substr(3, 5));
				int firstYear = stoi(firstDateToken.substr(6, 10));
				Date firstDate(firstDay, firstMonth, firstYear);
				firstDateIndex++;

				int goesInStorageIndex = firstDateIndex;
				for (int i = firstDateIndex; input[i] != ' '; i++)
				{
					goesInStorageIndex++;
				}
				std::string goesInStorageToken = input.substr(firstDateIndex, goesInStorageIndex - firstDateIndex);
				int goesInStorageDay = stoi(goesInStorageToken.substr(0, 2));
				int goesInStorageMonth = stoi(goesInStorageToken.substr(3, 5));
				int goesInStorageYear = stoi(goesInStorageToken.substr(6, 10));
				Date goesInStorageDate(goesInStorageDay, goesInStorageMonth, goesInStorageYear);
				goesInStorageIndex++;

				int manufacturerIndex = goesInStorageIndex;
				for (int i = goesInStorageIndex; input[i] != ' '; i++)
				{
					manufacturerIndex++;
				}
				std::string manufacturer = input.substr(goesInStorageIndex, manufacturerIndex - goesInStorageIndex);
				manufacturerIndex++;

				int unitIndex = manufacturerIndex;
				for (int i = manufacturerIndex; input[i] != ' '; i++)
				{
					unitIndex++;
				}
				std::string unitToken = input.substr(manufacturerIndex, unitIndex - manufacturerIndex);
				bool unit;
				if (unitToken == "kilograms")
				{
					unit = true;
				}
				else
				{
					unit = false;
				}
				unitIndex++;

				int volumeIndex = unitIndex;
				for (int i = unitIndex; input[i] != ' '; i++)
				{
					volumeIndex++;
				}
				std::string volumeToken = input.substr(unitIndex, volumeIndex - unitIndex);
				int volume = stoi(volumeToken);
				volumeIndex++;

				int noteIndex = volumeIndex;
				for (int i = volumeIndex; input[i] != ' '; i++)
				{
					noteIndex++;
				}
				std::string note = input.substr(volumeIndex, noteIndex - volumeIndex);

				int quantity = stoi(input.substr(++noteIndex, input.size() - noteIndex));

				Product product(name, firstDate, goesInStorageDate, manufacturer, unit, volume, note, quantity);

				storage.add(product);
			}
			else if (command == "remove" && isOpen)
			{
				int nameIndex = index;
				for (int i = index; input[i] != ' '; i++)
				{
					nameIndex++;
				}
				std::string name = input.substr(index, nameIndex - index);

				int quantity = stoi(input.substr(++nameIndex, input.size() - nameIndex));

				storage.remove(name, quantity);
			}
			else if (command == "log" && isOpen)
			{
				int firstDateIndex = index;
				for (int i = index; input[i] != ' '; i++)
				{
					firstDateIndex++;
				}
				std::string firstDateToken = input.substr(index, firstDateIndex - index);
				int firstDay = stoi(firstDateToken.substr(0, 2));
				int firstMonth = stoi(firstDateToken.substr(3, 5));
				int firstYear = stoi(firstDateToken.substr(6, 10));
				Date firstDate(firstDay, firstMonth, firstYear);

				std::string secondDateToken = input.substr(++firstDateIndex, input.size() - firstDateIndex);
				int secondDay = stoi(secondDateToken.substr(0, 2));
				int secondMonth = stoi(secondDateToken.substr(3, 5));
				int secondYear = stoi(secondDateToken.substr(6, 10));
				Date secondDate(secondDay, secondMonth, secondYear);

				storage.log(firstDate, secondDate);
			}
			else if (command == "clean" && isOpen)
			{
				std::string dateToken = input.substr(index, input.size() - index);
				int day = stoi(dateToken.substr(0, 2));
				int month = stoi(dateToken.substr(3, 5));
				int year = stoi(dateToken.substr(6, 10));
				Date date(day, month, year);

				storage.clean(date);
			}
			
		}
		else if (input == "close" && isOpen)
		{
			isOpen = false;
		}
		else if (input == "save" && isOpen)
		{
			std::ofstream save_file;
			save_file.open(path);
			save_file.clear();

			storage.print_on_file(save_file);

			save_file.close();
		}
		else if (input == "help")
		{
			std::cout << "The following commands are supported : " << std::endl;
			std::cout << "open <file>	opens <file>" << std::endl;
			std::cout << "close			closes currently opened file " << std::endl;
			std::cout << "save			saves the currently open file " << std::endl;
			std::cout << "saveas <file>	saves the currently open file in <file> " << std::endl;
			std::cout << "help			prints this information " << std::endl;
			std::cout << "exit			exists the program " << std::endl;
		}
		else if (input == "exit")
		{
			std::cout << "Exiting program!" << std::endl;
			return 1;
			flag = false;
		}
	} while (flag);
    return 0;
}

