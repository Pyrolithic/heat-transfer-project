#include "Array1D.h"

/*-------------------------------------------------------------------------------------------

Constructors

-------------------------------------------------------------------------------------------*/

//  default constructor
array1D::array1D() : std::vector<double>() {}

//  alternate constructor - creates a 1D array of num filled with zeros
array1D::array1D(int num) : std::vector<double>()
{

	//  check values given are postive
	try 
	{
		if (num < 0) throw std::invalid_argument("1D Array cannot be created: Negative size given");
	}
	catch (const std::invalid_argument& ia) {
		std::cout << "Invalid argument: " << ia.what() << '\n';
		return;
	}

	// set the size of the array to the value provide
	(*this).resize(num);

	// initialise with zero
	std::size_t i;
	for (i = 0; i < size(); i++) (*this)[i] = 0.0;

}


//  deconstructor
array1D::~array1D()
{

}




/*-------------------------------------------------------------------------------------------

Accessor Methods

-------------------------------------------------------------------------------------------*/

//  returns the real length of the array
int array1D::rlength() const
{
	return size();
}

//  returns the number of the last accessable element (length minus 1)
int array1D::clength() const
{
	return (size() - 1);
}

//  transer function
void array1D::transfer(array1D a)
{
	//  check the arrays are the same size
	if (rlength() != a.rlength())
	{
		std::cout << "Array lengths do not match, unable to transfer values" << std::endl;
		return;
	}

	//  copys the values across
	for (int i = 0; i < rlength(); i++)
	{
		(*this)[i] = a[i];
	}

	return;
}



/*-------------------------------------------------------------------------------------------

  Input Methods

-------------------------------------------------------------------------------------------*/

//  keyboard input, create the array if it does not exist
std::istream& operator>>(std::istream& is, array1D& a) {

	int length;

	//  check to see whether the array exists, otherwise create it
	if (!a.rlength()) {
		std::cout << "Input the size of the array" << std::endl;
		is >> length;
		//  check input 
		if (length < 0) throw std::invalid_argument("Array cannot be created: Negative value provided");

		//  prepare the array to hold nrows by ncols values
		a = array1D(length);
	}
	//  else if the array exists, get the size
	else
	{
		length = a.rlength();
	}

	//  input the elements
	std::cout << "Input " << length << " values:" << std::endl;
	for (int i = 0; i < length; i++)
	{
		is >> a[i];
	}

	// return the stream object
	return is;
}

//  files input, create the array if it does not exist
std::ifstream& operator>>(std::ifstream& ifs, array1D& a) {

	int length;

	//  check to see whether the array exists
	//  otherwise create it using the first value as the length
	if (!a.rlength())
	{
		//  read size from the file
		ifs >> length; 
		//  check inputs are valid
		if (length < 0) throw std::invalid_argument("Array cannot be created: Negative value provided");

		//  prepare the array to hold nrows by ncols values
		a = array1D(length);
	}
	//  else if the array exists, get the size
	else
	{
		length = a.rlength();
	}

	//  input the values
	for (int i = 0; i < length; i++)
	{
		ifs >> a[i];
	}

	//  return the stream object
	return ifs;
}



/*-------------------------------------------------------------------------------------------

  Output Methods

-------------------------------------------------------------------------------------------*/

//  output to display
std::ostream& operator<<(std::ostream& os, const array1D& a)
{
	if (a.rlength() > 0) 
	{
		for (int i = 0; i < a.rlength(); i++)
		{
			//  tab placed first so output does not hug the side of the screen
			os << "\t" << a[i] << std::endl;
		}
	}
	else
	{
		os << "Array does not exist" << std::endl;
	}
	return os;
}

//  output to file
std::ofstream& operator<<(std::ofstream& ofs, const array1D& a) 
{

	for (int i = 0; i < a.rlength(); i++)
	{
		//  write the array values in a down list
		ofs << a[i] << std::endl;
	}

	return ofs;
}