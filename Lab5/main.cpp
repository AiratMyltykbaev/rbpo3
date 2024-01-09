#include <iostream>
import Math;

using namespace Math;

Complex f(const Complex& z);
Rational f(const Rational& r);
double f(double x);

int main() {
	double temp1, temp2;
	std::cout << "REAL AND FAKE FOR COMPLEX" << std::endl;
	std::cin >> temp1 >> temp2;
	Complex complexNum = { temp1, temp2 };
	std::cout << "NOM DENOM" << std::endl;
	std::cin >> temp1 >> temp2;
	Rational rationalNum = { (int)temp1, (int)temp2 };
	std::cout << "f(const Complex& z) = " << f(complexNum) << std::endl;
	std::cout << "f(const Rational& r) = " << f(rationalNum) << std::endl;
	std::cout << "f(double x) = " << f((double)rationalNum) << std::endl;
	return 0;
}

Complex f(const Complex& u)
{
	return 2 * u + sin(Complex(u - 1i));
}
Rational f(const Rational& u)
{
	return (Rational)2 * u + Rational(sin(u - 1/2));
}
double f(double u)
{
	return 2 * u + sin(u - 0.5);
}

/*
1 1 1 1
*/
