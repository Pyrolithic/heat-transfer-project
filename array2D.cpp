#include "array2D.h"

/*-------------------------------------------------------------------------------------------

  Constructors

-------------------------------------------------------------------------------------------*/


//  default constructor (empty array)
array2D::array2D() : std::vector<std::vector<double>>() {}

//  alternate constructor - creates a 2D array of Nrows by Ncols filled with zeros
array2D::array2D(int Nrows, int Ncols) : std::vector<std::vector<double> >()
{
	//  check values given are postive
	try {
		if (Nrows < 0 || Ncols < 0) throw std::invalid_argument("2D Array cannot be created: Negative value provided");
	}
	catch (const std::invalid_argument& ia) {
		std::cout << "Invalid argument: " << ia.what() << '\n';
		return;
	}

	//  set the size for the rows
	(*this).resize(Nrows);
	//  set the size for the columns
	for (int i = 0; i < Nrows; i++)
	{
		(*this)[i].resize(Ncols);
	}

	//  initialise the matrix to contain zero
	for (int i = 0; i < Nrows; i++)
	{
		for (int j = 0; j < Ncols; j++)
		{
			(*this)[i][j] = 0.0;
		}
	}
}

//  deconstructor
array2D::~array2D()
{

}

/*-------------------------------------------------------------------------------------------

  Accessor Methods

-------------------------------------------------------------------------------------------*/

//  return the number of rows
int array2D::getNrows() const
{
	return size();
}

//  return the number of columns
int array2D::getNcols() const
{
	return (*this)[0].size();
}

//  resize an existing array to Nrows by Ncols filled with zeros
void array2D::alter(int Nrows, int Ncols)
{
	//check input
	if (Nrows < 0 || Ncols < 0) throw std::invalid_argument("Array cannot be created: Negative value provided");

	// set the size for the rows
	(*this).resize(Nrows);
	// set the size for the columns
	for (int i = 0; i < Nrows; i++) (*this)[i].resize(Ncols);

	// initialise the matrix to contain zero
	for (int i = 0; i < Nrows; i++)
		for (int j = 0; j < Ncols; j++) (*this)[i][j] = 0.0;
}



/*-------------------------------------------------------------------------------------------

  Functions

-------------------------------------------------------------------------------------------*/

//  compare the values in array a and array b and put a[n] - b[n] into the calling array
void array2D::compare(array2D const a, array2D const b)
{
	//  check arrays are same size
	if (a.getNcols() != b.getNcols() || a.getNrows() != b.getNrows())
	{
		std::cout << "Error: The arrays cannot be compared" << std::endl;
		return;
	}

	for (int i = 0; i < a.getNrows(); i++)
	{
		for (int j = 0; j < a.getNcols(); j++)
		{
			(*this)[i][j] = a[i][j] - b[i][j];

			//  set error to zero if it smaller than 1 * 10^-7
			//  makes the results look cleaner 
			//  works fine for this application but might need to be made smaller/removed in other ones
			if ((*this)[i][j] < 1e-7 && (*this)[i][j] > -1e-7)
			{
				(*this)[i][j] = 0.0;
			}
		}
	}
	
}

//  compare the values in array a and array b and put abs(a[n] - b[n]) into the calling array
void array2D::abscompare(array2D const a, array2D const b)
{
	//check arrays are same size
	if (a.getNcols() != b.getNcols() || a.getNrows() != b.getNrows())
	{
		std::cout << "Error: The arrays cannot be compared" << std::endl;
		return;
	}

	for (int i = 0; i < a.getNrows(); i++)
	{
		for (int j = 0; j < a.getNcols(); j++)
		{
			(*this)[i][j] = fabs(a[i][j] - b[i][j]);
			
			//set error to zero if it smaller than 1 * 10^-7
			if ((*this)[i][j] < 1e-7 )
			{
				(*this)[i][j] = 0;
			}
		}
	}

}


/*-------------------------------------------------------------------------------------------

  Input Methods

-------------------------------------------------------------------------------------------*/

//  keyboard input, create the array if it does not exist
std::istream& operator>>(std::istream& is, array2D& a) {

	int nrows, ncols;

	//  check to see whether the array exists, otherwise create it
	if (!a.getNrows()) {
		std::cout << "input the number of rows for the array:" << std::endl;
		is >> nrows;
		std::cout << "input the number of coloumns for the array:" << std::endl;
		is >> ncols;
		//  check input 
		if (nrows < 0 || ncols < 0) throw std::invalid_argument("Array cannot be created: Negative value provided");

		//  prepare the array to hold nrows by ncols values
		a = array2D(nrows, ncols);
	}
	//  else if the array exists, get the size values
	else
	{
		nrows = a.getNrows();
		ncols = a.getNcols();
	}

	// input the elements
	std::cout << "Input " << nrows * ncols << " values:" << std::endl;
	for (int i = 0; i < nrows; i++)
	{
		for (int j = 0; j < a.getNcols(); j++)
		{
			is >> a[i][j];
		}
	}

	// return the stream object
	return is;
}

//  files input, create the array if it does not exist
std::ifstream& operator>>(std::ifstream& ifs, array2D& a) {

	int nrows, ncols;

	//  check to see whether the array exists
	//  otherwise create it with the first file value being the number of rows
	//  and the second value being the number of columns
	if (!a.getNrows()) 
	{
		//  read size from the file
		ifs >> nrows; ifs >> ncols;
		//  check inputs are valid
		if (nrows < 0 || ncols < 0) throw std::invalid_argument("Array cannot be created: Negative value provided");

		//  prepare the array to hold nrows by ncols values
		a = array2D(nrows, ncols);
	}
	//  else if the array exists, get the size values
	else
	{
		nrows = a.getNrows();
		ncols = a.getNcols();
	}

	//  input the values
	for (int i = 0; i < nrows; i++)
	{
		for (int j = 0; j < ncols; j++)
		{
			ifs >> a[i][j];
		}
	}

	//  return the stream object
	return ifs;
}



/*-------------------------------------------------------------------------------------------
 
  Output Methods

 -------------------------------------------------------------------------------------------*/

//  output to display
std::ostream& operator<<(std::ostream& os, const array2D& a) {

	//  check to see if the array has been defined
	//  if array exists output it
	if (a.getNrows() > 0 && a.getNcols() > 0) {
		
		for (int i = 0; i < a.getNrows(); i++)
		{
			for (int j = 0; j < a.getNcols(); j++)
			{
				//  tab placed first so output does not hug the side of the screen
				os << "\t" << a[i][j];
			}
			os << std::endl;
		}
		os << std::endl;
	}
	//  else if array does not display error message
	else
	{
		os << "The array does not exist" << std::endl;
	}

	return os;
}

//  output to file
std::ofstream& operator<<(std::ofstream& ofs, const array2D& a) {
	
	for (int i = 0; i < a.getNrows(); i++)
	{
		//write the array values in comma seperated format
		ofs << a[i][0];

		for (int j = 1; j < a.getNcols(); j++)
		{
			ofs << ", " << a[i][j];
		}
		ofs << std::endl;
	}

	return ofs;
}