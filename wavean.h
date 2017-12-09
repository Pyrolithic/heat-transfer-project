#ifndef wavean_H      //  include guard
#define wavean_H

#include "waveeq.h"

/*-------------------------------------------------------------------------------------------

  not required
  included to show how different equations and schemes can be built off of numanalysis
  added without affecting each other

-------------------------------------------------------------------------------------------*/

class wavean : virtual public waveeq {

public:

	/*-------------------------------------------------------------------------------------------

	Constructors

	-------------------------------------------------------------------------------------------*/

	// construtors inheritied form numanalysis
	wavean() : waveeq() {}
	explicit wavean(int size) : waveeq(size) {}



	/*-------------------------------------------------------------------------------------------

	Functions

	-------------------------------------------------------------------------------------------*/

};

#endif