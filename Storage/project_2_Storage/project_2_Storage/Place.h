#pragma once
#include<vector>
#include"Product.h"
#include"Date.h"
/*! \class Place
\brief Class which defines a Place
*/
class Place
{
private:
	int section; 	
	int shelf;
	int number; 

	int volume; 
	int current_volume; 

	std::vector<Product> products; 
public:
	Place();
	Place(int section, int shelf, int number);

	int get_section() const;
	int get_shelf() const;
	int get_number() const;
	int get_volume() const;
	int get_current_volume() const;
	std::vector<Product> get_products() const;

	void set_section(int section);
	void set_shelf(int shelf);
	void set_number(int number);
	void set_volume(int volume);
	void set_current_volume(int volume);
	void set_products(std::vector<Product> products);

	//! добавя продукт 
	void add_product(Product pr);

};

