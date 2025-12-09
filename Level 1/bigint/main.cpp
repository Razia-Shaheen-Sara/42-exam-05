#include "bigint.hpp"

int main()
{
    const bigint a(42);
    bigint b(21), c, d(1337), e(d);

    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "c = " << c << std::endl;
    std::cout << "d = " << d << std::endl;
    std::cout << "e = " << e << std::endl;

    // c = b;

    // std::cout << "after assignment c = " << c <<std::endl;

    std::cout << "a + b = " << a + b << std::endl;
    std::cout << "(c += a) = " << (c += a) << std::endl;

    std::cout << "b = " << b << std::endl;
    std::cout << "++b = " << ++b << std::endl;
    std::cout <<"b current val :" << b <<std::endl;
    std::cout << "b++ = " << b++ << std::endl;
    std::cout <<"b current val :" << b <<std::endl;
    

    std::cout << "(b << 10) + 42 = " << ((b << 10) + 42) << std::endl;
    std::cout << "b = " << b << std::endl; //b will not change
    std::cout << "d = " << d << std::endl; 
    std::cout << "(d <<= 4) = " << (d <<= 4) << std::endl; //due to = sign, d will change
    std::cout << "d = " << d << std::endl;
    std::cout << "(e >> 2) = " << (e >> 2) << std::endl;
    std::cout << "e = " << e << std::endl;
    std::cout << "(e >> 4) = " << (e >> 4) << std::endl;
    std::cout << "e = " << e << std::endl;
    std::cout << "(e >>= 3) = " << (e >>= 3) << std::endl;
    std::cout << "e = " << e << std::endl;
    std::cout << "(d >>= 2) = " << (d >>= (const bigint)2) << std::endl;

    std::cout << "a =" << a << std::endl;
    std::cout << "d =" << d << std::endl;

    std::cout << "(d < a) = " << (d < a) << std::endl;
    std::cout << "(d <= a) = " << (d <= a) << std::endl;
    std::cout << "(d > a) = " << (d > a) << std::endl;
    std::cout << "(d >= a) = " << (d >= a) << std::endl;
    std::cout << "(d == a) = " << (d == a) << std::endl;
    std::cout << "(d != a) = " << (d != a) << std::endl;
}