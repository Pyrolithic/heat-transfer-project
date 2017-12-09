#ifndef lu_H     //  include guard
#define lu_H

#include "array1D.h"

class lu {
	
protected:

	//  values used for the tridiagonal decompostion
	//  defined here so they do not have to be redefined in any subsequent class
	//  set to protected so they are inherited but hidden
	double a;
	double b;
	double c;

public:

	/*-------------------------------------------------------------------------------------------

	Constructors

	-------------------------------------------------------------------------------------------*/

	//  no constructors as this class is only used for its functions
	//  do not want to get into any inadvertant diamond problems



	/*-------------------------------------------------------------------------------------------

	Functions
	even though these are defined with array1Ds, any class which inherits the array1D 
	constructor can sent through

	-------------------------------------------------------------------------------------------*/

	//  LU decopostion for a diagonal tribanded matrix
	//  l is the array used to store the l subdiagonal
	//  u is the array used to store the u main diagonal
	//  a is the subdiagonal of the orignal matrix
	//  b is the main diagonal of the orignal matrix
	//  c is the super diagonal of the orignal matrix
	//  if the a, b, and c values do not change during the scheme this function only needs to be run once
	//  this does not work for all values of a, b, anc c. in these special cases one calculation 
	//  will create a 0 causing subsequent calculations to try and divide by 0 
	//  know cases include a = b = c, (a/2) = b = c, -a = b = -c and -a = b = -(a/2)
	//  other cases may exist
	//  due to the way the LU decopostion works and the special case of the diagonal tribanded matrix
	//  the l matrix works out as a single band diagonal matrix so can be stored in a 1d array
	//  this band is on the sub diagonal so the array is one smaller than the size of the matrix.
	//  the u matric works out as a dual band diagonal. the superdiagonal is always the c value
	//  so the main diagonal can also be stored in a 1d array.
	//  this minimises memory usage as the zeros do not need to be stored
	//  this function can be used as a starting point for a future function which performs the 
	//  LU decompostion on a nonbanded tridiagonal matrix. a, b, and c would need to be changed to arrays
	//  with the code tweeked to reflect this and another array to store the u superdiagonal 
	//  would probably be needed. 
	void triband(array1D &l, array1D &u, const double a, const double b, const double c);

	//  LU decopostion solver for a diagonal tribanded matrix
	//  l is l subdiagonal result from the LU decopostion for a diagonal tribanded matrix
	//  u is u main diagonal result from the LU decopostion for a diagonal tribanded matrix
	//  b is the array of the know results of ax = b where a is the orginal matrix 
	//  c is the u superdiagonal which in this case is also the superdiagonal of the orginal matrix
	//  x is the unknow vector calculated in this function
	void lusolvetri(const array1D &l, const array1D &u, const array1D &b, const double c, array1D &x);

};

#endif