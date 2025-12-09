#ifndef BIGINT_HPP
#define BIGINT_HPP
#include <iostream>

class bigint
{
    private:
        std::string str; //store number as string
        std::string result;
    public:
        bigint();
        bigint(unsigned int num); //from subject - not const; const mstters when passing by ref or passing a complex object
        bigint(const bigint &source);//copy constructor- pass the object(not int) by ref; so it is const, sending without ref will need a copy!

        //assignment
        bigint& operator=(const bigint& source);
        // // Copies the value from source (right-hand side) to first (left-hand side) and returns a reference to first

        // //addition
         bigint operator+(const bigint& other) const; 
        // // Returns a new bigint that is the sum of first (this object) and second (argument); first is not modified
        bigint& operator+=(const bigint& other); //Adds second to first, modifies first, and returns a reference to first
        
        // //increment
        bigint& operator++(); // Prefix ++ : increments first, modifies first, and returns a reference to first
        bigint operator++(int); //// Postfix ++ : returns a copy of first before incrementing; first is then incremented

        // //digit shift with unsigned int
        bigint  operator<<(unsigned int n) const;
        // // Returns a new bigint where first is shifted left by n digits; first is not modified
        bigint  operator>>(unsigned int n)  const;
        // // Returns a new bigint where first is shifted right by n digits; first is not modified
        bigint& operator<<=(unsigned int n);
        // // Shifts first left by n digits, modifies first, and returns a reference to first
        bigint& operator>>=(unsigned int n);
        // // Shifts first right by n digits, modifies first, and returns a reference to first

        // //digit shift with object
        bigint operator<<(const bigint &second) const;
        bigint operator>>(const bigint &second) const;
        bigint &operator<<=(const bigint &second);
        bigint &operator>>=(const bigint &second);

        // //comparisons
        bool operator==(const bigint &second) const;
        bool operator!=(const bigint &second) const;
        bool operator<(const bigint &second) const;
        bool operator>(const bigint &second) const;
        bool operator>=(const bigint &second) const;
        bool operator<=(const bigint &second) const;

        // //If you wrote bigint other (by value)-- 

        // //when assining- no const because you are literally changing the first parameter, Also- 
        // //ALWAYS returns a reference to the first one every time = sign is used
        
        std::string getStr()const; //for debugging. getters should not modify objects so it is const
        
        // ~bigint();
};

std::ostream& operator<<(std::ostream& output, const bigint& obj);

#endif


//Return value in C++:
//Everything before the function name (operator++) is the return type.
//bigint operator+(const bigint &other) const; // returns a new BigInt
//bigint &operator+=(const bigint &other);     // returns a reference to the modified object
//bool operator<(const bigint &other) const;   // returns true/false


//why need copy constructor?
//If your class stores dynamic memory (like a char*, int*, or your own allocated buffer), you must define how to copy that memory safely.
//Otherwise both objects would point to the same internal memory.
//So the copy constructor’s job is:
//allocate new memory for the new object
//copy the content from the source object
//avoid sharing pointer


//assignment operator example
//BigInt a(10);
//BigInt b;
//b = a;       // this calls operator=

//addition operator example
//BigInt a(12);
//BigInt b(30);
//BigInt c = a + b;   // this calls operator+

//
//Cannot use "const" at the end:
//example: bigint &operator=(const bigint &source);
// parameter is const because you don't modify the source
// function is NOT const because operator= must modify the object (left side)

//
// Use of "const":
// bigint operator+(const bigint &other) const;
// (const bigint &other)  -> cannot modify the received parameter inside the function
// ... ) const            -> will not modify the object the function is called on

//Things to remember for exam:
//object passed operator(here) = 13
//equal signs with operator (<<=, +=) will return reference
//reference retrurn = 7
//const = 11