#ifndef VECT2_HPP
#define VECT2_HPP

#include <iostream>

class vect2
{
    private:
    int x;
    int y;
    
    public:
    vect2(); 
    vect2(int num1, int num2); //parameterized constructor
    vect2(const vect2& source); //copy constructor
    vect2& operator=(const vect2& source); //assignment operator
    //subscription operator
    int& operator[](int index);
    int operator[](int index)const;//subscript operator const version
    //increments decreaments
    vect2& operator++(); //prefix
    vect2 operator++(int); //postfix
    vect2& operator--();
    vect2 operator--(int);

    //addition
    vect2 operator+(const vect2& other)const;
    vect2& operator+=(const vect2& other);
    //subs
    vect2 operator-(const vect2& other)const;
    vect2& operator-=(const vect2& other);

    //unari minus
    vect2 operator-()const;

    //mult (vect2*int) (vect2*=int) (NON MEMBER! int*vect2)
    vect2 operator*(int num) const;
    vect2& operator*=(int num);

    bool operator==(const vect2& obj)const;
    bool operator!=(const vect2& obj)const;


    ~vect2();

};

std::ostream& operator<<(std::ostream& output, const vect2& v); 

vect2 operator*(int n, const vect2& obj);

#endif