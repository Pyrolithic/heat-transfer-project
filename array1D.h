#ifndef array1d_H     //  include guard
#define array1d_H

#include <iostream>   //  generic IO operations
#include <fstream>    //  file IO operations
#include <stdexcept>  //  provides exceptions
#include <vector>     //  std vector upon which the array is based

class array1D : private std::vector<double> {
	typedef std::vector<double> vec;

public:
	using vec::operator[];

	/*-------------------------------------------------------------------------------------------

	Constructors

	-------------------------------------------------------------------------------------------*/

	//  default constructor
	array1D(); 

	//  alternate constructor - creates a 1D array of size num filled with zeros
	explicit array1D(int num);

	//  deconstructor - included but not used as class contains no pointers
	~array1D();



	/*-------------------------------------------------------------------------------------------

	Accessor Methods

	-------------------------------------------------------------------------------------------*/

	//  returns the real length of the array
	int rlength() const;

	//  returns the number of the last accessable element (length minus 1)
	//  included so that rlength - 1 does not have to be used in loops which exclude boundary values
	//  makes the code easier for me to read
	int clength() const;

	//  copys the values in array a into the calling array
	//  used in the scheme to shift the values as time increases
	void transfer(array1D a);



	/*-------------------------------------------------------------------------------------------

	Input Methods

	-------------------------------------------------------------------------------------------*/

	//  overloaded istream >> operator
	//  keyboard input
	//  is is the keyboard input stream
	//  a is the array to write to
	friend std::istream& operator>>(std::istream& is, array1D& a);

	//  Overloaded ifstream >> operator. 
	//  file input
	//  ifs is file input stream
	//  a is the array to write to
	friend std::ifstream& operator>>(std::ifstream& ifs, array1D& a);



	/*-------------------------------------------------------------------------------------------

	Output Methods

	-------------------------------------------------------------------------------------------*/

	//  overloaded ostream << operator
	//  screen output
	//  os is the display output stream
	//  a is the array to read from
	friend std::ostream& operator<<(std::ostream& os, const array1D& a);

	//  overloaded ofstream << operator
	//  file output
	//  ofs is the file output stream
	//  a is array to read from
	friend std::ofstream& operator<<(std::ofstream& ofs, const array1D& a);

};


#endif