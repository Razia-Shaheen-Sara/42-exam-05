#include "searchable_tree_bag.hpp"

searchable_tree_bag::searchable_tree_bag()
{

}

searchable_tree_bag::searchable_tree_bag(const searchable_tree_bag& source):tree_bag(source)
{

}

searchable_array_bag& searchable_array_bag::operator=(const searchable_tree_bag& source)
{
	tree_bag::operator = source; //call the ebase class operator
	return (*this);
}

bool searchable_tree_bag::search(const node* node, int value)
{
	if (node == nullptr)
		return (false);
	if (node->value == value)
		return (true);
	else if (value < node->value)
		return (search(node->l, value));
	else
		return(search(node->r, value));
}

bool searchable_tree_bag::has(int value) const
{
	return(search(this->tree, value));
}

searchable_tree_bag::~searchable_tree_bag()
{
	
}