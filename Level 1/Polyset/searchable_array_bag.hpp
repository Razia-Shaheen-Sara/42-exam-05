#pragma once

#include "array_bag.hpp"
#include "searchable_bag.hpp"

class searchable_array_bag : public array_bag, public searchable_bag
{
	public:
	searchable_array_bag();
	searchable_array_bag(const searchable_array_bag& source); //copy constructor
	searchable_array_bag& operator=(const searchable_array_bag& source); //assignment operator
	bool has(int) const;//copied from searchable_bag.hpp
	~searchable_array_bag();
};