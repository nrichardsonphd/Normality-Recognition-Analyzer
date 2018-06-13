/// @file
#ifndef CAMS_CPP
#define CAMS_CPP
#include "cams.h"


Analysis_Parameters Setup_Parameters()
{
	Analysis_Parameters ap;
	cout << "Welcome to Constant Analyzer Menu System (CAMS)" << endl;

	do
	{
		Display_AP(ap);			
		cout << "1. Select Constant" << endl;
		cout << "2. Next Group" << endl;
		cout << "3. Group Value" << endl;
		cout << "4. Group Size" << endl;
		cout << "5. Number of Groups" << endl;
		cout << "6. Number of Digits" << endl;
		cout << "7. Base" << endl;
		cout << "8. Pre Decimal" << endl;
		cout << "9. Custom File" << endl;
		cout << ". Exit" << endl;

		cout << "Select Option: ";
		
		// Start Project
		/// select parallelization
		//Select_Parallel(ap);

		/// select constant to analyze
		//Select_Constant(ap);
		// pi, e, other, .. decimal/hex
		// file / generated
		// primes

		// setup get next digit


		/// select method how to analyze
		//Select_Analysis_Method(ap);
		// N-digit, poker, other ...
		// random search
		// check/compare
		// display only

		// setup get next group/class
	} 
	while (false);

	cout << "Sorry, but CAMS is not implemented yet." << endl;


	return ap;

}
void Select_Parallel(Analysis_Parameters ap)
{
	cout << "Parallelization not implemented." << endl;
}

void Select_Constant(Analysis_Parameters ap)
{
	string buffer;
	int option;

	cout << "Please select a constant to run an analysis." << endl;
	ifstream in("../menus/constants.txt", ios::in);
	if (!in)
	{
		cout << "Unable to open constants menu file." << endl;
		return;
	}

	int i = 0;

	while ( !in.eof() )
	{
		getline(in, buffer);
		cout << i++ << " " << buffer << endl;
	}

	in.close();
	
	cout << "Select a constant option: ";
	cin >> option;

	switch (option)
	{
	case CUSTOM_FILE: 		// get file name
		cout << "Enter filename path: ";
		cin >> CONSTANTS_FILES[CUSTOM_FILE];
		ap.filename = CONSTANTS_FILES[CUSTOM_FILE];
		break;
	case PI:				// set to pi file
		ap.filename = CONSTANTS_FILES[PI];
		break;
	case E:
		ap.filename = CONSTANTS_FILES[E];
		break;
	default:
		cout << "Not an option." << endl;
	};

}

void Select_Analysis_Method(Analysis_Parameters ap)
{
	cout << "Analysis Method not implemented." << endl;
}

void Select_Process_Interval(Analysis_Parameters ap)
{
	cout << "Process Interval not implemented." << endl;
}

void Display_Results(Analysis_Parameters ap)
{
	cout << "Display Results not implemented." << endl;
}

#endif