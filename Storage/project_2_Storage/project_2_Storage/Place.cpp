#include "stdafx.h"
#include "Place.h"


Place::Place()
{
	this->section = 0;
	this->shelf = 0;
	this->number = 0;

	this->volume = 20;

	this->current_volume = 0;
}
Place::Place(int section, int shelf, int number)
{
	this->section = section;
	this->shelf = shelf;
	this->number = number;
	this->set_volume(20);
	this->current_volume = 0;
}

int Place::get_section() const
{
	return this->section;
}
int Place::get_shelf() const
{
	return this->shelf;
}
int Place::get_number() const
{
	return this->number;
}
int Place::get_volume() const
{
	return this->volume;
}
int Place::get_current_volume() const
{
	return this->current_volume;
}
std::vector<Product> Place::get_products() const
{
	return this->products;
}

void Place::set_section(int section)
{
	this->section = section;
}
void Place::set_shelf(int shelf)
{
	this->shelf = shelf;
}
void Place::set_number(int number)
{
	this->number = number;
}
void Place::set_volume(int volume)
{
	if (this->volume <= 20)
	{
		this->volume = volume;
	}
}
void Place::set_current_volume(int volume)
{
	this->current_volume = volume;
}
void Place::set_products(std::vector<Product> products)
{
	this->products = products;
}

//! adds a product to place
void Place::add_product(Product pr)
{
	if (this->current_volume + pr.get_volume() <= this->volume)
	{
		this->current_volume += pr.get_volume();

		products.push_back(pr);
	}
}
