#ifndef heatim_H     //  include guard
#define heatim_H

#include "heateq.h"
#include "lu.h"

//  inherit heateq for the numerical analysis
//  virtual inheritance becasue heatall combines it with heatex and heatan which also inherit heateq
//  and lu for the tridiagional solver
class heatim : public virtual heateq, public lu {

public:


	/*-------------------------------------------------------------------------------------------

	Constructors

	-------------------------------------------------------------------------------------------*/

	//  construtors inheritied from heateq
	heatim() : heateq() {}
	explicit heatim(int size) : heateq(size) {}
	
	/*-------------------------------------------------------------------------------------------

	Functions

	-------------------------------------------------------------------------------------------*/
	
	//  performs the crank-nichalson scheme with the output timesteps provided by the calling array
	//  filename is the settings file
	//  result is the 2d array into which the values of the output time steps will be stored
	void crank(std::string filename, array2D &result);

	//  performs the laasonen scheme with the output timesteps provided by the calling array
	//  filename is the settings file
	//  result is the 2d array into which the values of the output time steps will be stored
	void laasonen(std::string filename, array2D &result);

};

#endif