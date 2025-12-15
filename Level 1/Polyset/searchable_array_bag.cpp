#include "searchable_array_bag.hpp"
#include "searchable_tree_bag.hpp"


searchable_array_bag::searchable_array_bag()
{}


//call base class copy const.
searchable_array_bag::searchable_array_bag(const searchable_array_bag& source):array_bag(source)//one :
{

}

searchable_array_bag& searchable_array_bag::operator=(const searchable_array_bag& source)
{
	if (this!= &source)//self check essential because of complex struct
		array_bag::operator=(source);//call base class assignment operator// 
	return (*this);
	
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
{}
