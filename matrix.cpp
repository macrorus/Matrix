#include <iostream>
using namespace std;
#include "math.h"

class Matrix
{
	
protected:
	int n;
	int m;
	float* data;
public:
	Matrix gauss()
	{
		Matrix a(m,n);
		int min = n;
		if (m < n)
			min = m;
		for (int i = 0; i < m * n; i++)
			a.data[i] = data[i];
		for (int i = 0; i < min; i++)
		{
			if ((a.get(i,i) == 0) && (i < min - 1))
			{
				for (int k = 0; k < m; k++)
				{
					float c = a.get(k, i);
					a.set(k, i, a.get(k, i+1));
					a.set(k, i+1, c);
				}
				
			}
				
			for (int j = i + 1; j < n; j++)
			{
				float c = -a.get(i, j)/a.get(i,i);
				for (int k = 0; k < m; k++)
					a.set(k,j,a.get(k,j)+a.get(k,i)*c);	
			}
			a.print(cout);
		cout << endl;
		}
		return a;
	}
	Matrix()
	{
		n = 0;
		m = 0;
		data = NULL;
	}
	Matrix(int m, int n)
	{
		this->m = m;
		this->n = n;
		data = new float[m * n];
		for (int i = 0; i < m * n; i++)
			data[i] = 0;

	}
	virtual Matrix operator+(Matrix& b)
	{
		if ((m != b.m) || (n != b.n))
		{
			Matrix a = Matrix();
			return a;
		}
		Matrix a(m, n);
		for (int i = 0; i < n*m; i++)
			a.data[i] = data[i] + b.data[i];
		return a;
	}
	virtual Matrix operator*(Matrix& b)
	{
		if (m != b.n)
		{
			Matrix a = Matrix();
			return a;
		}
		Matrix a(b.m, n);
		for (int i = 0; i < b.m; i++)
			for (int j = 0; j < n; j++)
			{
				float c = 0;
				for (int k = 0; k < m; k++)
					c += this->get(k, j) * b.get(i, k);
				a.set(i, j, c);
			}
		return a;
	}
	virtual Matrix operator*(float b)//убрал у аргумента &
	{
		Matrix a(m,n);
		for (int i = 0; i < n*m; i++)
			a.data[i] = data[i]*b;
		return a;
	}
	virtual Matrix operator-(Matrix& b)
	{
			if ((m != b.m) || (n != b.n))
		{
			Matrix a = Matrix();
			return a;
		}
		Matrix a(m, n);
		for (int i = 0; i < n*m; i++)
			a.data[i] = data[i] - b.data[i];
		return a;
	}
	virtual Matrix reverse()
	{
		if ((m != n) || (determinant() == 0))
		{
			Matrix a;
			return a;
		}
		Matrix a(n*2,n), b(n, n);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				a.set(i, j, get(i, j));
		for (int i = 0; i < n; i++)
			a.set(i + n, i, 1);
		a.print(cout);
		cout << endl;
		a = a.gauss();
		a.print(cout);
		cout << endl;
		for (int i = n - 1; i > 0; i--)
			for (int j = 0; j < i; j++)
			{
				float c = -a.get(i, j)/a.get(i, i);
				for (int k = i; k < n*2; k++)
					a.set(k, j, a.get(k, j)+a.get(k, i)*c);
			}
		a.print(cout);
		cout << endl;
		for (int i = 0; i < n; i++)
			for (int k = 2*n; k >= i; k--)
				a.set(k, i, a.get(k,i)/a.get(i,i));
		a.print(cout);
		cout << endl;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				b.set(i,j,a.get(i+n, j));
		return b;


	}
	virtual Matrix transpose()
	{
		Matrix a(n,m);
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
				a.set(j, i, get(i, j));
		return a;
	}
	virtual float determinant()
	{
		if (n != m)
			return 0;
		Matrix a = Matrix();
		a = gauss();
		int c = 1;
		for (int i = 0; i < n; i++)
			c *= a.get(i,i);
		return c;
	}
	virtual ostream& print(ostream& o)
	{
		for (int j = 0; j < n; j++)
		{
			for (int i = 0; i < m; i++)
				o << get(i, j) << '\t';
			o << endl;
		}
		return o;
	}
	virtual istream& read(istream& i)
	{
		int n = 0, m = 0;
		i >> m >> n;
		this->m = m;
		this->n = n;
		data = new float[m * n];
		for (int j = 0; j < m * n; j++)
			i >> data[j];
		return i;		
	}
	virtual void set(int i, int j, float data)
	{
		float x = pow(10.0,-5);//!
		if ((i < m) && (j < n))
			if ((data > -x) && (data < x))
			{
				this->data[j*m + i] = 0;
			}
			else
				this->data[j*m + i] = data;
		return;
	}
	virtual float get(int i, int j)
	{
		if ((i >= m) || (j >= n))
			return 0;
		return data[j*m + i];
	}
	virtual int getN()
	{
		return n;
	}
	virtual int getM()
	{
		return m;
	}
	virtual bool failed()
	{
		return data == NULL;
	}
};
