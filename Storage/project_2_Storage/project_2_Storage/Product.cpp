#include "stdafx.h"
#include "Product.h"


Product::Product()
{
	Date defaultDate;

	this->name = "";
	this->expirationDate = defaultDate;
	this->goesInStorage = defaultDate;
	this->manufacturer = "";
	this->unit = false;
	this->volume = 1;
	this->note = "";
}
Product::Product(const std::string name, const Date expirationDate, const Date goesInStorage,
	const std::string manufacturer, bool unit, int volume,
	const std::string note, int quantity)
{
	this->name = name;
	this->expirationDate = expirationDate;
	this->goesInStorage = goesInStorage;
	this->manufacturer = manufacturer;
	this->unit = unit;
	this->volume = volume;
	this->note = note;
	this->quantity = quantity;
}

std::string Product::get_name() const
{
	return this->name;
}
Date Product::get_expirationDate() const
{
	return this->expirationDate;
}
Date Product::get_goesInStorage() const
{
	return this->goesInStorage;
}
std::string Product::get_manufacturer() const
{
	return this->manufacturer;
}
bool Product::get_unit() const
{
	return this->unit;
}
int Product::get_volume() const
{
	return this->volume;
}
std::string Product::get_note() const
{
	return this->note;
}
int Product::get_quantity() const
{
	return this->quantity;
}

void Product::set_name(const std::string name)
{
	this->name = name;
}
void Product::set_expirationDate(const Date expirationDate)
{
	this->expirationDate = expirationDate;
}
void Product::set_goesInStorage(const Date goesInStorage)
{
	this->goesInStorage = goesInStorage;
}
void Product::set_manufacurer(const std::string manufactorer)
{
	this->manufacturer = manufactorer;
}
void Product::set_unit(bool unit)
{
	this->unit = unit;
}
void Product::set_volume(int volume)
{
	this->volume = volume;
}
void Product::set_note(const std::string note)
{
	this->note = note;
}
void Product::set_quantity(int quantity)
{
	this->quantity = quantity;
}

//! increases quantity on the product
void Product::increaseQuantity(int otherQuantity)
{
	this->quantity += otherQuantity;
}
