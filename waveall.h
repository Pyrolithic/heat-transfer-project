#ifndef waveall_H     //  include guard
#define waveall_H

#include "wavean.h"
#include "waveex.h"
#include "waveim.h"

/*-------------------------------------------------------------------------------------------

  catch all class which combines the explict, implicit and analyitical functions

  not required
  included to show how different equations and schemes can be built off of numanalysis
  added without affecting each other

-------------------------------------------------------------------------------------------*/

class waveall : public waveex, public waveim, public wavean {

public:

	/*-------------------------------------------------------------------------------------------

	Constructors

	-------------------------------------------------------------------------------------------*/

	//  construtors inheritied from heateq
	waveall() : waveeq() {}
	explicit waveall(int size) : waveeq(size) {}


	/*-------------------------------------------------------------------------------------------

	Functions

	-------------------------------------------------------------------------------------------*/

	//  No functions needed at the moment

};

#endif
