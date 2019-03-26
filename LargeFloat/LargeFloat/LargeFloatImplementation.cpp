#include "pch.h"
#include "LargeFloatImplementation.h"

#include <string.h>
#include <cmath>
#include <iostream>




LargeFloat::LargeFloat(double value = 0.0) {
	// sign
	if (value >= 0) {
		this->sign = 0;
	}
	else { this->sign = 1; }
	//exponent
	int valueExponent;
	double valueSignificant;
	valueSignificant = frexp(value, &valueExponent);
	std::cout << "The exponent is: " <<valueExponent<< std::endl;
	std::cout << "The significant is: " << valueSignificant <<std::endl;
	--valueExponent;
	this->exponent = valueExponent;



	// the number is represented in a way to be copied bitwise
	valueSignificant = valueSignificant * 2;
	//std::cout << "The Value significant is : " << valueSignificant << std::endl;
	valueSignificant = valueSignificant -1;
	//std::cout << "The Value significant is : " << valueSignificant << std::endl;
	for (int i = 0;i < 5;++i)
	{
		this->significant[i] = 0;
	}



	doubleBitRepresentation bitValueSignificant;
	bitValueSignificant.doubleValue = valueSignificant;

	for (int i = 0;i < 40;++i) {
		int doubleArrayPosition = (i + 12) / 8; // first 12 bits are for sign + exp
		int doubleBitPosition = (i + 12) % 8;
		unsigned char doubleBitMask = (1u << doubleBitPosition);
		bool positionInDoubleIsSet = (bitValueSignificant.bitRepresentation[doubleArrayPosition] & doubleBitMask) != 0;





		if (positionInDoubleIsSet) {
			int LargeFloatArrayPosition = i / 8;
			int LargeFloatBitPosition = i / 8;
			unsigned char bitMask = (1u << LargeFloatBitPosition);
			this->significant[LargeFloatArrayPosition] = this->significant[LargeFloatArrayPosition] | bitMask;
		}
	}


	

	




}

std::ostream& operator<<(std::ostream& stream, const LargeFloat& value) {

	double significantValue = 1; // implicit first bit
	double radixPart = 0.0;
	for (int i = 0;i < 5;++i) {
		//std::cout << "Outer cycle number " << i << std::endl;
		for (int j = 0;j < 8;++j) {
			unsigned char bitMask = (1u << j);


			unsigned char val = value.significant[i] & bitMask;
			bool booleanVal = val;


			int power = -(i * 8 + j + 1);
			//std::cout << "For positions " << i << " , " << j << " the power is " << power 
			//												 << "and the val is " << booleanVal << std::endl;
			double addition = pow(2, power);
			//std::cout << "addition = " << addition << std::endl;
			significantValue += addition * booleanVal;
		}
		//std::cout << "Outer cycle number " << i << " the value is : " << significantValue << std::endl;
	}
	significantValue *= pow(2, value.exponent);
	if (bool(value.sign) == 1) {

		significantValue *= -1;
	}

	stream << significantValue;
	return stream;
}
LargeFloat operator+(const LargeFloat& a, const LargeFloat& b)
{
	LargeFloat answer;
	return answer;
}
