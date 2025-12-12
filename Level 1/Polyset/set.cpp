#include "set.hpp"
#include "searchable_array_bag.hpp"

set::set(searchable_bag& s_bag):bag(s_bag) // Initializes set's private member 'bag' with the given searchable_bag
{

}

bool set::(int)const
{
	return(bag.has(value));//Calls the 'has' function of the referenced searchable_bag (or its derived class)
}

void set::insert(int value)
{
	if(!(this->has(value)))
		bag.insert(value);
}

void set::insert(int *array, int size)
{
	for (int i = 0; i < size; i++)
	{
		this->insert(data[i]);
	}
}
void set::print() const 
{
	bag.print(); //coming from bag.hpp
}
void set::clear()
{
	bag.clear(); //coming from bag.hpp
}
const searchable_bag& set::get_bag()
{
	return (this->bag);
}
set::~set()
{

}