#ifndef array2d_H     //  include guard
#define array2d_H

#include <iostream>   //  generic IO operations
#include <fstream>    //  file IO operations
#include <stdexcept>  //  provides exceptions
#include <vector>     //  std vector upon which the array is based

class array2D : private std::vector<std::vector<double> > {
	typedef std::vector<std::vector<double> > vec;

public:
	using vec::operator[];  // make the array access operator public

    /*-------------------------------------------------------------------------------------------

      Constructors

    -------------------------------------------------------------------------------------------*/
	
	//  default constructor (empty array)
	array2D();

	//  alternate constructor - creates a 2D array of Nrows by Ncols filled with zeros
	explicit array2D(int Nrows, int Ncols);

	//  deconstructor - included but not used as class contains no pointers
	~array2D();
	


	/*-------------------------------------------------------------------------------------------

	  Accessor Methods

	-------------------------------------------------------------------------------------------*/

	//  get the number of rows in the array
	int getNrows() const;

	//  get the colums of rows in the array
	int getNcols() const;

	//  resize the array to Nrows by Ncols
	void alter(int Nrows, int Ncols); 

	

	/*-------------------------------------------------------------------------------------------

	  Functions

	-------------------------------------------------------------------------------------------*/

	//  compare the values in array a and array b and put the differances into the calling array
	//  a and b must be the same size 
	//  calculates this[n] = a[n] - b[n]
	void compare(array2D const a, array2D const b);

	//  compare the values in array a and array b and put the absolute differances into the calling array
	//  a and b must be the same size
	//  calculates this[n] = abs( a[n] - b[n] )
	void abscompare(array2D const a, array2D const b);


	/*-------------------------------------------------------------------------------------------

	  Input Methods

	-------------------------------------------------------------------------------------------*/

	//  overloaded istream >> operator
	//  keyboard input
	//  is is the keyboard input stream
	//  a is the array to write to
	friend std::istream& operator>>(std::istream& is, array2D& a);

    //  Overloaded ifstream >> operator. 
	//  file input
	//  ifs is file input stream
	//  a is the array to write to
	friend std::ifstream& operator>>(std::ifstream& ifs, array2D& a);



	/*-------------------------------------------------------------------------------------------

	  Output Methods

	-------------------------------------------------------------------------------------------*/

	//  overloaded ostream << operator
	//  screen output
	//  os is the display output stream
	//  a is the array to read from
	friend std::ostream& operator<<(std::ostream& os, const array2D& a);
	
	//  overloaded ofstream << operator
	//  file output
	//  ofs is the file output stream
	//  a is array to read from
	friend std::ofstream& operator<<(std::ofstream& ofs, const array2D& a);

};

#endif