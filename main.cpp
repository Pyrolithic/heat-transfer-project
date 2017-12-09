#include <iostream>   //  generic IO operations
#include <fstream>    //  file IO operations
#include "heatall.h"  //  used for the schemes
#include <time.h>     //  time operations
#include <stdexcept>  //  provides exceptions

using namespace std;

int main()
{
	//  variables required to run the schemes
	heatall values(5);         //  array to hold the output timesteps
	array2D output(21, 5);     //  array to hold the scheme results
	array2D output2(21, 5);    //  array to hold the analytical results
	array2D dif(21, 5);        //  array to hold the differance between the scheme and analytical results
	ofstream ofs;              //  output file varible

	//  variables to calculate the scheme run time, used for testing
	clock_t time;  //  variable to get time
	double r = 0, d = 0, c = 0, l1 = 0, l2 = 0, l3 = 0, l4 = 0;  // used to calculate average time
	int sample = 10;  //  number of times to run the schemes 

	//  required output timesteps in hours
	values[0] = 0.1;
	values[1] = 0.2;
	values[2] = 0.3;
	values[3] = 0.4;
	values[4] = 0.5;


    //  run analytical needs to be run first so data is avaible for comparing
	ofs.open("results/analytical.dat");
	values.uniformboundary(output2);
	ofs << output2;
	ofs.close();

	//  run schemes multiple times so an average runtime can be calculated 
	for (int i = 0; i < sample; i++)
	{

		/*------------------------------------------------------------------------------------------------
		  Richardson scheme
		------------------------------------------------------------------------------------------------*/
		//  open file for Richardson
		ofs.open("results/richardson.dat");
		//  get start time
		time = clock();
		//  run Richardson scheme
		values.richardson("settings.dat", output);
		//  get end time and calculate run time
		time = clock() - time;
		//  add together all the runtimes for average
		r = r + (((float)time) / CLOCKS_PER_SEC);
		//  compare Richardson with analytical
		dif.compare(output, output2);
		//  output Richardson results are error to file
		ofs << "Richardson Results (dx = 0.05, dt = 0.01)" << endl;
		ofs << output << endl;
		ofs << "Richardson error" << endl;
		ofs << dif << endl;
		//  close Richardson results file
		ofs.close();


		/*------------------------------------------------------------------------------------------------
		  Dufort scheme
		------------------------------------------------------------------------------------------------*/
		//  open file for Dufort results
		ofs.open("results/dufort-frankel.dat");
		//  get start time
		time = clock();
		//  run Dufort scheme
		values.dufortfrankel("settings.dat", output);
		//  get end time and calculate run time
		time = clock() - time;
		//  add together all the runtimes for average
		d = d + (((float)time) / CLOCKS_PER_SEC);
		//  compare Dufort with analytical
		dif.compare(output, output2);
		//  output Dufort results are error to file
		ofs << "Dufort-Frankel Results (dx = 0.05, dt = 0.01)" << endl;
		ofs << output << endl;
		ofs << "Dufort-Frankel Error" << endl;
		ofs << dif << endl;
		//  close Dufort results file
		ofs.close();


		/*------------------------------------------------------------------------------------------------
		  Crank scheme
		------------------------------------------------------------------------------------------------*/
		//  open file for Crank results
		ofs.open("results/crank.dat");
		//  get start time
		time = clock();
		//  run Crank scheme
		values.crank("settings.dat", output);
		//  get end time and calculate run time
		time = clock() - time;
		//  add together all the runtimes for average
		c = c + (((float)time) / CLOCKS_PER_SEC);
		//  compare Crank with analytical
		dif.compare(output, output2);
		//  output Crank results are error to file
		ofs << "Crank Results (dx = 0.05, dt = 0.01)" << endl;
		ofs << output << endl;
		ofs << "Crank Error" << endl;
		ofs << dif << endl;
		//  close Crank results file
		ofs.close();


		/*------------------------------------------------------------------------------------------------
		  Laasonen scheme (dt = 0.01h)
		------------------------------------------------------------------------------------------------*/
		//  open file for Laasonen results
		ofs.open("results/laasonen.dat");
		//  get start time
		time = clock();
		//  run Laasonen scheme
		values.laasonen("settings.dat", output);
		//  get end time and calculate run time
		time = clock() - time;
		//  add together all the runtimes for average
		l1 = l1 + (((float)time) / CLOCKS_PER_SEC);
		//  compare Laasonen with analytical
		dif.compare(output, output2);
		//  output Laasonen results are error to file
		ofs << "Laasonen Results (dx = 0.05, dt = 0.01)" << endl;
		ofs << output << endl;
		ofs << "Laasonen Error" << endl;
		ofs << dif << endl;
		//  close Laasonen results file
		ofs.close();


		/*------------------------------------------------------------------------------------------------
		  Laasonen scheme (dt = 0.025h)
		------------------------------------------------------------------------------------------------*/
		//  open file for Laasonen results
		ofs.open("results/laasonen2.dat");
		//  get start time
		time = clock();
		//  run Laasonen scheme
		values.laasonen("settings2.dat", output);
		//  get end time and calculate run time
		time = clock() - time;
		//  add together all the runtimes for average
		l2 = l2 + (((float)time) / CLOCKS_PER_SEC);
		//  compare Laasonen with analytical
		dif.compare(output, output2);
		//  output Laasonen results are error to file
		ofs << "Laasonen Results (dx = 0.05, dt = 0.025)" << endl;
		ofs << output << endl;
		ofs << "Laasonen Error" << endl;
		ofs << dif << endl;
		//  close Laasonen results file
		ofs.close();


		/*------------------------------------------------------------------------------------------------
		  Laasonen scheme (dt = 0.05h)
		------------------------------------------------------------------------------------------------*/
		//  open file for Laasonen results
		ofs.open("results/laasonen3.dat");
		//  get start time
		time = clock();
		//  run Laasonen scheme
		values.laasonen("settings3.dat", output);
		//  get end time and calculate run time
		time = clock() - time;
		//  add together all the runtimes for average
		l3 = l3 + (((float)time) / CLOCKS_PER_SEC);
		//  compare Laasonen with analytical
		dif.compare(output, output2);
		//  output Laasonen results are error to file
		ofs << "Laasonen Results (dx = 0.05, dt = 0.05)" << endl;
		ofs << output << endl;
		ofs << "Laasonen Error" << endl;
		ofs << dif << endl;
		//  close Laasonen results file
		ofs.close();


		/*------------------------------------------------------------------------------------------------
		  Laasonen scheme (dt = 0.1h)
		------------------------------------------------------------------------------------------------*/
		//  open file for Laasonen results
		ofs.open("results/laasonen4.dat");
		//  get start time
		time = clock();
		//  run Laasonen scheme
		values.laasonen("settings4.dat", output);
		//  get end time and calculate run time
		time = clock() - time;
		//  add together all the runtimes for average
		l4 = l4 + (((float)time) / CLOCKS_PER_SEC);
		//  compare Laasonen with analytical
		dif.compare(output, output2);
		//  output Laasonen results are error to file
		ofs << "Laasonen Results (dx = 0.05, dt = 0.1)" << endl;
		ofs << output << endl;
		ofs << "Laasonen Error" << endl;
		ofs << dif << endl;
		//  close Laasonen results file
		ofs.close();

	}

	//  display average scheme run times on screen
	cout << "Average run time for Richardson was: " << (r / sample) << " seconds\n";
	cout << "Average run time for Dufort was: " << (d / sample) << " seconds\n";
	cout << "Average run time for Crank was: " << (c / sample) << " seconds\n";
	cout << "Average run time for Laasonen (dt = 0.01h) was: " << (l1 / sample) << " seconds\n";
	cout << "Average run time for Laasonen (dt = 0.025h) was: " << (l2 / sample) << " seconds\n";
	cout << "Average run time for Laasonen (dt = 0.05h) was: " << (l3 / sample) << " seconds\n";
	cout << "Average run time for Laasonen (dt = 0.1h) was: " << (l4 / sample) << " seconds\n\n";

	//  open file for average times
	ofs.open("results/timings.dat");
	ofs << "Average run time for Richardson was: " << (r / sample) << " seconds\n";
    ofs << "Average run time for Dufort was: " << (d / sample) << " seconds\n";
	ofs << "Average run time for Crank was: " << (c / sample) << " seconds\n";
	ofs << "Average run time for Laasonen (dt = 0.01h) was: " << (l1 / sample) << " seconds\n";
	ofs << "Average run time for Laasonen (dt = 0.025h) was: " << (l2 / sample) << " seconds\n";
	ofs << "Average run time for Laasonen (dt = 0.05h) was: " << (l3 / sample) << " seconds\n";
	ofs << "Average run time for Laasonen (dt = 0.1h) was: " << (l4 / sample) << " seconds\n\n";
	ofs.close();

	return 0;
}