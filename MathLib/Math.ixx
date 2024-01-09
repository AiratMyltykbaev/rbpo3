module;
#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <compare>
export module Math;
export namespace Math {
	class Complex
	{
	public:
		Complex() noexcept;
		Complex(double, double) noexcept;
		Complex(double num) noexcept;
		static Complex FromExponentialForm(double, double) noexcept;
		static Complex FromAlgebraicForm(double, double) noexcept;
		double Re() const noexcept;
		double Im() const noexcept;
		double Mod() const noexcept;
		double Arg() const noexcept;
		explicit operator double() const noexcept;
		Complex operator-();
		Complex& operator++();
		Complex operator++(int);
		Complex& operator--();
		Complex operator--(int);
		Complex& operator+=(const Complex&);
		Complex& operator-=(const Complex&);
		Complex& operator*=(const Complex&);
		Complex& operator/=(const Complex&);
	private:
		double mod;
		double arg;
	};

	Complex operator"" i(long double);
	Complex operator"" i(unsigned long long);
	std::ostream& operator<<(std::ostream&, Complex);

	class Rational
	{
	public:
		Rational();
		Rational(int, int);
		Rational(int);
		int Nominator() const noexcept;
		int Denominator() const noexcept;
		explicit operator double();
		Rational operator-();
		Rational& operator++();
		Rational operator++(int);
		Rational& operator--();
		Rational operator--(int);
		Rational& operator-=(const Rational& rhs);
		Rational& operator+=(const Rational& rhs);
		Rational& operator*=(const Rational& rhs);
		Rational& operator/=(const Rational& rhs);

	private:
		int nominator;
		int denominator;
	};

	int FindGreatestCommonDivisor(int, int);
	int FindLeastCommonMultiple(int, int);

	Complex::Complex() noexcept
		: arg(0), mod(0)
	{
	}

	Complex sin(const Complex& obj)
	{
		Complex newObj = obj; 
		return Complex(std::sin(obj.Re()) * cosh(obj.Im()), cos(obj.Re()) * sinh(obj.Im()));

	}

	Complex::Complex(double re, double im) noexcept
		: mod(std::sqrt(re* re + im * im)), arg(0)
	{
		if (re > 0)
			arg = std::atan(im / re);
		else if (re == 0 || im < 0)
			arg = M_PI / 2;
		else if (re == 0 || im < 0)
			arg = -M_PI / 2;
		else if (im < 0)
			arg = -M_PI + std::atan(im / re);
		else
			arg = M_PI + std::atan(im / re);
	}

	Complex::Complex(double num) noexcept
		: mod(num), arg(0)
	{
	}

	Complex Complex::FromExponentialForm(double mod, double arg) noexcept
	{
		return Complex(mod * std::cos(arg), mod * std::sin(arg));
	}

	Complex Complex::FromAlgebraicForm(double re, double im) noexcept
	{
		return Complex(re, im);
	}

	double Complex::Re() const noexcept
	{
		return mod * std::cos(arg);
	}

	double Complex::Im() const noexcept
	{
		return mod * std::sin(arg);
	}

	double Complex::Mod() const noexcept
	{
		return mod;
	}

	double Complex::Arg() const noexcept
	{
		return arg;
	}

	Complex::operator double() const noexcept
	{
		return Re();
	}

	Complex Complex::operator-()
	{
		return Complex(-Re(), Im());
	}

	Complex& Complex::operator++()
	{
		return *this = Complex(Re() + 1, Im());
	}

	Complex Complex::operator++(int)
	{
		++(*this);
		return Complex(Re() - 1, Im());
	}

	Complex& Complex::operator--()
	{
		return *this = Complex(Re() - 1, Im());
	}

	Complex Complex::operator--(int)
	{
		--(*this);
		return Complex(Re() + 1, Im());
	}

	Complex& Complex::operator+=(const Complex& rhs)
	{
		return *(this) = Complex(Re() + rhs.Re(), Im() + rhs.Im());
	}

	Complex& Complex::operator-=(const Complex& rhs)
	{
		return *(this) = Complex(Re() - rhs.Re(), Im() - rhs.Im());
	}

	Complex& Complex::operator*=(const Complex& rhs)
	{
		return *(this) = Complex
		(Re() * rhs.Re() - Im() * rhs.Im(),
			Im() * rhs.Re() + rhs.Im() * Re());
	}

	Complex& Complex::operator/=(const Complex& rhs)
	{
		return *(this) = Complex
		((Re() * rhs.Re() + Im() * rhs.Im()) / (rhs.Re() * rhs.Re() + rhs.Im() * rhs.Im()),
			(Im() * rhs.Re() - Re() * rhs.Im()) / (rhs.Re() * rhs.Re() + rhs.Im() * rhs.Im()));
	}

	Complex operator+(Complex lhs, Complex rhs) {
		return Complex(lhs.Re(), lhs.Im()) += rhs;
	}

	Complex operator-(Complex lhs, Complex rhs) {
		return Complex(lhs.Re(), lhs.Im()) -= rhs;
	}

	Complex operator*(Complex lhs, Complex rhs) {
		return Complex(lhs.Re(), lhs.Im()) *= rhs;
	}

