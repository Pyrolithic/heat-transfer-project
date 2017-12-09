#ifndef numanalysis_H
#define numanalysis_H

#include "array1D.h"  
#include "array2D.h"
#include <string>

class numanalysis : public array1D {

protected:

	//  variables used in all/most numerical scheme
	//  defined here so they do not have to be redefined in any subsequent class
	//  set to protected so they are inherited but hidden
	double dx;
	double dt;
	double t;
	double x;
	int xstart;
	int xend;
	int xsize;

public:

	/*-------------------------------------------------------------------------------------------

	Constructors

	-------------------------------------------------------------------------------------------*/

	//  construtors inheritied from array1D
	numanalysis() : array1D() {}
	explicit numanalysis(int size) : array1D(size) {}



	/*-------------------------------------------------------------------------------------------

	Functions

	-------------------------------------------------------------------------------------------*/
	
	//  Intial Condtions
	//  this function fills an array with intial and bounary conditions
	//  boundary1 is the boundary value stored in the first postion of the array
	//  boundary2 is the boundary value stored in the last postion of the array
	//  inside is the intial value stored in all the other postions of the array
	//  this function is only for problems where the intial values are identical 
	//  The function has varibles for both the left and right had bounadrys so that
	//  it can handle symetrical and asymetrical boundary condtions.
	void initalconditions(double boundary1, double boundary2, double inside);
	
	//  Store
	//  This function will store the current calcuated step in a 2d array
	//  if it matches one of the required output timesteps
	void store(double const t, double const dt, array1D const &tnext, array2D &result, int &n);

};

#endif