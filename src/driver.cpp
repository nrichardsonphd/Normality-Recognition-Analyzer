/// \file
/// @file
/// Normality Recognition Analyzer
/// \author Dr. Nicholas Richardson


/// Default Testing Parameters
/// Place in Project Properpties -> Debug -> Command Arguments
/// -d 1000000 -b 1 -C 1 -f ../../data/Pi-dec-1M.txt -o ../../logs/debug.txt -q ../../logs/summary.txt


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
	#ifdef TESTING
		cout << "Testing Mode" << endl;
		Command_Options co;
		co.opt_pre = true;										// remove pre decimal
		
		//****co.opt_block = true;
		

//		co.opt_full = false;									// full output, file may get large
		co.opt_hex2bin = false;									// treat hexadecimal file as binary, convert on fly
		
		// stream digits tested
		// block digits*blocksize tested
		co.number_sequences = 700;										// number of digits to test
		co.block_size = 1;										// select size of block, maximum if using variable sizes
		co.max_class = 16;										// number of possible classifications, (default base)
		
		co.opt_base = true;//?

		//*** test every $granularity or only test final result
		co.opt_cont = true;										// continuous testing on interval
		co.granularity = 1;
		
		// defaults
		co.next_seq = 1;										// select next sequence function 1. 2. 3.?
		co.seq_val = 1;											// select sequence value function 1. 2. 3.?
	
		co.input_file = "../../data/pi1k-hex.txt";				// input file (required)
	

//		co.output_file = "../../results/pi1k-dec-full.txt";		// output file
//		co.opt_file = true;
		
//		co.opt_summary = true;
//		co.summary_file = "../../results/pi1k-dec-sum.txt";		// summary output file

		Command_Summarry(co);
		Command_Execute(co);
		
	#else
		Command_Arguments( argc, argv );
	#endif

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