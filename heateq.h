#ifndef heateq_H      //  include guard
#define heateq_H

#include "numanalysis.h"

class heateq : public numanalysis {

protected:

	//  variables used in the heat equation
	//  defined here so they do not have to be redefined in any subsequent class
	//  set to protected so they are inherited but hidden
	double r;
	double d;
	double tsur0;
	double tsur1;
	double tin;

public:

	/*-------------------------------------------------------------------------------------------

	Constructors

	-------------------------------------------------------------------------------------------*/
	
	// construtors inheritied form numanalysis
	heateq() : numanalysis() {}
	explicit heateq(int size) : numanalysis(size) {}



	/*-------------------------------------------------------------------------------------------

	Functions

	-------------------------------------------------------------------------------------------*/

	//  file input
	//  filename is the name of the settings file
	//  this function takes the values in the settings file and puts them into the variables
	//  in the file the varibles are required to be in the order
	//  dx     --  delta x
	//  dt     --  delta t
	//  xstart --  the first value of x
	//  xend   --  the last value of x 
	//  tsur0  --  boundary condition (I consider this the left hand side bounday)
	//  tsur1  --  boundary condition (I consider this the right hand side bounday)
	//  tin    --  the intial internal condtion
	//  d      --  the coefficient
	//  otherwise the values will be put into the wrong varible and bad things happen
	//  well maybe not bad things but at best the results will be usless
	//  error checking means the scheme will not be run if 
	//  the error checking allows the varibles to be stored either as pure values or
	//  in the format dx: 0.05 which makes the file easier to read
	//  it would be good to improve this so that the order is not important but that is a nice to have
	void fileinput(std::string filename);
	
};

#endif