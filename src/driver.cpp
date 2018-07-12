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
// Setting up program
#include "analysis\analysis_parameters.h"
#include "common\cams.h"

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

void Command_Arguments( int argc, char **argv );	
void Command_Help();
void Command_Summarry( bool opt_test, bool opt_detail, bool opt_pre, bool opt_file, int next_seq, int seq_val, int seq_tests, int block_size, string input_file, string output_file ); 
void Command_Execute( bool opt_test, bool opt_detail, bool opt_pre, bool opt_file, int next_seq, int seq_val, int seq_tests, int block_size, string input_file, string output_file );

void Display_Results( unsigned long long int *results, Analysis_Parameters &ap, ostream &out );
void Full_Testing( bool detail );




// *** TODO Add Command line arguments

int main( int argc, char **argv)
{
	// Initialize for Version Control
	Git_Init();
	Sequence_Test();
	exit( 1 );
	time_t start = time( nullptr );
	cout << "Start Time: " << ctime( &start ) << endl;
	
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
// -V #		Select numbered Sequence Value
//
// -p		remove predecimal
// -s #		number of sequences to test
// -b #		size of each sequence
//
// -?		nonoverlapping blocks of digits
// -?		stream digits with overlapping blocks
// 
// -f <filename>		select input file for test
// -r <filename>		select output file for test
//
// -c		Continuous Testing
// -g #		granularity for continuous testing
///////////////////////////////////////////////////////////////////////////////////////////////////
void Command_Arguments( int argc, char **argv )
{

	bool menu = true;		// default, no options use cams

	bool opt_test = false,
		opt_detail = false,
		opt_pre = false,
		opt_cont = false,
		opt_file = false;

	int next_seq = 1;
	int seq_val = 1;
	int seq_tests = 1000;
	int block_size = 1;
	int granularity = 1;

	string input_file = "default.in";
	string output_file = "constant_analyzer.out";

	// parse command arguments
	for ( int i = 0; i < argc; ++i )
	{
		//cout << "Command " << i << ":" << argv[i] << endl;

		if ( argv[i][0] == '-' )
		{
			menu = false;

			switch ( argv[i][1] )
			{
				case 'T':			// detailed test
					opt_test = true;
					opt_detail = true;
					break;

				case 't':			// quiet output
					opt_detail = false;
					opt_test = true;
					break;

				case 'p':			// remove pre decimal
					opt_pre = true;
					break;

				case 's':			// select number of sequence 
					seq_tests = atoi( argv[++i] );
					break;

				case 'b':			// select maximum size of blocks
					block_size = atoi( argv[++i] );
					break;

				case 'N':			// select Next Sequence
					next_seq = atoi( argv[++i] );
					break;

				case 'V':			// select Sequence Value
					seq_val = atoi( argv[++i] );
					break;

				case 'f':
					input_file = argv[++i];
					break;

				case 'r':
					opt_file = true;
					output_file = argv[++i];
					break;

				default:
					cout << "ERROR: Unknown Command:" << argv[i] << endl;
			};
		}
	}

	if ( menu )
	{
		// go to cams menu setup
		cout << "Menu not implemented, use command line arguments" << endl;
		Command_Help();
	}
	else
	{
		Command_Summarry( opt_test, opt_detail, opt_pre, opt_file, next_seq, seq_val, seq_tests, block_size, input_file, output_file );

		Command_Execute( opt_test, opt_detail, opt_pre, opt_file, next_seq, seq_val, seq_tests, block_size, input_file, output_file );


	}
}

void Command_Help()
{
	cout << " -t\t\tRun all tests to ensure program is correct (quiet)" << endl;
	cout << " -T\t\tsame as -t except detailed" << endl;

	cout << " -N #\t\tSelect numbered Next Sequence" << endl;
	cout << "\t 1. Digit Test" << endl;
	cout << " -V #\t\tSelect numbered Sequence Value" << endl;
	cout << "\t 1. Digit Value" << endl;

	cout << " -p \t\tremove predecimal" << endl;
	cout << " -s # \t\tnumber of sequences to test" << endl;
	cout << " -b # \t\tsize of each sequence" << endl;

	cout << " -f <filename> \tselect input file for test" << endl;
	cout << " -r <filename> \tselect output file for test" << endl;

}

void Command_Summarry( bool opt_test, bool opt_detail, bool opt_pre, bool opt_file, int next_seq, int seq_val, int seq_tests, int block_size, string input_file, string output_file )
{
	cout << "Command Setup" << endl;
	cout << "\tRun Tests: " << ((opt_test) ? "TRUE" : "FALSE") << "\t\tDetail Tests: " << ((opt_detail) ? "TRUE" : "FALSE") << endl;
	cout << "\tRemove Pre Decimal: " << ((opt_pre) ? "TRUE" : "FALSE") << endl;
	
	cout << "\tNext Sequence: " << next_seq << endl;
	cout << "\tSequence Value: " << seq_val << endl;
	
	cout << "\tSequence Tests: " << seq_tests << endl;
	cout << "\tBlock Size: " << block_size << endl;
	
	cout << "\tInput File: " << input_file << endl;
	cout << "\tOutput File: " << ((opt_file) ? "TRUE" : "FALSE") << endl;
	cout << "\tOutput File: " << output_file << endl;
}

void Command_Execute( bool opt_test, bool opt_detail, bool opt_pre, bool opt_file, int next_seq, int seq_val, int seq_tests, int block_size, string input_file, string output_file )
{
	// check testing parameters
	if ( opt_test )
		Full_Testing( opt_detail );

	Analysis_Parameters ap;
	ap.remove_predecimal = opt_pre;
	ap.number_of_sequences_to_test = seq_tests;
	ap.max_sequence_size = block_size;
	ap.filename = input_file;


	// setup different function pointers based on arguments
	unsigned long long int *results;
	ap.total_number_of_classes = (unsigned int) pow( 10, ap.max_sequence_size );

	Sequence( *Next_Sequence )(Read_Number &rn, int digits);
	unsigned int( *Sequence_Value )(Sequence s);
	
	// default sequence function pointers
	Next_Sequence = &Get_Block_Sequence;
	Sequence_Value = &Get_Sequence_Digits_Base_10;

	if ( next_seq == 1 )
		Next_Sequence = &Get_Block_Sequence;
	else if ( next_seq == 2 )
		Next_Sequence = &Get_Stream_Sequence;

	if ( seq_val == 1 )
		Sequence_Value = &Get_Sequence_Digits_Base_10;

	results = Analyze_Number( Next_Sequence, Get_Sequence_Digits_Base_10, ap );
	
	if ( ap.total_number_of_classes <= 20 )
		Display_Results( results, ap, cout );
	else
		if ( !opt_file )
		{
			string filename = "../../logs/tmp.txt";
			cout << "Results are in file " << filename << " due to large number of classes." << endl;
			
			ofstream outfile( filename, ios::out );
			Display_Results( results, ap, outfile );
			outfile.close();
		}
	
	if ( opt_file )	// output file exists
	{
		ofstream cloutfile( output_file, ios::out );
		Display_Results( results, ap, cloutfile );		
		cloutfile.close();
	}

	delete[] results;

	// Start Project
	/// select parallelization
	//Select_Parallel(ap);				// CAMS

	/// select constant to analyze
	//Select_Constant(ap);				// CAMS
	// pi, e, other, .. decimal/hex
	// file / generated
	// primes

	// setup get next digit


	/// select method how to analyze
	//Select_Analysis_Method(ap);		// CAMS
	// N-digit, poker, other ...
	// random search
	// check/compare
	// display only

	// setup get next group/class

	//cout << "Current Analysis Parameters" << endl;
	//Display_AP(ap);

	/// process
	// do analysis
	//Select_Process_Interval(ap);
	// one time run for N digits
	// report every kth digit ( complete analysis on up to k digits each time )
	// report every digit with continuous calculation ( save time, some calculations not possible ie median/mode)

	/// display results
	//Display_Results(ap);
	// chi, mead median, ....
	// other statistics based on classifications

	/// verify testing correct?
}

void Display_Results( unsigned long long int *results, Analysis_Parameters &ap, ostream &out )
{
	out << "Digits\t";
	if ( ap.digits_tested >= 10000000 ) out << "\t";
	out << "|\t";

	for ( unsigned int i = 0; i < ap.total_number_of_classes; ++i )
	{
		out << i << "\t";
		if ( ap.digits_tested >= 10000000 ) out << "\t";
	}
	out << "\t\t| Chi Squared" << endl;
	

	out << ap.digits_tested << "\t|\t";
	for ( unsigned int i = 0; i < ap.total_number_of_classes; ++i )
	{
		out << results[i] << "\t";
		if ( ap.digits_tested >= 10000000  && results[i] < 10000000 ) out << "\t";
	}
	out << "\t\t| ";

	Analyze_List al;
	al.Set_List( results, ap.total_number_of_classes );
	out << al.Chi_Squared() << endl;

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
	cout << "Normality Recognition Analyzer" << endl;	
	cout << "Author: Dr. Nicholas M. Richardson" << endl;
	cout << "Development Build: " << VERSION << endl;
	cout << "----------------------------------" << endl << endl;


}
// This is used to keep track of revision numbers
// buildno.txt
string Git_Version_Number()
{
	// format of versions
	// <Version>.<Revision>.<Commit>.<Build>

	ifstream in("../../logs/buildno.txt", ios::in);
	if (!in)
	{
		cout << "Unable to open buildno.txt" << endl;
		exit(1);
	}
	int version;
	int revision;
	int commit;
	int build;
	string tmp;
	in >> version;
	in.get();
	in >> revision;
	in.get();
	in >> commit;
	in.get();
	in >> build;
	in.close();

	tmp = to_string(version);
	tmp += ".";
	tmp += to_string(revision);
	tmp += ".";
	tmp += to_string(commit);
	tmp += ".";
	tmp += to_string(++build);

	ofstream out("../../logs/buildno.txt", ios::out);
	if (!out)
	{
		cout << "Unable to write buildno.txt" << endl;
		tmp = "*.*.*.*";
	}
	else
	{
		out << tmp << endl;
		out.close();
	}

	return tmp;
}