#include "bigint.hpp"
#include <sstream>
#include <string>

bigint::bigint()
{
    this->str = "0"; //initializing to literal zero
}

bigint::bigint(unsigned int num)
{
    std::stringstream ss; //initialize a ss
    ss << num; //write the number in the stream (<< means write, >> means read)
    this-> str = ss.str(); // get the contents of the stream as a std::string
}

bigint::bigint(const bigint& src)
{
    this->str = src.str; //copy constructor, copies MEMBERS directly
}

std::string bigint::getStr() const
{
    return(this->str);
}

std::ostream& operator<<(std::ostream& output, const bigint& obj)
{
    output << obj.getStr(); //writing the string of the object to the output stream.
    return(output);
}

bigint& bigint::operator=(const bigint& source)
{
   this->str = source.str;//is it copying member?
   return (*this); //"this" is always a pointer to the object whose member function is running.
                    //we dereference it and return the actual object
}

std::string reverse(const std::string& str)
{
    std::string revStr;
    for(size_t i = str.length(); i > 0; i--)
    {
        revStr.push_back(str[i - 1]); //push_back appends a char at the end of a str
    }
    return(revStr);
}


std::string addition(const bigint& obj1, const bigint& obj2)
{
    std::string result_str;
    std::string revStr1 = reverse(obj1.getStr()); //"942" → "249"
    std::string revStr2 = reverse(obj2.getStr()); // "18"  → "81"
    size_t len1 = revStr1.length();
    size_t len2 = revStr2.length();
    if (len1 > len2)
    {
        int diff = len1 - len2;
        while (diff > 0)
        {
            revStr2.push_back('0'); //81 → 810
            diff--;
        } 
    }
    else if (len2 > len1)
    {
        int diff = len2 - len1;
        while (diff > 0)
        {
            revStr1.push_back('0');
            diff--;
        }
    }
    int carry = 0;
    int digit1;
    int digit2;
    size_t len = revStr1.length(); //both strings are now equal length
    for (size_t i = 0; i < len; i++)//iterate till reaches length
    {
        digit1 = revStr1[i] - '0';//keep converting to int
        digit2 = revStr2[i] - '0';
        int total = digit1 + digit2 + carry; //basic addition //7+8+0 = 15
        if (total > 9)// if it is bigger than 9, carry the first and write the rest to string
        {
            carry = total/10; //15/10 = 1; so carry 1
            result_str.push_back((total % 10) + '0'); //15 % 10 = 5 so add 5 to the string
        }
        else
            result_str.push_back(total + '0');
    } //for loop ends here
    if (carry != 0) //if carry is not 0 at the end of for loop
        result_str.push_back(carry + '0');
    return (reverse(result_str));
}

bigint bigint::operator+(const bigint& other)const
{
    std::string result = addition(*this, other); //make a string to hold sum result
    bigint temp; //make a new bigint that is empty
    temp.str = result; //put the result in there
    return (temp);   //return
}

bigint& bigint::operator+=(const bigint& other)
{
    (*this) = (*this) + other;
    return(*this);
}

bigint& bigint::operator++()
{
    *this= *this + bigint(1);
    return(*this);
}

bigint bigint::operator++(int)
{
    bigint temp = *this; //save the old value
    *this = *this + bigint(1); //increment
    return(temp); //return the old value
}

//for decimal bigints, left-shift (<< n) means multiply by 10ⁿ, 
// which is simply adding n zeros at the end of the string.

bigint bigint::operator<<(unsigned int n) const
{
    bigint temp = *this;
    temp.str.insert(temp.str.end(), n, '0');//insert(position, count, character)
    return(temp);
}


bigint& bigint::operator<<=(unsigned int n)
{
    *this = (*this) << n;
    return (*this);
}

bigint bigint::operator>>(unsigned int n) const
{
    bigint temp = *this;
    size_t len = temp.str.length();
    if (n >= len)
        temp.str = "0";//right-shift a decimal number by more digits than it's, the result is always literal 0
    else
        temp.str.erase(len - n, n);//just cut digit from the back; erase(start_index, count)
    return (temp);
}

bigint& bigint::operator>>=(unsigned int n)
{
    *this = *this >> n;
    return (*this);
}

unsigned int stringToUnit(std::string str)
{
    unsigned int num;
    std::stringstream ss(str);
    ss >> num; //READ INTO NUM that also converts ans stores as a int
    return (num);
}

bigint bigint::operator<<(const bigint& second) const
{
    bigint temp;
    temp = (*this) << stringToUnit(second.str);
    return (temp);
}

bigint bigint::operator>>(const bigint& second)const
{
    bigint temp;
    temp = *this >> stringToUnit(second.str);
    return(temp);
}

bigint& bigint::operator<<=(const bigint& second)
{
    *this = *this << stringToUnit(second.str);
    return(*this);
}

bigint& bigint::operator>>=(const bigint& second)
{
    *this = *this >> stringToUnit(second.str);
    return(*this);
}

bool bigint::operator==(const bigint& other) const
{
    if (this->str == other.str)
        return(true);
    return (false);
}

bool bigint::operator!=(const bigint& other) const
{
    if (*this == other)
        return(false);
    return(true);
}

bool bigint::operator<(const bigint& other) const
{
    std::string str1 = this->str;
    std::string str2 = other.str;
    size_t len1 = str1.length();
    size_t len2 = str2.length();
    if (len1 != len2)
        return (len1 < len2);
    return(str1 < str2);
}

bool bigint::operator>(const bigint& other) const
{
    if (*this < other)
        return (false);
    return (true);
}

bool bigint::operator<=(const bigint& other) const
{
    if (*this < other)
        return (true);
    if (*this == other)
        return (true);
    return (false);
}

bool bigint::operator>=(const bigint& other) const
{
    if (*this > other)
        return(true);
    if (*this == other)
        return (true);
    return (false);
}

