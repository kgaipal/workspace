#include "fraction.h"

#include <stdexcept>
#include <sstream>

template<typename T>
T gcd(T a, T b)
{
	// borrowed from gcc
	while (b != 0) {
		T r = a % b;
		a = b;
		b = r;
	}
	return a;
}

// int specialization
template<>
int gcd(int a, int b)
{
	if (a < 0) {
		a *= -1;
	}

	if (b < 0) {
		b *= -1;
	}

	// borrowed from gcc
	while (b != 0) {
		int r = a % b;
		a = b;
		b = r;
	}
	return a;
}

template<typename T>
Fraction<T>::Fraction(T numer, T denom)
	: m_numerator(numer)
	, m_denominator(denom)
{
	if (d() == 0) {
		throw std::runtime_error(
			"invalid fraction: denominator cant be zero");
	}

	// simplify
	reduceFactors();
}

template<typename T>
void Fraction<T>::reduceFactors()
{
	// propagate sign from denominator to numerator
	// -a/-b is a/b
	// a/-b is -a/b
	if (d() < 0) {
		m_denominator *= -1;
		m_numerator *= -1;
	}

	// equal factors
	if (n() == d()) {
		m_numerator = m_denominator = 1;
	}

	// multiples reduction
	const T g = gcd(n(), d());

	if (g != 1/*1 is everybody's divisor*/) {
		m_numerator /= g;
		m_denominator /= g;
	}
}

template<typename T>
Fraction<T>::Fraction(const Fraction<T>& other)
	: m_numerator(other.n())
	, m_denominator(other.d())
{
}

template<typename T>
const std::string Fraction<T>::toString() const
{
	std::stringstream ss;
	if (d() == 0 || n() == d() || d() == 1) {
		ss << n();
	} else {
		ss << n() << "/" << d();
	}

	return ss.str();
}

template<typename T>
const Fraction<T> Fraction<T>::operator+(const Fraction<T>& other) const
{
	// equal denominators
	if (d() == other.d()) {
		return Fraction(n() + other.n(), d());
	}

	// unequal denominators, make denominators equal and then add
	return Fraction((n() * other.d()) + (d() * other.n()), d() * other.d());
}

template<typename T>
const Fraction<T> Fraction<T>::operator-(const Fraction<T>& other) const
{
	// equal denominators
	if (d() == other.d()) {
		return Fraction(n() - other.n(), d());
	}

	// unequal denominators, make denominators equal and then subtract
	return Fraction((n() * other.d()) - (d() * other.n()), d() * other.d());
}

template<typename T>
const Fraction<T> Fraction<T>::operator*(const Fraction<T>& other) const
{
	return Fraction(n() * other.n(), d() * other.d());
}

template<typename T>
const Fraction<T> Fraction<T>::operator/(const Fraction<T>& other) const
{
	return Fraction(n() * other.d(), d() * other.n());
}

template<typename T>
bool Fraction<T>::operator==(const Fraction<T>& other) const
{
	if (d() == other.d()) {
		return n() == other.n();
	}

	// otherwise make denominators equal and then compare numerators
	return ((n() * other.d()) == (d() * other.n()));
}

template<typename T>
bool Fraction<T>::operator!=(const Fraction<T>& other) const
{
	return !(*this == other);
}

template<typename T>
bool Fraction<T>::operator>(const Fraction<T>& other) const
{
	if (d() == other.d()) {
		return n() > other.n();
	}

	// otherwise make denominators equal and then compare numerators
	return ((n() * other.d()) > (d() * other.n()));
}

template<typename T>
bool Fraction<T>::operator<(const Fraction<T>& other) const
{
	// if same denominators then only compare numerators
	if (d() == other.d()) {
		return n() < other.n();
	}

	// otherwise make denominators equal and then compare numerators
	return ((n() * other.d()) < (d() * other.n()));
}
