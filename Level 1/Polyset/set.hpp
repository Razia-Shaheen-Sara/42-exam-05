#pragma once
#include "searchable_bag.hpp"

//inheritance = “is-a”vs  composition/wrap = “has-a”

class set
{
	private:
		searchable_bag& bag;//bag is from searchable_bag.hpp
	public:
		set() = delete;
		set(const set& source) = delete;
		set& operator=(const set& source) = delete;//these not allowed why?

		set(searchable_bag& s_bag);//constructor taking existing searchable_bag reference (from searchable_bag.hpp)

		// all the below functions are **delegated to the wrapped concrete object** implemented in 
		bool has(int) const;//// declared in searchable_bag (pure virtual)
		void insert(int); //copy from array_bag
  		void insert(int *array, int size);//same
 		void print() const;//same
  		void clear();//same

		const searchable_bag& get_bag();

		~set();
};