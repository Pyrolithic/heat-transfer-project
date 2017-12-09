#ifndef heatex_H     //  include guard
#define heatex_H

#include "heateq.h"

//  virtual inheritance becasue heatall combines it with heatim and heatan which also inherit heateq
class heatex : public virtual heateq {

public:

	/*-------------------------------------------------------------------------------------------

	Constructors

	-------------------------------------------------------------------------------------------*/

	//  construtors inheritied from heateq
	heatex() : heateq() {}
	explicit heatex(int size) : heateq(size) {}



	/*-------------------------------------------------------------------------------------------

	Functions

	-------------------------------------------------------------------------------------------*/

	//  performs the simple explicit scheme
	//  not used as a scheme in itself
	//  used in both the dufort-frankel and richardson schemes for the first timestep
	//  therefore easier to create a new function if simple explicit is required as a standalone scheme
	//  c is the array holding the previous timestep values
	//  r is (d * dt) / (dx^2)
	void simple(heatex c, double r);

	//  performs the dufort-frankel scheme with the output timesteps provided by the calling array
	//  filename is the settings file
	//  result is the 2d array into which the values of the output time steps will be stored
	void dufortfrankel(std::string filename, array2D &result);

	//  performs the ricahrdson scheme with the output timesteps provided by the calling array
	//  filename is the settings file
	//  result is the 2d array into which the values of the output time steps will be stored
	void richardson(std::string filename, array2D &result);
	
};

#endif