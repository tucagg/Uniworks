#include <iostream>

using namespace std;

class Polynomial 
{
	public:
		Polynomial(); 
		Polynomial(const Polynomial&);

		Polynomial(double coefficient[],int size);
		~Polynomial();
		double& operator[](int degree);
		const double& operator[](int degree)const;

		const Polynomial& operator=(const Polynomial& rhs);
		int mySize();

		// friend functions:
		friend double evaluate(const Polynomial& ploy, double arg);
		friend Polynomial operator+(const Polynomial& Ish, const Polynomial& rhs);
		friend Polynomial operator-(const Polynomial& Ish, const Polynomial& rhs);
		friend Polynomial operator*(const Polynomial& Ish, const Polynomial& rhs);
	private:
		double * coef;
		int size;
};

int main()
{
	Polynomial empty;
	double one[] = {1};
	Polynomial One(one, 1);
	double quad[] = {3, 2, 1};
	double cubic[] = {1, 2, 0, 3};
	Polynomial q(quad, 3); // q is 3 + 2*x + x*x
	Polynomial c(cubic, 4);// c is 1 + 2*x + 0*x*x + 3*x*x*x
	Polynomial p = q; // test copy constructor
	Polynomial r;
	r = q;
	// test operator=
	r = c;
	cout << "Polynomial q " << endl;
	for(int i = 0; i < 3; i++)
	{
		cout << "term with degree " << i << " has coefficient " << q[i] << endl;
	}
	cout << "Polynomial c " << endl;
	for(int i = 0; i < 4; i++)
	{
		cout << "term with degree " << i << " has coefficient " << c[i] << endl;
	}
	cout << "value of q(2) is " << evaluate(q, 2) << endl;
	cout << "value of p(2) is " << evaluate(p, 2) << endl;
	cout << "value of r(2) is " << evaluate(r, 2) << endl;
	cout << "value of c(2) is " << evaluate(c, 2) << endl;
	r = q + c;
	cout << "value of (q + c)(2) is " << evaluate(r, 2) << endl;
	r = q - c;
	cout << "value of (q - c)(2) is " << evaluate(r, 2) << endl;
	r = q * c;
	cout << "size of q*c is " << r.mySize() << endl;
	cout << "Polynomial r (= q*c) " << endl;
	for(int i = 0; i < r.mySize(); i++)
		cout << "term with degree " << i << " has coefficient " << r[i] << endl;
	cout << "value of (q * c)(2) is " << evaluate(r, 2) << endl;

	return 0;
}

int Polynomial::mySize()
{
	return size;
}


Polynomial::Polynomial():coef(0), size(0)
{
	// empty constructor
}

const Polynomial& Polynomial::operator=(const Polynomial& rhs)
{
	if(rhs.coef == coef) 
		return rhs;      
	else
	{
		delete [] coef;
		coef = new double[rhs.size];
		for(int i = 0; i < rhs.size; i++)
			coef[i] = rhs.coef[i];
		size = rhs.size;
	}
	return rhs;
}

Polynomial::Polynomial(const Polynomial& rhs) : size(rhs.size)
{
	coef = new double[rhs.size];
	for(int i = 0; i < rhs.size; i++)
		coef[i] = rhs.coef[i];
}

Polynomial::Polynomial(double coefficient[],int size) : size(size)
{
	coef = new double[size];
	for(int i = 0; i < size; i++)
		coef[i] = coefficient[i];
}

Polynomial::~Polynomial()
{
	delete [] coef;
}

const double& Polynomial::operator[](int degree) const
{
	return coef[degree];
}

double& Polynomial::operator[](int degree)
{
	return coef[degree];
}

double max(double Ihs, double rhs)
{
	return (Ihs > rhs) ? Ihs : rhs;
}

Polynomial operator+(const Polynomial& Ihs, const Polynomial& rhs)
{
	const int sumSize = max(Ihs.size, rhs.size);
	double* sumCoefs = new double[sumSize];
	for(int i = 0; i < sumSize; i++)
		sumCoefs[i] = Ihs.coef[i] + rhs.coef[i];

	return Polynomial(sumCoefs, sumSize);
}

Polynomial operator-(const Polynomial& Ihs, const Polynomial& rhs)
{
	int sumSize = max(Ihs.size, rhs.size);
	double* sumCoefs = new double[sumSize];
	for(int i = 0; i < sumSize; i++)
		sumCoefs[i] = Ihs.coef[i] - rhs.coef[i];

	return Polynomial(sumCoefs, sumSize);
}

Polynomial operator*(const Polynomial& Ihs, const Polynomial& rhs)
{
	int prodSize = Ihs.size + rhs.size;
	double* prodCoefs = new double[prodSize];

	for(int i = 0; i < prodSize; i++)
		prodCoefs[i] = 0;

	for(int i = 0; i < Ihs.size; i++)
	{
		for(int j = 0; j < rhs.size; j++)
		{
			prodCoefs[i + j] += Ihs[i] * rhs[j];
		}
	}

	return Polynomial(prodCoefs, prodSize);
}

double evaluate(const Polynomial& poly, double arg)
{
	double value = 0;
	for(int i = poly.size - 1; i >= 0; i--)
		value = poly[i] + arg * value;

	return value;
}