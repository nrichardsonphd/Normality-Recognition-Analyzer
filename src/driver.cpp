/// \file
/// @file
/// Normality Recognition Analyzer
/// \author Dr. Nicholas Richardson

#define RELEASE "0.2.77:1245"		// Release version
//#define DEBUG						// Debug mode for development

#define MAX_SCREEN_CLASSES	16		// maximum number of classes that will be displayed on the screen, file output larger sets
#define _CRT_SECURE_NO_WARNINGS		// stop useless warnings



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
//
// -C #		Continuous Testing, # is for granularity
///////////////////////////////////////////////////////////////////////////////////////////////////


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

struct Command_Options
{
	bool opt_test = false,		// test all units
		opt_detail = false,		// detailed testing
		opt_pre = false,		// remove pre-decimal
		opt_cont = false,		// continuous testing
		opt_file = false,		// file output
		opt_base = false,		// manually specify base of file
		opt_stream = false,		// block v stream
		opt_hex2bin = false;	// convert hexadecimal file to binary input

	int next_seq = 1;
	int seq_val = 1;
	int digits = 1000;
	int block_size = 1;
	int max_class = 10;
	int granularity = 1;

};

void Command_Arguments( int argc, char **argv );	
void Command_Help();
void Command_Summarry( Command_Options co, string input_file, string output_file );
void Command_Execute( Command_Options co, string input_file, string output_file );

void Display_Results( unsigned long long int *results, Analysis_Parameters &ap, ostream &out );
void Full_Testing( bool detail );




// *** TODO Add Command line arguments

