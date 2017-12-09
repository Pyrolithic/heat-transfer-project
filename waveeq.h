#ifndef waveeq_H      //  include guard
#define waveeq_H

#include "numanalysis.h"

/*-------------------------------------------------------------------------------------------

  not required
  included to show how different equations and schemes can be built off of numanalysis
  added without affecting each other

-------------------------------------------------------------------------------------------*/

class waveeq : public numanalysis {

protected:

	//  variables used in the wave equation
	//  defined here so they do not have to be redefined in any subsequent class
	//  set to protected so they are inherited but hidden

public:

	/*-------------------------------------------------------------------------------------------

	Constructors

	-------------------------------------------------------------------------------------------*/

	// construtors inheritied form numanalysis
	waveeq() : numanalysis() {}
	explicit waveeq(int size) : numanalysis(size) {}



	/*-------------------------------------------------------------------------------------------

	Functions

	-------------------------------------------------------------------------------------------*/

};

#endif