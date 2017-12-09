#include "heatex.h"

//  performs the simple explicit scheme
void heatex::simple(heatex c, double r)
{
	
	for (int i = 1; i < (*this).clength(); i++)
	{
		(*this)[i] = r * (c[i + 1] + c[i - 1]) + (1 - 2 * r) * c[i];
	}

}

//  performs the dufort-frankel scheme with the output timesteps provided by the calling array
void heatex::dufortfrankel(std::string filename, array2D &result)
{
	// Extract the values from the settings file
	// Display the error message and exit if the values
	// cannot be read
	try 
	{
		fileinput(filename);
	}
	catch (const char *msg)
	{
		std::cout << msg << std::endl;
		return;
	}
	
	xsize = (xend - xstart) / dx + 1;

	// Arrays to hold values, 3 requried as this scheme uses t + 1, t, and t - 1
	// Caculated values are put into tnext
	heatex tnext(xsize);
	heatex tcurrent(xsize);
	heatex tprevious(xsize);

	//  Resize the result array to number of x values by number of output time steps
	result.alter(xsize, (*this).rlength());

	//  Calculate the value of r
	//  Used to simplify formula as used multiple times
	r = (d * dt) / (dx * dx);

	//  Start time assumed to be 0
	//  Variable allows this to be changed if required
	t = 0;

	//  Varible used to access the output time step values
	int n = 0;
	
	//  fill all arrays with the intial values
	//  only really required to fill tprevious as this
	//  holds the intial conditions at the start
	//  but this ensures tcurrent and tnext contain the boundary conditions
	tprevious.initalconditions(tsur0, tsur1, tin);
	tcurrent.initalconditions(tsur0, tsur1, tin);
	tnext.initalconditions(tsur0, tsur1, tin);

	//  use the simple explicit scheme for the first time step as
	//  t - 1 is -dt so no useable values avaible 
	tcurrent.simple(tprevious, r);

	//  run the the dufort-frankel scheme
	//  start the scheme at time step 2 as first time step is caculated above
	//  run until one time step past the last required output time
	//  one past to ensure the last required timestep is calculated
	for (t = (2 * dt); t < ((*this)[(*this).clength()] + dt); t += dt)
	{
		//  dufort-frankel scheme
		for (int i = 1; i < tnext.clength(); i++)
		{
			tnext[i] = tprevious[i] + 2 * r * (tcurrent[i + 1] - tprevious[i] + tcurrent[i - 1]);
			tnext[i] = tnext[i] / (1 + 2 * r);
		}
		
		//  Run the store function to see if the time step needs to be saved
		(*this).store(t, dt, tnext, result, n);

		//  Shift the tcurrnet values to tnext and the tnext values to tcurrent
		//  so they can be used in the next calculation
		tprevious.transfer(tcurrent);
		tcurrent.transfer(tnext);
	}

}

void heatex::richardson(std::string filename, array2D &result)
{
	// Extract the values from the settings file
	// Display the error message and exit if the values
	// can not be read
	try 
	{
		fileinput(filename);
	}
	catch (const char *msg)
	{
		std::cout << msg << std::endl;
		return;
	}

	//  Use xstart, xend, and dx to calculate the number of grid points required
	xsize = (xend - xstart) / dx + 1;

	//  Arrays to hold values, 3 requried as this scheme uses t + 1, t, and t - 1
	//  Caculated values are put into tnext
	heatex tnext(xsize);
	heatex tcurrent(xsize);
	heatex tprevious(xsize);

	//  Resize the result array to number of x values by number of output time steps
	result.alter(xsize, (*this).rlength());

	//  Calculate the value of r
	//  Used to simplify formula as used multiple times
	r = (d * dt) / (dx * dx);

	//  Start time assumed to be 0
	//  Variable allows this to be changed if required
	t = 0;

	int n = 0;

	//  fill all arrays with the intial values
	//  only really required to fill tprevious as this
	//  holds the intial conditions at the start
	//  but this ensures tcurrent and tnext contain the boundary conditions
	tprevious.initalconditions(tsur0, tsur1, tin);
	tcurrent.initalconditions(tsur0, tsur1, tin);
	tnext.initalconditions(tsur0, tsur1, tin);
	
	//  use the simple explicit scheme for the first time step as
	//  t - 1 is -dt so no useable values avaible 
	tcurrent.simple(tprevious, r);

	//  run the richardson scheme
	//  start the scheme at time step 2 as first time step is caculated above
	//  run until one time step past the last required output time
	//  one past to ensure the last required timestep is calculated 
	for (t = (2 * dt); t < ((*this)[(*this).clength()] + dt); t += dt)
	{
		//  richardson scheme 
		for (int i = 1; i < tnext.clength(); i++)
		{
			tnext[i] = tprevious[i] + 2 * r * (tcurrent[i + 1] - 2 * tcurrent[i] + tcurrent[i - 1]);
		}

		// Run the store function to see if the time step needs to be saved
		(*this).store(t, dt, tnext, result, n);
		
		//  Shift the tcurrnet values to tnext and the tnext values to tcurrent
		//  so they can be used in the next calculation
		tprevious.transfer(tcurrent);
		tcurrent.transfer(tnext);

	}

}