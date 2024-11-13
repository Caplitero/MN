
#include <iostream>
#include <math.h>

#include <iostream>
#include <cmath>
#include <stdexcept>
#include "math_cap.h"
using namespace std;

double var[101];
double x[101];
double results[101][101];



#define MAX_SIZE  101  // Maximum matrix size, adjust if needed




double Newton(int i, int k)
{
	
	if (k == 0)
		return var[i];
	else {
		double r = 0;


		r= ((Newton(i + 1, k - 1) - Newton(i, k - 1)) / (x[i + k] - x[i]));
		results[i][k] = r;
		return r;
	}
}


void square_method(int n,int power)
{
	Matrix<float> mat(power, power);
	Matrix<float> mat2(power, 1);
	float value=0;

	for (int i = 0; i < power; i++)
	{
		for (int j = 0; j < power; j++)
		{
			float sum = 0;
			for (int s = 1; s <= n; s++)
				sum += pow(x[s], i + j);
			mat.at(i,j) = sum;
		}

	}

	for (int i = 0; i < power; i++)
	{
		float sum = 0;
		for (int s = 1; s <= n; s++)
		{
			sum += var[s] * pow(x[s], i);
		}
		mat2.at(i, 0) = sum;
	}

	std::cout << "Matrix X : \n";
	mat.display();
	std::cout << "\n";
	Matrix<float> inverse = mat.get_inverse();
	std::cout << " Inverse of matrix X: \n";
	inverse.display();
	std::cout << " \n";

	std::cout << "Matrix Y : \n";
	mat2.display();

	std::cout << "\n";
	std::cout << " Coefficients : \n";
	(inverse.multiply(mat2)).display();
	   
	

}

int main()
{
	int n;
	std::cout << "Number of variables : ";
	cin >> n;
	std::cout << "x values : ";
	for (int i = 1; i <= n; i++)
		cin >> x[i];
	std::cout << "y values : ";
	for (int i = 1; i <= n; i++)
		cin >> var[i];
	
	

	std::cout << "Choose method : \n 1) Newton \n 2) Square  \n 3) Lagrange\n";
	int method;
	cin >> method;
	if (method == 1)
	{
		Newton(1, n - 1);


		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n - i; j++)
				std::cout << results[i][j] << " ";
			std::cout << "\n";
		}
	}
	if (method == 2)
	{
		int grade;
		std::cout << "Choose the calculating grade (ex 2,3,4) : ";
		cin >> grade;
		square_method(n,grade);
	}

	if (method == 3)
	{
		float choosen_X;
		cout << "Please choose a value to aproximate : x = ";
		cin >> choosen_X;
		float value = 0;
		for (int s = 1; s <= n; s++)
		{
			float produs=1;
			for (int p = 1; p <= n; p++)
			{
				if(p!=s)
				produs *= (choosen_X - x[p]) / (x[s] - x[p]);
			}
			value += produs*var[s];
			
		}
		std::cout << value;
	}

}




