#include "command.h"


void Command_Help()
{
	//	cout << " -t\t\tRun all tests to ensure program is correct (quiet)" << endl;
	//	cout << " -T\t\tsame as -t except detailed" << endl;

	cout << " -N #\t\tSelect numbered Next Sequence" << endl;
	cout << "\t 1. Digit Test" << endl;
	cout << " -V #\t\tSelect numbered Sequence Value" << endl;
	cout << "\t 1. Digit Value" << endl;
	cout << " -h \t\trun file as hexadecimal" << endl;
	cout << " -d #\t\tnumber of digits to test" << endl;
	cout << " -p \t\tremove predecimal" << endl;
	cout << " -b # \t\tmaximum size of a sequence" << endl;
	cout << " -c # \t\tmaximum number of classes (set base)" << endl;
	cout << " -s \t\tstream digits by overlapping bl	ocks" << endl;
	cout << " -C #\t\tcontiuous testing at intervals of #" << endl;
	cout << " -f <filename> \tselect input file for test" << endl;
	cout << " -o <filename> \tselect output file for test" << endl;

}

void Command_Summarry( Command_Options co )
{
	#ifdef DEBUG
		cout << "Command Setup" << endl;
		cout << "\tRun Tests: " << ((co.opt_test) ? "TRUE" : "FALSE") << "\t\tDetail Tests: " << ((co.opt_detail) ? "TRUE" : "FALSE") << endl;
		cout << "\tRemove Pre Decimal: " << ((co.opt_pre) ? "TRUE" : "FALSE") << endl;

		cout << "\tNext Sequence: " << co.next_seq << endl;
		cout << "\tSequence Value: " << co.seq_val << endl;

		cout << "\tDigits to Tests: " << co.digits << endl;
		cout << "\tBlock Size: " << co.block_size << endl;

		cout << "\tInput File: " << co.input_file << endl;
		cout << "\tOutput File: " << ((co.opt_file) ? "TRUE" : "FALSE") << endl;
		cout << "\tOutput File: " << co.output_file << endl;
		cout << "\tSummary File: " << ((co.opt_summary) ? "TRUE" : "FALSE") << endl;
		cout << "\tSummary File: " << co.summary_file << endl;
	#endif

}

void Command_Arguments( int argc, char **argv )
{

	bool menu = true;		// default, no options use cams
	bool in_file = false;// need input file to read

	Command_Options co;
	#ifdef DEBUG
		cout << "List Of Command Arguments" << endl;
	
		for ( int i = 0; i < argc; ++i )
			cout << "Command " << i << ":" << argv[i] << endl;
	#endif

	// parse command arguments
	for ( int i = 0; i < argc; ++i )
	{

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

				case 'c':
					co.max_class = atoi( argv[++i] );
					co.opt_base = true;
					break;

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

				case 'h':
					co.opt_hex2bin = true;
					break;

				case 'f':
					co.input_file = argv[++i];
					in_file = true;
					break;

				case 'o':
					co.opt_file = true;
					co.output_file = argv[++i];
					break;

				case 'q':
					co.opt_summary = true;
					co.summary_file = argv[++i];
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

		#ifdef DEBUG
			Command_Summarry( co );
		#endif


		Command_Execute( co );


	}
}


void Command_Execute( Command_Options co )
{
	// check testing parameters
//	if ( co.opt_test )
//		Full_Testing( co.opt_detail );

	// pointer to store results
	unsigned long long int *results;	

	// setup analysis parameter from command line arguments
	Analysis_Parameters ap;ap.remove_predecimal = co.opt_pre;
	ap.number_of_digits_to_test = co.digits;
	ap.max_sequence_size = co.block_size;
	ap.filename = co.input_file;

	// setup base and number of classes
	Set_Base( co, ap );
	
	// setup next sequence
	Next_Sequence ns = Set_Next_Sequence( co, ap );

	// setup sequence value
	Sequence_Value sv = Set_Sequence_Value( co, ap);

	// analyze number
	#ifdef DEBUG
		cout << "Analysis Parameters before Analyze_Number" << endl;
		Display_AP( ap );
	#endif

	// run analysis
	if ( co.opt_cont )
	{
		// setup output for continuous analysis
		ofstream outfile;

		if ( ap.number_of_classes_possible > MAX_SCREEN_CLASSES || co.opt_file )
		{	
			cout << "Continuous results are in file " << CONTINUOUS_LOG << " due to large number of classes." << endl;
			outfile.open( CONTINUOUS_LOG, ios::out );
		}

		results = Analyze_Number_Continuously( ns, sv, ap, co.granularity, outfile );
		outfile.close();
	}
	else
	{
		results = Analyze_Number( ns, sv, ap );
	}

	// display results
	Display_Results( co, ap, results );
	
	delete[] results;			// clean up memory

	#ifdef DEBUG
		cout << "Final Analysis Parameters" << endl;
		Display_AP( ap );
	#endif
}

