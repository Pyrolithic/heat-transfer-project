#include "lu.h"

//  LU decopostion for a diagonal tribanded matrix
void lu::triband(array1D &l, array1D &u, const double a, const double b, const double c)
{
	//  set u[0] to the value of b
	u[0] = b;

	//  calculate the l sub diagnal and u main diagonal
	//  iterative calulation as l[i] requires u[i] and u[i + 1] requires l[i]
	//  l[i] is really in the same row as u[i + 1], due to l starting on the second row
	for (int i = 0; i < l.rlength(); i++)
	{
		l[i] = a / u[i];
		u[i + 1] = b - c * l[i];
	}

	return;
}

//  LU decopostion solver for a diagonal tribanded matrix
void lu::lusolvetri(const array1D &l, const array1D &u, const array1D &b, const double c, array1D &x)
{
	//  array to store the y values as ly = b and yx = u
	array1D y(b.rlength());
	
	//  calculate the y values using the b and l values
	y[0] = b[0];
	
	for (int i = 0; i < y.clength(); i++)
	{
		y[i + 1] = b[i + 1] - y[i] * l[i];
	}
	
	//  use the y and u values to calculate x 
	x[y.clength()] = y[(y.clength())] / u[(y.clength())];

	for (int i = (y.clength() - 1); i > -1; i--)
	{
		x[i] = (y[i] - x[i + 1] * c) / u[i];
	}
		
}