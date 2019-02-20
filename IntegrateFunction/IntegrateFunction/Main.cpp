#include<iostream>
// Борис Соколов



double integrateFunction(double A, double B, double(*F)(double)) {
	double riemmanSum = 0.0;
	int numberSubintervals = 1000000;
	
	double lenghtSubintervals = (B - A) / numberSubintervals;
	double xI_1 = A;
	double xI = A + lenghtSubintervals;
	double compensation = 0.0; // Kahan
	for (int i = 0 ; i < numberSubintervals; ++i) {
		double delta = xI - xI_1;
		double middlePoint = xI_1 + delta / 2;
		double middlePointValue = F(middlePoint);
		double y = middlePointValue * delta - compensation;
		double t = riemmanSum + y;
		compensation = (t - riemmanSum) - y;
		riemmanSum = t;
		xI_1 = xI;
		xI += lenghtSubintervals;
	}
	return riemmanSum;
}

double squareFunction(double x) {
	return x*x;
}


int main() {
	int A, B;
	std::cin >> A >> B;
	double integralValue = integrateFunction(A, B, squareFunction);

	std::cout << std::endl << "Integral value is : " << integralValue << std::endl;
	getchar();

}

