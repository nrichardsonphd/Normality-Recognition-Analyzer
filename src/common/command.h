#ifndef COMMAND_H
#define COMMAND_H

//#define MAX_SCREEN_CLASSES		16								// maximum number of classes that will be displayed on the screen, file output larger sets

#define CONTINUOUS_LOG			"../../logs/continuous.txt"		// only for continuous output to file
#define FULL_LOG				"../../logs/full.txt"			// full output file name
#define RUN_LOG					"../../logs/summary.txt"		// summary output file name

///////////////////////////////////////////////////////////////////////////////////////////////////
// Command Line Arguments
// This is a rough setup, no combining arguments
// Only use known sequence functions
// Output will be displayed to screen and recorded in log files
//
// nra.exe -{hrsF} -{NVdbcC} # -o <full file output> <input file>
// nra.exe -N 2 -V 2 -r -g 5 -b 8 -r -o tmp.out ../../data/Pi1K-dec.txt 
//
// -N #					Select numbered Next Sequence
//							0. Custom (user implemented CUSTOM_NEXT_SEQUENCE()
//							1. Digit block
//							2. Digit Stream
//							3. Random (not implemented)
//							4. etc ...	These are to be expanded by user research
//
// -V #					Select numbered Sequence Value
//							0. Custom (user implemented) CUSTOM_SEQUENCE_VALUE()
//							1. Number Value
//							2. Poker Value (not implemented)
//							3. etc ...	These are to be expanded by user research
//
// -r					remove predecimal
// -d #					Number of sequences to test 
// -b #					maximum size of each sequence ( dependent on Next_Sequence )
// -c #					number of classes ( dependent on Sequence_Value )
//
// -g #					Continuous Testing, # is for granularity how often to calculate results
//
// <filename>			input file, i.e. input.in: File should be in binary/Hexadecimal or decimal
// -h					hexadecimal input file, converted to binary on the fly
//
// -o <filename>		select output file for test, overide auto logs (Not Implemented)
//
// -t					Diagnostic Test (not implemented)
// -T					Diagnostic Test (not implemented)
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
using namespace std;
#include "../setup.h"

#include "../Analyze Number.h"
#include "../analysis/Constant_Analysis.h"
struct Command_Options
{
	// Diagnostic Testing:
	bool opt_test = false;		// for test all units
	bool opt_detail = false;	// Diagnostic Testing: detailed testing

	// Files I/O
	string input_file = "default.in";		// this file contains the digits to be read
	string output_file = "custom.out";		// this is a custom output file in addition to default logs ***Not implemented
											// must assign options for output: final, continuous min/max, full, ... TBD

											// binary files are stored as hexadecimal, when reading the remaining bits are remembered
	bool opt_hex2bin = false;				// convert hexadecimal file to binary input (Needed when file is in hex
											// Hexadecimal will be binary with a group of 4 bits

	// Analysis Options
	int next_seq = 1;						// Specify Next Sequence Function
	int seq_val = 1;						// Specify Sequence Value Function
			
	int number_sequences = 1000;			// number of sequences to test	
	bool opt_pre = false;					// remove pre-decimal
	int block_size = 1;						// maximum size of sequence block, used by Next Sequence function
	int max_class = 10;						// total number of classifications, depends on sequence value function

	// Logging Options
	bool opt_cont = false;					// continuous testing, if false, only final results will be displayed
	int granularity = 1;					// Every n blocks is analyzed 

};

typedef Sequence( *Next_Sequence )(Read_Number &rn, int digits);
typedef unsigned int( *Sequence_Value )(Sequence s);

void Command_Arguments( int argc, char **argv );
void Command_Help();
void Command_Summarry( Command_Options co );
void Command_Execute( Command_Options co );


// setup base and number of classes
// setup next sequence
// setup sequence value
// setup output

// analyze number

// display results

void Set_Base( Command_Options co, Analysis_Parameters &ap );
Next_Sequence Set_Next_Sequence( Command_Options co, Analysis_Parameters &ap );
Sequence_Value Set_Sequence_Value( Command_Options co, Analysis_Parameters &ap );

void Display_Results( Command_Options co, Analysis_Parameters &ap, unsigned long long int *results );

void Display_Results_Full( unsigned long long int *results, Analysis_Parameters &ap, ostream &out );
void Display_Results_Partial( unsigned long long int *results, Analysis_Parameters &ap, ostream &out );


#endif