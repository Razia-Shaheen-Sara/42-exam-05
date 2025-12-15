//orders to implement and test quickly:
//1. constructors and destructors
//2. operator[] (both const & non-const)
//3. stream operator<< (start testing immediately)
//4. increments & decreaments coz no use of operators
//rest

//object + object means addition operator
//member + member means regular built in plus

#include "vect2.hpp"
#include <iostream>

vect2::vect2()
{
    this->x = 0;
    this->y = 0; //set them to number 0 coz themself int
}

vect2::vect2(int num1, int num2)
{
    this->x = num1;
    this->y = num2;
}

int vect2::operator[](int index)const //basically hard code who is first and who is second
{
    if (index == 0)
        return (this->x);
    else
        return (this->y);
}

std::ostream& operator<<(std::ostream& output, const vect2& v) //Dont write const here
{
   output << "{" << v[0] << ", " << v[1] << "}" << std::endl;//copy from subject-- we need index operator
   return (output);
}
//because operator<< receives a const vect2, it can only call the const version of operator[]

vect2::~vect2()
{

}

vect2::vect2(const vect2& source) //copy const
{
    //    *this = source;  // ❌ THIS IS INFINITE RECURSION
    //copy members directly
    this->x = source.x;
    this->y = source.y;
}

vect2& vect2::operator=(const vect2& source)
{
    //    *this = source;  // ❌ THIS IS INFINITE RECURSION
    this->x = source.x;
    this->y = source.y;
    return (*this);
}

vect2& vect2::operator++() //prefix //KISS
{
    x+=1;
    y+=1;
    return (*this);
}

vect2 vect2::operator++(int) //postfix, should return old value but increase itself
{
    vect2 temp = *this;//save old value
    x+=1;//increase actual object
    y+=1;
    return (temp);//return old value
}

vect2& vect2::operator--()
{
    x-=1;
    y-=1;
    return (*this);
}

vect2 vect2::operator--(int)
{
    vect2 temp = *this;
    x-=1;
    y-=1;
    return (temp);
}

vect2 vect2::operator+(const vect2& other)const 
{
    vect2 temp = *this;
    temp.x = this->x + other.x; //member by member
    temp.y = this->y + other.y;
    return (temp);
}

vect2& vect2::operator+=(const vect2& other)
{
    *this = *this + other;
    return (*this);
}

vect2 vect2::operator-(const vect2& other)const 
{
    vect2 temp = *this;
    temp.x = this->x - other.x; //member by member
    temp.y = this->y - other.y;
    return (temp);
}

vect2& vect2::operator-=(const vect2& other)
{
    *this = *this - other;
    return (*this);
}

//vect2*int
vect2 vect2::operator*(int n)const
{
    vect2 temp = *this;
    temp.x = this->x * n;
    temp.y = this->y * n;
    return (temp);

}

vect2& vect2::operator*=(int n)
{
    this->x *= n;
    this->y *= n;
    return (*this);
}

bool vect2::operator==(const vect2& obj) const
{
    if ((this->x == obj.x) && (this->y == obj.y))
        return (true);
    else
        return (false);
}

bool vect2::operator!=(const vect2& obj) const
{
    if (*this == obj)
        return (false);
    else
        return (true);
}

//non member mult (int* vect2)
vect2 operator*(int n, const vect2& obj)
{
    return (obj * n);
}

int& vect2::operator[](int index)
{
    if (index == 0)
        return (this->x);
    else
        return (this->y);
}




//No argument
//Negates this vector itself
//Returns a new vect2
//Does not modify the object
vect2 vect2::operator-()const
{
    return (vect2(-x, -y));
}

