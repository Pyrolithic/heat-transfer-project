#ifndef heatan_H     //  include guard
#define heatan_H

#include "heateq.h"

//  virtual inheritance becasue heatall combines it with heatex and heatim which also inherit heateq
class heatan :	virtual public heateq {

public:

	/*-------------------------------------------------------------------------------------------

	Constructors

	-------------------------------------------------------------------------------------------*/

	//  construtors inheritied from heateq
	heatan() : heateq() {}
	explicit heatan(int size) : heateq(size) {}
	


	/*-------------------------------------------------------------------------------------------

	Functions

	-------------------------------------------------------------------------------------------*/

	//  analytical solution for where the boundary conditions are identical
	//  calculates the output timesteps provided by the calling array
	//  result is the 2d array into which the values of the output time steps will be stored
	void heatan::uniformboundary(array2D &result);

	//  analytical solution for where the boundary conditions are not identical
	//  calculates the output timesteps provided by the calling array
	//  result is the 2d array into which the values of the output time steps will be stored
	void heatan::dualboundary(array2D &result);

};

#endif

