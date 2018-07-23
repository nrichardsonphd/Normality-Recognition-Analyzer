/// \file
/// @file
/// Normality Recognition Analyzer
/// \author Dr. Nicholas Richardson

#define _CRT_SECURE_NO_WARNINGS



#include <fstream>
#include <iostream>
#include <string>
#include <ctime>
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

	time_t const start = std::time(NULL);
	
	cout << "Start Time: " << ctime(&start) << endl;
	
	// command line arguments
	Command_Arguments( argc, argv );
	
	// end of program
	time_t end = time( nullptr );

	cout << "Start Time:\t" << ctime( &start );
	cout << "End Time:\t" << ctime( &end );
	cout << "Total Time: " << end - start << endl;
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