#ifndef COMMAND_H
#define COMMAND_H

#define MAX_SCREEN_CLASSES	16		// maximum number of classes that will be displayed on the screen, file output larger sets


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
		opt_summary = false;	// output a summary file

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

void Command_Arguments( int argc, char **argv );
void Command_Help();
void Command_Summarry( Command_Options co );
void Command_Execute( Command_Options co );

void Display_Results( unsigned long long int *results, Analysis_Parameters &ap, ostream &out );


#endif