#pragma once
#include"Date.h"
#include<string>
/*! \class Product
\brief Class which defines a Product
*/
class Product
{
private:
	std::string name;
	Date expirationDate;
	Date goesInStorage;
	std::string manufacturer;
	bool unit; 
	int volume; 
	std::string note;
	int quantity; 
public:
	Product();
	Product(const std::string name, const Date expirationDate, const Date goesInStorage,
		const std::string manufacturer, bool unit, int volume,
		const std::string note, int quantity);

	std::string get_name() const;
	Date get_expirationDate() const;
	Date get_goesInStorage() const;
	std::string get_manufacturer() const;
	bool get_unit() const;
	int get_volume() const;
	std::string get_note() const;
	int get_quantity() const;

	void set_name(const std::string name);
	void set_expirationDate(const Date expirationDate);
	void set_goesInStorage(const Date goesInStorage);
	void set_manufacurer(const std::string manufactorer);
	void set_unit(bool unit);
	void set_volume(int volume);
	void set_note(const std::string note);
	void set_quantity(int quantity);

	void increaseQuantity(int otherQuantity);
};

