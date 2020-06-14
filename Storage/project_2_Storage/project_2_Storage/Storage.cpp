#include "stdafx.h"
#include "Storage.h"
#include<fstream>


Storage::Storage()
{
	this->volume = 0;
}

//! sets the colume and creates the places in the storage
void Storage::set_volume(int volume)
{
	this->volume = volume;
	this->generate_places();
}

//! prints the products on the console
void Storage::print()
{
	Command currentCommand("print", this->get_currentDate());
	this->commands.push_back(currentCommand);

	for (int i = 0; i < this->places.size(); i++)
	{
		std::vector<Product> current_products = this->places[i].get_products();
		for (int j = 0; j < current_products.size(); j++)
		{
			std::cout << "Product: " << current_products[j].get_name() << std::endl;
			std::cout << "Expiration date: " << current_products[j].get_expirationDate().get_day()
				<< "/" << current_products[j].get_expirationDate().get_month()
				<< "/" << current_products[j].get_expirationDate().get_year() << std::endl;
			if (current_products[j].get_unit())
			{
				std::cout << "Unit: kilograms" << std::endl;
			}
			else
			{
				std::cout << "Unit: liters" << std::endl;
			}
			std::cout << "Qantity: " << current_products[j].get_quantity() << std::endl;
			std::cout << "Note: " << current_products[j].get_note() << std::endl;
			std::cout << std::endl;
		}
	}

}
//! adds a product in the storage
void Storage::add(const Product &product)
{
	Command currentCommand("add", this->get_currentDate());
	this->commands.push_back(currentCommand);

	bool flag = true;

	for (size_t i = 0; i < this->places.size(); i++)
	{
		std::vector<Product> current_products = this->places[i].get_products();
		for (size_t j = 0; j < current_products.size(); j++)
		{
			if (current_products[j].get_name() == product.get_name() 
				&& (this->places[i].get_current_volume() + product.get_volume()) <= this->places[i].get_volume())
			{
				if (current_products[j].get_expirationDate() == product.get_expirationDate())
				{
					current_products[j].set_quantity(current_products[j].get_quantity() + product.get_quantity());
					this->places[i].set_products(current_products);
					flag = false;
				}
				else
				{
					for (size_t i = 0; i < this->places.size(); i++)
					{
						if (product.get_volume() <= this->places[i].get_volume()
							&& this->places[i].get_current_volume() + product.get_volume() <= this->places[i].get_volume())
						{
							this->places[i].add_product(product);
							break;
						}
					}
					flag = false;
				}
			}
		}
	}

	for (size_t i = 0; i < this->places.size() && flag; i++)
	{
		if (product.get_volume() <= this->places[i].get_volume()
			&& this->places[i].get_current_volume() + product.get_volume() <= this->places[i].get_volume())
		{
			this->places[i].add_product(product);
			break;
		}
	}
}
//! removes a product from the storage 
void Storage::remove(const std::string &name, int quantity)
{
	Command currentCommand("remove", this->get_currentDate());
	this->commands.push_back(currentCommand);

	std::vector<Product> current_products_remove;
	for (size_t i = 0; i < this->places.size(); i++)
	{
		std::vector<Product> current_products = this->places[i].get_products();
		for (size_t j = 0; j < current_products.size(); j++)
		{
			if (current_products[j].get_name() == name)
			{
				current_products_remove.push_back(current_products[j]);
				this->places[i].set_current_volume(this->places[i].get_current_volume() - current_products[j].get_volume());
				current_products.erase(current_products.begin() + j);
				this->places[i].set_products(current_products);
			}
		}
	}


	if (current_products_remove.size() > 1)
	{
		Date min_date = current_products_remove[0].get_expirationDate();
		int min_index = 0;
		for (size_t i = 0; i < current_products_remove.size(); i++)
		{
			if (current_products_remove[0].get_expirationDate() < min_date)
			{
				min_date = current_products_remove[0].get_expirationDate();
				min_index = i;
			}
		}

		current_products_remove.erase(current_products_remove.begin() + (min_index - 1));
	}
	else if (current_products_remove.size() == 0)
	{
		std::cout << "No such product!" << std::endl;
	}
	else
	{
		if (current_products_remove[0].get_quantity() < quantity)
		{
			std::cout << "Quantity exceeds stock!" << std::endl;
		}
		else
		{
			if (current_products_remove[0].get_quantity() == quantity)
			{
				current_products_remove.pop_back();
			}
			else if (current_products_remove[0].get_quantity() > quantity)
			{
				current_products_remove[0].set_quantity(current_products_remove[0].get_quantity() - quantity);
			}
			else
			{
				std::cout << "Quantity exceeds stock!" << std::endl;
			}
		}
	}

	for (int i = 0; i < current_products_remove.size(); i++)
	{
		this->add(current_products_remove[i]);
	}
}
//! print commands in a given period on the console
void Storage::log(const Date &from, const Date &to)
{
	std::cout << "Commands: " << std::endl;
	for (Command command : commands)
	{
		Date commandDate = command.get_date();
		if (commandDate >= from && commandDate <= to)
		{
			std::cout << command.get_command() << std::endl;
		}
	}
	std::cout << std::endl;
}
//! cleans expired products
void Storage::clean(const Date &date)
{
	Command currentCommand("clean", this->get_currentDate());
	this->commands.push_back(currentCommand);

	std::cout << "Expired products: " << std::endl;
	for (size_t i = 0; i < this->places.size(); i++)
	{
		std::vector<Product> current_products = this->places[i].get_products();
		for (size_t j = 0; j < current_products.size(); j++)
		{
			Date productExpirationDate = current_products[j].get_expirationDate();
			if (productExpirationDate >= date || (this->daysBetweenTwoDates(productExpirationDate, date) < 3))
			{
				std::cout << current_products[j].get_name() << " has expired!" << std::endl;
				current_products.erase(current_products.begin() + j);
				this->places[i].set_products(current_products);
			}
		}
	}
}

//! prints storare on file 
void Storage::print_on_file(std::ofstream &file)
{
	file << this->volume << std::endl;
	for (int i = 0; i < this->places.size(); i++)
	{
		std::vector<Product> current_products = this->places[i].get_products();
		for (int j = 0; j < current_products.size(); j++)
		{
			file << "Product: " << current_products[j].get_name() << std::endl;
			file << "Expiration date: " << current_products[j].get_expirationDate().get_day()
				<< "/" << current_products[j].get_expirationDate().get_month()
				<< "/" << current_products[j].get_expirationDate().get_year() << std::endl;
			if (current_products[j].get_unit())
			{
				file << "Unit: kilograms" << std::endl;
			}
			else
			{
				file << "Unit: liters" << std::endl;
			}
			file << "Qantity: " << current_products[j].get_quantity() << std::endl;
			file << "Note: " << current_products[j].get_note() << std::endl;
			file << std::endl;
		}
	}

}