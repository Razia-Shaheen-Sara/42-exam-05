#include "set.hpp"
#include "searchable_array_bag.hpp"
#include "searchable_tree_bag.hpp"



// Constructor: initialize the set by wrapping a concrete searchable_bag object
set::set(searchable_bag& s_bag):bag(s_bag)
{

}

bool set::has(int value)const//// Check if a value exists in the set
{
	return(bag.has(value));//Calls the 'has' function of the referenced searchable_bag (or its derived class)
}

void set::insert(int value)// Insert a single value into the set if not already present
{
	if(!(this->has(value)))
		bag.insert(value);//call insert from derived class or wraped obj
}

void set::insert(int *array, int size)//insert an array of values
{
	for (int i = 0; i < size; i++)
	{
		this->insert(array[i]);
	}
}
//print all elements of the set
void set::print() const 
{
	bag.print(); //coming from bag.hpp
}
//clear
void set::clear()
{
	bag.clear(); //coming from bag.hpp
}
// Return a reference to the wrapped searchable_bag
const searchable_bag& set::get_bag()
{
	return (this->bag);
}
set::~set()
{

}