void Set_Base( Command_Options co, Analysis_Parameters &ap )
{
	if ( co.opt_base )
		G_BASE = co.max_class;
	else
	{
		if ( co.opt_hex2bin )
			G_BASE = 2;
		else
			G_BASE = 10;
	}

	// set base
	ap.number_of_classes_possible = (unsigned long long int) pow( G_BASE, ap.max_sequence_size );

	if ( ap.number_of_classes_possible >= 1410065408 )		// number of classes is too large
	{
		cout << "Too many classes to support.  Reduce the maximum number of classes to track.";
		exit( 1 );
	}

}

Next_Sequence Set_Next_Sequence( Command_Options co, Analysis_Parameters &ap )
{
	// default next sequence function pointer
	Next_Sequence ns = &Get_Block_Sequence;
	
	switch ( co.next_seq )
	{
		case 1:
			if ( co.opt_stream ) // Stream Sequence
			{
				if ( co.opt_hex2bin )
					ns = &Get_Bin_Stream_Sequence;
				else 
					ns = &Get_Stream_Sequence;
			}
			else 	// Block Sequence
			{
				if ( co.opt_hex2bin )
					ns = &Get_Bin_Block_Sequence;
				else
					ns = &Get_Block_Sequence;
			}
			break;

		// add additional case labels here
		case 2:
			//break;

		default:
			cout << "Error: Unknown Get_Next_Sequence Function in command line" << endl;
			exit( 1 );
			break;

	}

	return ns;
}

Sequence_Value Set_Sequence_Value( Command_Options co, Analysis_Parameters &ap )
{
	// default sequence value function pointer
	Sequence_Value sv = &Get_Sequence_Digits_Base;

	switch ( co.seq_val )
	{
		case 1:
			//Sequence_Value
			sv = &Get_Sequence_Digits_Base;
			break;

		// add additional case labels here
		case 2:
			//break;

		default:
			cout << "Error: Unknown Get_Next_Sequence Function in command line" << endl;
			exit( 1 );
			break;
	}

	return sv;
}


void Display_Results( Command_Options co, Analysis_Parameters &ap, unsigned long long int *results )
{
	// display to screen only small results
	if ( ap.number_of_classes_possible > MAX_SCREEN_CLASSES )
		Display_Results_Full( results, ap, cout );				// summary of result
	else
		Display_Results_Partial( results, ap, cout );			// partial results sent to screen

																// output final results to file
	if ( co.opt_file )
	{
		ofstream result_file;

		cout << "Full results are in file " << co.output_file << "." << endl;
		result_file.open( co.output_file, ios::out );
		Display_Results_Full( results, ap, result_file );
		result_file.close();
	}

	if ( co.opt_summary )
	{
		ofstream result_file;

		cout << "Summary results are in file " << co.summary_file<< "." << endl;
		result_file.open( co.summary_file, ios::app );
		Display_Results_Partial( results, ap, result_file );
		result_file.close();
	}
}

void Display_Results_Full( unsigned long long int *results, Analysis_Parameters &ap, ostream &out )
{
	unsigned long long int sum = 0;

	out << "Chi Squared\t| " << "Digits\t";
	if ( ap.digits_tested >= 10000000 ) out << "\t";
	out << "|\t";

	for ( unsigned int i = 0; i < ap.number_of_classes_possible; ++i )
	{
		sum += results[i];
		out << i << "\t";
		if ( ap.digits_tested >= 10000000 ) out << "\t";
	}
	out << endl;

	Analyze_List al;
	al.Set_List( results, ap.number_of_classes_possible );

	out << al.Chi_Squared() << "\t\t| " << ap.digits_tested << "\t\t";
	if ( ap.digits_tested >= 10000000 ) out << "\t";
	out << "|\t";

	for ( unsigned int i = 0; i < ap.number_of_classes_possible; ++i )
	{
		out << results[i] << "\t";
		if ( ap.digits_tested >= 10000000 && results[i] < 10000000 ) out << "\t";
	}

	out << endl;


}

void Display_Results_Partial( unsigned long long int *results, Analysis_Parameters &ap, ostream &out )
{
	Analyze_List al;
	al.Set_List( results, ap.number_of_classes_possible );

	out << "Digits: " << al.Sum() << "\tChi-Squared: " << al.Chi_Squared() << endl;
}
