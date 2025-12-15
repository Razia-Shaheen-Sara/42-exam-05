#pragma once

#include "searchable_bag.hpp"
#include "tree_bag.hpp"

class searchable_tree_bag : public tree_bag, public searchable_bag
{
	private:
	bool search(node* node, int value)const;
	
	public:
	searchable_tree_bag();
	searchable_tree_bag(const searchable_tree_bag& source);
	searchable_tree_bag& operator=(const searchable_tree_bag& source);
	bool has(int)const;////copied from searchable_bag.hpp
	~searchable_tree_bag();
};