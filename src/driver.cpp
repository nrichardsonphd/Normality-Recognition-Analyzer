/// \file
/// @file
/// Normality Recognition Analyzer
/// \author Dr. Nicholas Richardson



///////////////////////////////////////////////////////////////////////////////////////////////////
// Command Line Arguments
// This is a rough setup, no combining arguments
// Only use known sequence functions
// 
// nra.exe -t -T -N 2 -V 2 -p -s 5 -b 8 -f ../../data/Pi1K-dec.txt -r tmp.out
//
// -t		Run all tests to ensure program is correct (quiet)
// -T		same as -t except detailed
//
// -N #		Select numbered Next Sequence
//			1. Digit blocks
// -V #		Select numbered Sequence Value
//			1. Number value
//			2. 
// -h		hexadecimal input file, convert to binary
//
// -d #		Number of digits to test
// -r		remove predecimal
// -b #		maximum size of each sequence
// -c #		maximum number of classes
// -s		stream digits with overlapping blocks (nonoverlapping is default)
// 
// -f <filename>		select input file for test
// -o <filename>		select output file for test
// -q <filename>		quiet summary, only digits and X^2, no class values
//
// -C #		Continuous Testing, # is for granularity
///////////////////////////////////////////////////////////////////////////////////////////////////


#include <fstream>
#include <iostream>
#include <string>
#include <ctime>
#include <chrono>
using namespace std;

#include "setup.h"

// Setting up program
#include "analysis\analysis_parameters.h"
#include "common\cams.h"
#include "common\command.h"

#include "testing\testing.h"
#include "testing\Read_Number-test.h" 

#include "Get_Next_Sequence.h"
#include "Get_Sequence_Value.h"

#include "Analyze Number.h"
#include "analysis\Analyze_List.h"

#include "Sequence.h"



// Version Control Functions
string VERSION;				// store current version of program
void Git_Init();
string Git_Version_Number();



void Full_Testing( bool detail );

int main( int argc, char **argv)
{
	// Initialize for Version Control
	Git_Init();

	//time_t start = time();
	//cout << "Start Time: " << put_time( &start ) << endl;
	
	// command line arguments
	Command_Arguments( argc, argv );
	
	// end of program
	//ti//me_t end = time( nullptr );

	//cout << "Start Time:\t" << ctime( &start );
	//cout << "End Time:\t" << ctime( &end );
	//cout << "Total Time: " << end - start << endl;
	cout << endl;
	return 0;
}





void Full_Testing( bool detail )
{
	if ( detail )
	{
		cout << "Detailed Test: " << endl;
		Test_All( true );
		cout << endl;
	}
	else
	{
		cout << "Summary Test" << endl;
		Test_All( false );
		cout << endl;
	}
}

void Git_Init()
{
	VERSION = Git_Version_Number();
	cout << "Normality Recognition Analyzer " << RELEASE << endl;	
	cout << "Author: Dr. Nicholas M. Richardson" << endl;
	#ifdef DEBUG
		cout << "Development Build: " << VERSION << endl;
	#else
		cout << "Release: " << VERSION << endl;
	#endif
	cout << "----------------------------------" << endl << endl;


}
// This is used to keep track of revision numbers
// buildno.txt
string Git_Version_Number()
{
	// format of versions
	// <Version>.<Revision>.<Commit>.<Build>

	#ifdef DEBUG
		string tmp;
		ifstream in("../../buildno.txt", ios::in);
	
		if (!in)
		{
			cout << "Unable to open buildno.txt" << endl;
			tmp = "*.*.*.*";
			//exit(1);
		}
		else
		{
			int version;
			int revision;
			int commit;
			int build;

			in >> version;
			in.get();
			in >> revision;
			in.get();
			in >> commit;
			in.get();
			in >> build;
			in.close();

			tmp = to_string( version );
			tmp += ".";
			tmp += to_string( revision );
			tmp += ".";
			tmp += to_string( commit );
			tmp += ".";
			tmp += to_string( ++build );

			ofstream out( "../../buildno.txt", ios::out );
			if ( !out )
			{
				cout << "Unable to write buildno.txt" << endl;
				tmp = "*.*.*.*";
			}
			else
			{
				out << tmp << endl;
				out.close();
			}
		}

		return tmp;
	
	#else
		return RELEASE;
	#endif

}