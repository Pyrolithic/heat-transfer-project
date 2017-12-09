#include "heateq.h"

//  file input
void heateq::fileinput(std::string filename)
{
	//  open settings file
	std::ifstream ifs(filename);
	//  error count
	int error = 0;
	//  array to hold the file values
	//  a bit ugly to do it this way
	//  but it means the error part only needs to be written once
	heateq inputs(8);

	//  put the values from the files into the input array
	for (int i = 0; i < inputs.rlength(); i++)
	{
		ifs >> inputs[i];
		//  check if the input was accepted else run the error loop
		//  this is mainly included so that the variable names can be included
		//  in the settings file but also helps to detect an incorrect file
		//  this loop could be improved to detect other ways of writting the settings file
		while (ifs.fail())
		{
			//  increment error count
			error++;
			//  unset fail bit
			ifs.clear();
			//  skip bad input to see if the settings are in the format 
			//  dx: 0.05
			ifs.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
			//  retry input
			ifs >> inputs[i];

			//  exit if 1000 errors have occured
			//  no reason for this number other than it is big
			if (error == 1000)
			{
				throw "\nError: The settings file is incorrect - Unable to perfom the required scheme\n";
			}
		}
		
		// put the values from the settings file into the variables
		// I did not expect this to work but it does because classes? cool, it makes things easier
		dx = inputs[0];
		dt = inputs[1];
		xstart = inputs[2];
		xend = inputs[3];
		tsur0 = inputs[4];
		tsur1 = inputs[5];
		tin = inputs[6];
		d = inputs[7];

		//  check xstart is less than xend
		//  if xstart is greater the schemes will try to create negative arrays
		//  and other bad things might happen
		if (xstart > xend)
		{
			throw "\nError: Xstart needs to be less than xend - Unable to perfom the required scheme\n";
		}
	}
}