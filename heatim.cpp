#include "heatim.h"

//  performs the crank-nichalson scheme with the output timesteps provided by the calling array
void heatim::crank(std::string filename, array2D &result)
{
	//  Extract the values from the settings file
	//  Display the error message and exit if the values
	//  can not be read
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

	//  Arrays to hold values, 2 are requried as this scheme uses t + 1 and t.
	//  Calculated values are put into tnext.
	heatim tnext(xsize);
	heatim tcurrent(xsize);

	//  Arrays to hold the values required for the lu decompostion.
	//  These are need as the boundary conditions are not used
	//  in the calculatons, hence the size - 2 for in, out, and u.
	//  l is size - 3 as it holds the l subdiagonal, so one less value.
	//  The boundary conditions could be removed so the in and out
	//  arrays are not needed but I like to keep them so they are not forgotten/lost
	//  Array to hold the values sent to the solver
	heatim in(xsize - 2);
	//  Array to hold the values from the solver
	heatim out(xsize - 2);
	//  Arrays to hold the l and u values
	array1D l(xsize - 3), u(xsize - 2);

	//  Resize the result array to number of x values by number of output time steps
	result.alter(xsize, (*this).rlength());

	//  Start time assumed to be 0
	//  Variable allows this to be changed if required
	t = 0;

	int n = 0;
	int end = tcurrent.clength();

	//  Calculate the value of r
	//  Used to simplify formula as used multiple times
	//  Value is divided by 2 so r / 2 does not have to be used
	//  Some workings leave the 2 outside of r 
	r = (d * dt) / (2 * dx * dx);
	
	//  a b and c values for the tridiagonal matrix
	a = c = -r;
	b = 1 + 2 * r;
	
	//  fill both arrays with the intial values
	//  only really required to fill tcurrent as this
	//  holds the intial conditions at the start
	//  but this ensures tnext contains the boundary conditions
	tcurrent.initalconditions(tsur0, tsur1, tin);
	tnext.initalconditions(tsur0, tsur1, tin);

	//  Calculate the l and u matrices 
	//  Only needs to be done once as a, b, and c do not change
	triband(l, u, a, b, c);

	//  run the crank nichalson scheme
	//  run until one time step past the last required output time
	//  one past to ensure the last required timestep is calculated
	for (t = (dt); t < ((*this)[(*this).clength()] + dt); t += dt)
	{
		//  convert the tcurrent values into the format required for the lu solver
		//  first value requires the boundary condition in the b array
		in[0] = r * tcurrent[2] + (1 - 2 * r) * tcurrent[1] + r* tcurrent[0] + r * tsur0;
		
		for (int i = 1; i < in.clength(); i++)
		{
			in[i] = r * tcurrent[i + 2] + (1 - 2 * r) * tcurrent[i + 1] + r* tcurrent[i];
		}
		
		//  last value requires the boundary condition in the b array	
		in[in.clength()] = r * tcurrent[end] + (1 - 2 * r) * tcurrent[end - 1] + r* tcurrent[end - 2] + r * tsur1;
		
		// run the lu solver to calculate the next timestep
		lusolvetri(l, u, in, c, out);

		//  put the solver results into the tnext array
		//  this keeps the boundary conditions in tnext
		for (int i = 0; i < out.rlength(); i++)
		{
			tnext[i + 1] = out[i];
		}

		// Run the store function to see if the time step needs to be saved
		(*this).store(t, dt, tnext, result, n);

		//  Shift the tnext values to tcurrent so they can be used in the next calculation
		tcurrent.transfer(tnext);

	}

}

//  performs the laasonen scheme with the output timesteps provided by the calling array
void heatim::laasonen(std::string filename, array2D &result)
{
	//  Extract the values from the settings file
	//  Display the error message and exit if the values
	//  can not be read
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

	//  fill both arrays with the intial values
	//  only really required to fill tprevious as this
	//  holds the intial conditions at the start
	//  but this ensures tnext contains the boundary conditions
	heatim tnext(xsize);
	heatim tcurrent(xsize);

	//  Arrays to hold the values required for the lu decompostion.
	//  These are need as the boundary conditions are not used
	//  in the calculatons, hence the size - 2 for in, out, and u.
	//  l is size - 3 as it holds the l subdiagonal, so one less value.
	//  The boundary conditions could be removed so the in and out
	//  arrays are not needed but I like to keep them so they are not forgotten/lost
	//  Array to hold the values sent to the solver
	heatim in(xsize - 2);
	//  Array to hold the values from the solver
	heatim out(xsize - 2);
	//  Arrays to hold the l and u values
	array1D l(xsize - 3), u(xsize - 2);

	//  Resize the result array to number of x values by number of output time steps
	result.alter(xsize, (*this).rlength());
	
	//  Start time assumed to be 0
	//  Variable allows this to be changed if required
	t = 0;
	
	//varible used to access the output time step values
	int n = 0;

	//  Record to clength of the arrays 
	int end = tcurrent.clength();

	//calculate the value of r
	//used to simplify formula as used multiple times
	r = (d * dt) / (dx * dx);
	
	//caculate the b and c values for the tri diaganaol matrix
	a = c = -r;
	b = 1 + 2 * r;

	//  fill both arrays with the intial values
	//  only really required to fill tcurrent as this
	//  holds the intial conditions at the start
	//  but this ensures tnext contains the boundary conditions
	tcurrent.initalconditions(tsur0, tsur1, tin);
	tnext.initalconditions(tsur0, tsur1, tin);

	//  Calculate the l and u matrices 
	//  Only needs to be done once as a, b, and c do not change
	triband(l, u, a, b, c);

	//  run the laasonen scheme
	//  run until one time step past the last required output time
	//  one past to ensure the last required timestep is calculated
	for (t = (dt); t < ((*this)[(*this).clength()] + dt); t += dt)
	{
		//  convert the tcurrent values into the format required for the lu solver
		//  first value requires the boundary condition in the b array
		in[0] = tcurrent[1] + r * tsur0;

		for (int i = 1; i < in.clength(); i++)
		{
			in[i] = tcurrent[i + 1];
		}

		//  last value requires the boundary condition in the b array
		in[in.clength()] = tcurrent[end - 1] + r * tsur1;

		//  run the lu solver to calculate the next timestep
		lusolvetri(l, u, in, c, out);

		//  put the solver results into the tnext array
		//  this keeps the boundary conditions in tnext
		for (int i = 0; i < out.rlength(); i++)
		{
			tnext[i + 1] = out[i];
		}

		//  Run the store function to see if the time step needs to be saved
		(*this).store(t, dt, tnext, result, n);

		//  Shift the tnext values to tcurrent so they can be used in the next calculation
		tcurrent.transfer(tnext);

	}
}