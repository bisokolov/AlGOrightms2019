#include <iostream>
#include <string.h>

/* define simple structure */

/*
struct Body
{
    size_t significant : 40 ;
    size_t exponent : 6;
    size_t exponent_sign : 1;
    size_t sign : 1;
};
*/

struct MyStruct
{
    long long myInt;
    short myShort;
};
struct  LargeFloat
{
    short  significantPartOne : 16;
    short significantPartTwo : 16;
    short significantPartThree : 8;
    short exponent : 6;
    short exponent_sign : 1;
    short sign : 1;
};




int main() {
    MyStruct m_value;
	std::cout<<"Memory is "<< sizeof(m_value) ;



	return 0;
}
