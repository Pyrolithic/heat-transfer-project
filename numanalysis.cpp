#include "numanalysis.h"

//  Intial Condtions
 void numanalysis::initalconditions(double boundary1, double boundary2, double inside)
{
	(*this)[0] = boundary1;
	(*this)[(*this).clength()] = boundary2;

	for (int i = 1; i < (*this).clength(); i++)
	{
		(*this)[i] = inside;
	}
}

//  store function
void numanalysis::store(double const t, double const dt, array1D const &tnext, array2D &result, int &n)
{

	//  check if tnext values are at a required output time step
	//  store them in the results array if they are
	//  tnext used as these are the values that were just calculated.
	//  I believe this is correct, else values might be one time step out.
	//  Check is 
	//  (n - (dt / 2))  <  t  <  (n + (dt / 2)) 
	//  since floats might have differances of 1e^-(insert big number here).
	//  This should also allow it to work if output time / dt is a fraction
	//  allthough it is untested.
	if (t > ((*this)[n] - dt / 2) && t < ((*this)[n] + dt / 2))
	{

		for (int i = 0; i < tnext.rlength(); i++)
		{
			result[i][n] = tnext[i];
		}

		//  If there are still values in the output time step
		//  array, increase n to point to the next value if
		//  the last value has been reached do not increase n.
		//  This is to prevent an out of range error.
		if (n < (*this).clength())
		{
			n++;
		}
	}
}