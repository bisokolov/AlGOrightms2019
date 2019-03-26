#pragma once
#include<iostream>

union doubleBitRepresentation
{
	double doubleValue;
	unsigned char bitRepresentation[sizeof(double)];
};



class  LargeFloat {
public:

	LargeFloat(double);
	friend std::ostream& operator<<(std::ostream&, const LargeFloat&);
	friend LargeFloat operator+(const LargeFloat&, const LargeFloat&);


	//private:
	char sign : 1;
	char exponent : 7;
	char significant[5];
};
