#ifndef heatall_H     //  include guard
#define heatall_H

#include "heatan.h"
#include "heatex.h"
#include "heatim.h"

/*-------------------------------------------------------------------------------------------

catch all class which combines the explict, implicit and analyitical functions
done so that one array of time steps can be used for all heat schemes

-------------------------------------------------------------------------------------------*/

class heatall : public heatex, public heatim, public heatan {

public:

	/*-------------------------------------------------------------------------------------------

	Constructors

	-------------------------------------------------------------------------------------------*/

	//  construtors inheritied from heateq
	heatall() : heateq() {}
	explicit heatall(int size) : heateq(size) {}


	/*-------------------------------------------------------------------------------------------

	Functions

	-------------------------------------------------------------------------------------------*/

	//  No functions needed at the moment

};

#endif
