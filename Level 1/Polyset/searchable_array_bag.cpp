#include "searchable_array_bag.hpp"

searchable_array_bag::searchable_array_bag()
{};


//call base class copy const.
searchable_array_bag::searchable_array_bag(const searchable_array_bag& source):array_bag(source)
{

}

searchable_array_bag& searchable_array_bag::operator=(const searchable_array_bag& source)
{
	array_bag::operator = source; // copy all members from the base class (array_bag)
	return (*this); // return the current object after assignment
}


bool searchable_array_bag::has(int n)const //checks if the int n exists or not
{
	for (int i = 0; i < this->size ; i++)//iterate through the members of array
	{
		if (this->data[i] == n)
			return (true);
	}
	return (false);//outside loop
}

searchable_array_bag::~searchable_array_bag()
{};
