#ifndef vect2.hpp
#define vect2.hpp

#include <iostream>

class vect2
{
    private:
    int x;
    int y;
    
    
    public:
    vect2();
    vect2(int num1, int num2);
    vect2(const vect2& source);
    vect2& operator=(const vect2& source);

    vect2 operator+(const vect2& other)const;
    vect2 operator-(const vect2& other)const;
    vect2 operator*(const vect2& other)const;
    ~vect2;

};

std::ostream& operator<<(std::ostream& output, const vect2 obj)const; 

#endif