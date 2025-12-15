#include "vect2.hpp"
#include <iostream>

int main()
{
    
    //given test
    vect2 v1; // 0, 0
	vect2 v2(1, 2); // 1, 2
	const vect2 v3(v2); // 1, 2
	vect2 v4 = v2; // 1, 2

	std::cout << "v1: " << v1 << std::endl;
	std::cout << "v1: " << "{" << v1[0] << ", " << v1[1] << "}" << std::endl;
	std::cout << "v2: " << v2 << std::endl;
	std::cout << "v3: " << v3 << std::endl;
	std::cout << "v4: " << v4 << std::endl;
	std::cout << v4++ << std::endl; // 2, 3
	std::cout << ++v4 << std::endl; // 3, 4
	std::cout << v4-- << std::endl; // 2, 3
	std::cout << --v4 << std::endl; // 1, 2

	v2 += v3; // 2, 4
	v1 -= v2; // -2, -4
	v2 = v3 + v3 *2; // 3, 6 means vect2*int
	v2 = 3 * v2; // 9, 18 means different NON MEMBER: int*vect2
	v2 += v2 += v3; // 20, 40
	v1 *= 42; // -84, -168 
	v1 = v1 - v1 + v1;

	std::cout << "v1: " << v1 << std::endl;
	std::cout << "v2: " << v2 << std::endl;
	std::cout << "-v2: " << -v2 << std::endl;
	std::cout << "v1[1]: " << v1[1] << std::endl;
	v1[1] = 12; //ONLY THIS LINE REQUIRES [] to return int&
	std::cout << "v1[1]: " << v1[1] << std::endl;
	std::cout << "v3[1]: " << v3[1] << std::endl;
	std::cout << "v1 == v3: " << (v1 == v3) << std::endl;
	std::cout << "v1 == v1: " << (v1 == v1) << std::endl;
	std::cout << "v1 != v3: " << (v1 != v3) << std::endl;
	std::cout << "v1 != v1: " << (v1 != v1) << std::endl;

   
    //EXTRA: 
    // std::cout << "v4: " << v4 << std::endl; // prefix increments v4 → prints {2, 3}
    // std::cout << "prefix" << ++v4 << std::endl; // prefix increments v4 → prints {2, 3}
    // std::cout << "v4: " << v4 << std::endl; // v4 after prefix → {2, 3}
    // std::cout <<"postfix:"<< v4++ << std::endl; //// postfix prints current v4 → {2, 3}, then increments
    // std::cout << "v4: " << v4 << std::endl;  // v4 after postfix → {3, 4}
    // std::cout << --v4 << std::endl; // 2,3
    // std::cout << v4-- << std::endl; // 2,3
    // std::cout << "v4: " << v4 << std::endl; //1,2

    //addition test
    // vect2 v10 = v2 += v3; // 2, 4
    // std::cout << "v10:(expect: 2,4) " << v10 << std::endl;
    // std::cout << "v2:(expect: 2,4) " << v2 << std::endl;
     // Reset v2 for subtraction tests
    //  v2 = vect2(2,4);       // {2,4} v3=(1,2)
    //  // Test operator-
    //  vect2 v11 = v2 - v3;    // creates new object {1,2}, v2 unchanged
    //  std::cout << "v11 (v2-v3, expect: 1,2): " << v11 << std::endl;
    //  std::cout << "v2  (expect unchanged 2,4): " << v2 << std::endl;
 
    //  // Test operator-=
    //  v2 -= v3;               // modifies v2 in-place {1,2}
    //  std::cout << "v2 after v2-=v3 (expect: 1,2): " << v2 << std::endl;

     
    // //multiplication
    // vect2 a(1,2);
    // // 1️⃣ Member: vect2 * int → should return new vect2 (by value)
    //  vect2 b = a * 3;  
    //  std::cout << "b (a*3): " << b << std::endl;
    //  std::cout << "a " << a << std::endl;
 
    //  // 2️⃣ Member: vect2 *= int → should return reference
    // vect2 c(1,2);
    // c *= 3;  // just test if *= works
    // std::cout << "c after *= 3: " << c << std::endl;
    //  // 3️⃣ Non-member: int * vect2 → should return new vect2 (by value)
    //  vect2 d = 3 * a;
    //  std::cout << "d (3*a): " << d << std::endl;


}