	Complex operator/(Complex lhs, Complex rhs) {
		return Complex(lhs.Re(), lhs.Im()) /= rhs;
	}
	Complex operator"" i(long double im) {
		return Complex(0, im);
	}
	Complex operator"" i(unsigned long long im) {
		return Complex(0, im);
	}
	std::ostream& operator<<(std::ostream& os, Complex rhs)
	{
		return os << rhs.Re() << " + " << rhs.Im() << "i";
	}

	Rational::Rational()
		: nominator(0), denominator(1)
	{
	}

	Rational::Rational(int nominator, int denominator)
		: nominator(nominator / FindGreatestCommonDivisor(nominator, denominator) * (denominator / std::abs(denominator))),
		denominator(denominator / FindGreatestCommonDivisor(nominator, denominator) * (denominator / std::abs(denominator)))
	{
	}
	Rational sin(const Rational& obj)
	{
		Rational newObj = obj;
		return std::sin(obj.Nominator() / obj.Denominator());

	}
	Rational::Rational(int nominator)
		: nominator(nominator), denominator(1)
	{
	}

	int Rational::Nominator() const noexcept
	{
		return nominator;
	}

	int Rational::Denominator() const noexcept
	{
		return denominator;
	}

	Rational::operator double()
	{
		return (double)nominator / denominator;
	}

	Rational Rational::operator-()
	{
		return Rational(-Nominator(), Denominator());
	}

	Rational& Rational::operator++()
	{
		return (*this) = Rational(Nominator() + Denominator(), Denominator());
	}

	Rational Rational::operator++(int)
	{
		++(*this);
		return Rational(Nominator() - Denominator(), Denominator());
	}

	Rational& Rational::operator--()
	{
		return (*this) = Rational(Nominator() - Denominator(), Denominator());
	}

	Rational Rational::operator--(int)
	{
		--(*this);
		return Rational(Nominator() + Denominator(), Denominator());
	}

	Rational& Rational::operator-=(const Rational& rhs)
	{
		return (*this) = Rational(Nominator() * rhs.Denominator() - rhs.Nominator() * Denominator(), Denominator() * rhs.Denominator());
	}

	Rational& Rational::operator+=(const Rational& rhs)
	{
		return (*this) = Rational(Nominator() * rhs.Denominator() + rhs.Nominator() * Denominator(), Denominator() * rhs.Denominator());
	}

	Rational& Rational::operator*=(const Rational& rhs)
	{
		return (*this) = Rational(Nominator() * rhs.Nominator(), Denominator() * rhs.Denominator());
	}

	Rational& Rational::operator/=(const Rational& rhs)
	{
		return (*this) = Rational(Nominator() * rhs.Denominator(), Denominator() * rhs.Nominator());
	}

	Rational operator+(const Rational& lhs, const Rational& rhs);
	Rational operator-(const Rational& lhs, const Rational& rhs);
	Rational operator*(const Rational& lhs, const Rational& rhs);
	Rational operator/(const Rational& lhs, const Rational& rhs);
	bool operator==(const Rational& lhs, const Rational& rhs);
	std::ostream& operator<<(std::ostream&, const Rational&);

	int FindGreatestCommonDivisor(int lhs, int rhs)
	{
		lhs = std::abs(lhs);
		rhs = std::abs(rhs);
		while (lhs && rhs)
			if (lhs > rhs)
				lhs %= rhs;
			else
				rhs %= lhs;
		return rhs + lhs;
	}

	int FindLeastCommonMultiple(int rhs, int lhs)
	{
		return (int)(std::abs(rhs * lhs) / FindGreatestCommonDivisor(rhs, lhs));
	}

	Rational operator+(const Rational& lhs, const Rational& rhs)
	{
		return Rational(lhs.Nominator(), lhs.Denominator()) += rhs;
	}

	Rational operator-(const Rational& lhs, const Rational& rhs)
	{
		return Rational(lhs.Nominator(), lhs.Denominator()) -= rhs;
	}

	Rational operator*(const Rational& lhs, const Rational& rhs)
	{
		return Rational(lhs.Nominator(), lhs.Denominator()) *= rhs;
	}

	Rational operator/(const Rational& lhs, const Rational& rhs)
	{
		return Rational(lhs.Nominator(), lhs.Denominator()) /= rhs;
	}

	bool operator==(const Rational& lhs, const Rational& rhs)
	{
		return (double) lhs.Nominator() / lhs.Denominator() == (double) rhs.Nominator() / rhs.Denominator();
	}

	bool operator>(const Rational& lhs, const Rational& rhs)
	{
		return (double) lhs.Nominator() / lhs.Denominator() > (double) rhs.Nominator() / rhs.Denominator();
	}

	bool operator<(const Rational& lhs, const Rational& rhs)
	{
		return (double) lhs.Nominator() / lhs.Denominator() < (double) rhs.Nominator() / rhs.Denominator();
	}

	bool operator>=(const Rational& lhs, const Rational& rhs)
	{
		return !(lhs < rhs);
	}

	bool operator<=(const Rational& lhs, const Rational& rhs)
	{
		return !(lhs > rhs);
	}

	std::ostream& operator<<(std::ostream& os, const Rational& rhs)
	{
		return os << rhs.Nominator() << "/" << rhs.Denominator();
	}

}
