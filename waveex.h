#ifndef waveex_H      //  include guard
#define waveex_H

#include "waveeq.h"

/*-------------------------------------------------------------------------------------------

  not required
  included to show how different equations and schemes can be built off of numanalysis
  added without affecting each other

-------------------------------------------------------------------------------------------*/

class waveex : virtual public waveeq {

public:

	/*-------------------------------------------------------------------------------------------

	Constructors

	-------------------------------------------------------------------------------------------*/

	// construtors inheritied form numanalysis
	waveex() : waveeq() {}
	explicit waveex(int size) : waveeq(size) {}



	/*-------------------------------------------------------------------------------------------

	Functions

	-------------------------------------------------------------------------------------------*/

};

#endif