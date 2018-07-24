#ifndef COMMAND_H
#define COMMAND_H

#define MAX_SCREEN_CLASSES		16								// maximum number of classes that will be displayed on the screen, file output larger sets

#define CONTINUOUS_LOG			"../../logs/continuous.txt"		// only for continuous output to file
#define FULL_LOG				"../../logs/full.txt"			// full output file name
#define RUN_LOG					"../../logs/summary.txt"		// summary output file name

///////////////////////////////////////////////////////////////////////////////////////////////////
// Command Line Arguments
// This is a rough setup, no combining arguments
// Only use known sequence functions
//
// nra.exe -{hrsF} -{NVdbcC} # -f <input file> -o <full file output> -q <summary file>
// nra.exe -N 2 -V 2 -s 5 -b 8 -f ../../data/Pi1K-dec.txt -r tmp.out
//
// -N #					Select numbered Next Sequence
//							1. Digit blocks
//							2. Random (not implemented)
//							3. etc ...	These are to be expanded by user research
//
// -V #					Select numbered Sequence Value
//							1. Number Value
//							2. Poker Value (not implemented)
//							3. etc ...	These are to be expanded by user research
//
// -r					remove predecimal
// -h					hexadecimal input file, converted to binary on the fly
// -s					stream digits with overlapping blocks (nonoverlapping is default)
// -F					select full results for continuous testing, default is only important results
//
// -d #					Number of digits to test ( binary or decimal )
// -b #					size of each sequence
// -c #					number of classes ( default is 2^n (hex) or 10^n(dec) where n is size of sequence )
// -C #					Continuous Testing, # is for granularity how often to calculate results
//
// -f <filename>		select input file for test
// -o <filename>		select output file for test
// -q <filename>		quiet summary, only digits and X^2, no class values
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
using namespace std;
#include "../setup.h"

#include "../Analyze Number.h"

struct Command_Options
{
	bool opt_test = false,		// test all units
		opt_detail = false,		// detailed testing
		opt_pre = false,		// remove pre-decimal
		opt_cont = false,		// continuous testing
		opt_file = false,		// file output
		opt_base = false,		// manually specify base of file
		opt_stream = false,		// block v stream
		opt_hex2bin = false,	// convert hexadecimal file to binary input
		opt_summary = false,	// output a summary file
		opt_full = false;		// select to record full results

	int next_seq = 1;
	int seq_val = 1;
	int digits = 1000;
	int block_size = 1;
	int max_class = 10;
	int granularity = 1;

	// files
	string input_file = "default.in";
	string output_file = "constant_analyzer.out";
	string summary_file = "summary.out.compressed";


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