int main( int argc, char **argv)
{
	// Initialize for Version Control
	Git_Init();

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



void Command_Arguments( int argc, char **argv )
{

	bool menu = true;		// default, no options use cams
	bool in_file = false;// need input file to read

	Command_Options co;
	
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
					co.opt_test = true;
					co.opt_detail = true;
					break;

				case 't':			// quiet output
					co.opt_detail = false;
					co.opt_test = true;
					break;

				case 'r':			// remove pre decimal
					co.opt_pre = true;
					break;

				case 's':
					co.opt_stream = true;
					break;

				case 'd':			// number of digits to test
					co.digits = atoi( argv[++i] );
					break;

				case 'b':			// select maximum size of blocks
					co.block_size = atoi( argv[++i] );
					break;

				//case 'c':
				//	co.max_class = atoi( argv[++i] );
				//	co.opt_base = true;
				//	break;

				case 'C':			// continuous 
					co.opt_cont = true;
					co.granularity = atoi( argv[++i] );
					break;

				case 'N':			// select Next Sequence
					co.next_seq = atoi( argv[++i] );
					break;

				case 'V':			// select Sequence Value
					co.seq_val = atoi( argv[++i] );
					break;

				case 'f':
					input_file = argv[++i];
					in_file = true;					
					break;

				case 'o':
					co.opt_file = true;
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

		if ( !in_file )
		{
			cout << "Error: Need an input file for command line" << endl;
			exit( 1 );
		}

		#ifndef RELEASE
			Command_Summarry( co, input_file, output_file );
		#endif


		Command_Execute( co, input_file, output_file );


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
	cout << " -h \t\trun file as hexadecimal" << endl;
	cout << " -d #\t\tnumber of digits to test" << endl;
	cout << " -p \t\tremove predecimal" << endl;
	cout << " -b # \t\tmaximum size of a sequence" << endl;
//	cout << " -c # \t\tmaximum number of classes (set base)" << endl;
	cout << " -s \t\tstream digits by overlapping blocks" << endl;
	cout << " -C #\t\tcontiuous testing at intervals of #" << endl;
	cout << " -f <filename> \tselect input file for test" << endl;
	cout << " -o <filename> \tselect output file for test" << endl;

}

void Command_Summarry( Command_Options co, string input_file, string output_file )
{
	cout << "Command Setup" << endl;
	cout << "\tRun Tests: " << ((co.opt_test) ? "TRUE" : "FALSE") << "\t\tDetail Tests: " << ((co.opt_detail) ? "TRUE" : "FALSE") << endl;
	cout << "\tRemove Pre Decimal: " << ((co.opt_pre) ? "TRUE" : "FALSE") << endl;
	
	cout << "\tNext Sequence: " << co.next_seq << endl;
	cout << "\tSequence Value: " << co.seq_val << endl;
	
	cout << "\tDigits to Tests: " << co.digits << endl;
	cout << "\tBlock Size: " << co.block_size << endl;
	
	cout << "\tInput File: " << input_file << endl;
	cout << "\tOutput File: " << ((co.opt_file) ? "TRUE" : "FALSE") << endl;
	cout << "\tOutput File: " << output_file << endl;
}

void Command_Execute( Command_Options co, string input_file, string output_file )
{
	// check testing parameters
	if ( co.opt_test )
		Full_Testing( co.opt_detail );
	
	Analysis_Parameters ap;
	ap.remove_predecimal = co.opt_pre;
	ap.number_of_digits_to_test = co.digits;
	ap.max_sequence_size = co.block_size;
	ap.filename = input_file;

	
	// setup different function pointers based on arguments
	unsigned long long int *results;

	if ( co.opt_base )
	{
		G_BASE = co.max_class;
		ap.number_of_classes_possible = (unsigned int) pow( G_BASE, ap.max_sequence_size );
	}
	else
		ap.number_of_classes_possible = (unsigned int) pow( 10, ap.max_sequence_size );

	Sequence( *Next_Sequence )(Read_Number &rn, int digits);
	unsigned int( *Sequence_Value )(Sequence s);
	
	// default next sequence function pointer
	Next_Sequence = &Get_Block_Sequence;
	
	if ( co.next_seq == 1 )		
	{
		if ( co.opt_stream ) // Stream Sequence
		{
			if ( co.opt_hex2bin )
				Next_Sequence = &Get_Bin_Stream_Sequence;
			else
				Next_Sequence = &Get_Stream_Sequence;
		}
		else 	// Block Sequence
		{
			if ( co.opt_hex2bin )
				Next_Sequence = &Get_Bin_Block_Sequence;
			else
				Next_Sequence = &Get_Block_Sequence;
		}
			
	}
	else
	{
		cout << "Error: Unknown Get_Next_Sequence Function in command line" << endl;
		exit( 1 );
	}

	// default sequence value function pointer
	Sequence_Value = &Get_Sequence_Digits_Base;

	if ( co.seq_val == 1 )
	{
		Sequence_Value = &Get_Sequence_Digits_Base;
	}
	else
	{
		cout << "Error: Unknown Get_Next_Sequence Function in command line" << endl;
		exit( 1 );
	}
	
	ofstream outfile;
	
	if ( ap.number_of_classes_possible > MAX_SCREEN_CLASSES || co.opt_file )
	{
		if ( !co.opt_file )
		{
			co.opt_file = true;
			output_file = "../../logs/tmp.txt";
			cout << "Results are in file " << output_file << " due to large number of classes." << endl;
		}
		
		outfile.open( output_file, ios::out );
	}
	
	//Display_AP( ap );

	if ( co.opt_cont )
		results = Analyze_Number_Continuously( Next_Sequence, Sequence_Value, ap, co.granularity, cout );// outfile );
	else
		results = Analyze_Number( Next_Sequence, Sequence_Value, ap );
	
	
	//exit( 1 );
	if ( ap.number_of_classes_possible <= 200 )
		Display_Results( results, ap, cout );
	else
		if ( co.opt_file )
		{		
			outfile << endl << endl;
			//outfile << "********************************************************" << endl;
			outfile << "Final Results" << endl;
			Display_Results( results, ap, outfile );
			outfile << endl << endl;
			outfile.close();

		}
	
	if ( co.opt_file )	// output file exists
	{
		ofstream cloutfile( output_file, ios::app );
		Display_Results( results, ap, cloutfile );		
		cloutfile.close();
	}

	delete[] results;

	
	Display_AP( ap );
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
	unsigned long long int sum = 0;

	out << "Digits\t";
	if ( ap.digits_tested >= 10000000 ) out << "\t";
	out << "|\t";

	for ( unsigned int i = 0; i < ap.number_of_classes_possible; ++i )
	{
		sum += results[i];
		out << i << "\t";
		if ( ap.digits_tested >= 10000000 ) out << "\t";
	}
	out << "\t\t| Chi Squared" << endl;
	

	out << ap.digits_tested << "\t|\t";
	for ( unsigned int i = 0; i < ap.number_of_classes_possible; ++i )
	{
		out << results[i] << "\t";
		if ( ap.digits_tested >= 10000000  && results[i] < 10000000 ) out << "\t";
	}
	out << "\t\t| ";

	Analyze_List al;
	al.Set_List( results, ap.number_of_classes_possible );
	out << al.Chi_Squared() << ": total " << sum << endl;



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
		ifstream in("../../buildno.txt", ios::in);
	
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

		ofstream out("../../buildno.txt", ios::out);
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
	
	#else
		return RELEASE;
	#endif

}