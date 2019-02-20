
#include <iostream>
#include <string.h>
#include <cmath>
//Борис Соколов

union doubleBitRepresentation
{
	double doubleValue;
	char bitRepresentation[sizeof(double)];
};



class  LargeFloat {
public:

	LargeFloat(double);
	friend std::ostream& operator<<(std::ostream&, const LargeFloat&);
	friend LargeFloat operator+(const LargeFloat&, const LargeFloat&);


//private:
	char sign : 1;
	char exponent : 7;
	char  significant [5];
};


LargeFloat::LargeFloat(double value = 0.0) {
	if(value >=0) {
		this->sign = 0;
	}
	else { this->sign = 1; }
	double valueSignificant;
	int valueExponent;
	valueSignificant = frexp(value, &valueExponent);
	--valueExponent;
	valueSignificant = valueSignificant * 2;
	this->exponent = valueExponent;
	valueSignificant = valueSignificant - 1;
	// the number is represented in a way to be copied bitwise
	doubleBitRepresentation bitValueSignificant;
	bitValueSignificant.doubleValue = valueSignificant;


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
			
			
			int power = - (i * 8 + j + 1);
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




int main() {
	
	LargeFloat m_value;
	m_value.sign = 0;
	m_value.exponent = 0;
	m_value.significant[0] = 255;
	m_value.significant[1] = 1;
	m_value.significant[2] = 0;
	m_value.significant[3] = 0;
	m_value.significant[4] = 0;
	std::cout << "Size of LargeFloat is : " << sizeof(m_value) << "\n";

	std::cout << m_value << std::endl;
	
	double test = 13.231;
	double signif;
	int exp;
	signif = frexp(test, &exp);

	std::cout << "The test number is : " << test << "  the exponent is : " << exp << " the significant is : " << signif << std::endl;
	std::cout << " The signif * 2 ^ exp is : " << signif*pow(2, exp) << std::endl;

	return 0;
}