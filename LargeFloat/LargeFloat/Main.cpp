
#include <iostream>
#include <string.h>
#include <cmath>
//Борис Соколов

void printbinchar(char character)
{
	char output[9];
	itoa(character, output, 2);
	printf("%s  ", output);
}

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
	char unsigned significant [5];
};


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
	--valueExponent;
	this->exponent = valueExponent;

	

	// the number is represented in a way to be copied bitwise
	valueSignificant = valueSignificant  * 2;
	valueSignificant = valueSignificant - 1;
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



		
		
		if(positionInDoubleIsSet) {
			int LargeFloatArrayPosition = i / 8;
			int LargeFloatBitPosition = i / 8;
			unsigned char bitMask = (1u << LargeFloatBitPosition);
			this->significant[LargeFloatArrayPosition] = this->significant[LargeFloatArrayPosition] | bitMask;
		}
	}

	std::cout << "LF constructor()" << std::endl;
	std::cout << "double partitioned is " << std::endl;
	for (int i = 0;i < 8;++i) {
		printbinchar(bitValueSignificant.bitRepresentation[i]);
	}
	std::cout << "End of double " << std::endl;
	std::cout << " large float partitioned is " << std::endl;
	for (int i = 0;i < 5;++i)
	{
		printbinchar(this->significant[i]);
	}
	std::cout << "End of double constructor";
	

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
	
	/* testing if operator << works
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

	*/
	double testValue = 1.1231231235561232;
	LargeFloat d_value(testValue);
	std::cout << "Test Value is : " << testValue << "  , and the Largefloat value is : " << d_value << std::endl;


	/*  testing how frexp works
	double test = 13.231;
	double signif;
	int exp;
	signif = frexp(test, &exp);

	std::cout << "The test number is : " << test << "  the exponent is : " << exp << " the significant is : " << signif << std::endl;
	std::cout << " The signif * 2 ^ exp is : " << signif*pow(2, exp) << std::endl;
	*/

	return 0;
}