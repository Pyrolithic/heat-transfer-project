#include "heatan.h"

//  analytical solution where both boundarys are the same temperature
void heatan::uniformboundary(array2D &result)
{
	//  variabes that change based on problem 
	//  should be modified so they can be set by the user
	dx = 0.05;
	tsur0 = 300;
	tin = 100;
	xsize = 21;
	
	//  variables used in the calculation
	//  calcation is split into the parts e, mpi, and sine for easier visualization
	double e;
	double mpi;
	double sine;
	double x;
	double tsum;
	double pi = atan(1) * 4;
	int n;

	//  resize the result array to number of x values by number of output time steps
	result.alter(xsize, (*this).rlength());

	//  run calcation for all time steps given by the calling array
	for (int j = 0; j < (*this).rlength(); j++)
	{
		//  clear n and x for each calculation
		//  n is used for the postion in the result array
		//  x is used for the postion being calculated
		n = 0;
		x = 0;

		//  set time to value specifed in array[j]
		t = (*this)[j];

		//  run the calculation for all postions of x
		for (int i = 0; i < xsize; i++)
		{
			//  clear tsum for each calculation
			//  this is used to hold the sum
			tsum = 0;
			
			//  run the summation 200 times
			//  at t = 0 this equation requires 500,000 summations to be within 0.001 of the intial 
			//  conditions for most x values. do not try to model this in excel, it is easy enough to do
			//  but excel will not like you.
			//  at t != 0, 150 to 500,000 summations produce values which are identical to 7dp for most
			//  values of x and t. Therefore 200 summations is used here as a balance between accuracy
			//  and runtime. 
			for (int m = 1; m < 200; m++)
			{
				e = exp(-0.1 *pow(m*pi, 2)*t);
				mpi = (1 - pow(-1, m)) / (m*pi);
				sine = sin(m*pi*x);
				tsum = tsum + (e * mpi * sine);
			}

			//  increase x to the next step
			x = x + dx;

			//  store the caclulated value in the correct postion of the results array
			result[n][j] = tsur0 + 2 * (tin - tsur0) * tsum;
			n++;
		}
	}
}


//  analytical solution where the boundarys have different temperatures
void heatan::dualboundary(array2D &result)
{
	//insert heat equation dual boundary calculation code here if required
}