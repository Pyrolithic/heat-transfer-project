#ifndef waveim_H      //  include guard
#define waveim_H

#include "waveeq.h"
#include "lu.h"

/*-------------------------------------------------------------------------------------------

  not required
  included to show how different equations and schemes can be built off of numanalysis
  added without affecting each other

-------------------------------------------------------------------------------------------*/

class waveim : virtual public waveeq, public lu {

public:

	/*-------------------------------------------------------------------------------------------

	Constructors

	-------------------------------------------------------------------------------------------*/

	// construtors inheritied form numanalysis
	waveim() : waveeq() {}
	explicit waveim(int size) : waveeq(size) {}



	/*-------------------------------------------------------------------------------------------

	Functions

	-------------------------------------------------------------------------------------------*/

};

#endif