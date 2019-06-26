#include "command.h"


void Command_Help()
{
	cout << endl;
	cout << "Normality Recognition Analyzer Version " << RELEASE << endl << endl;

	// General setup
	cout << "nra.exe - {hrsF} -{NVdbcC} #  - o <full file output> <input file>" << endl;
	cout << "nra.exe -N 2 -V 2 -r -g 5 -b 8 -r -o tmp.out -f ../../data/Pi1K-dec.txt" << endl;
	cout << "nra.exe\t\thelp menu" << endl << endl;
	
	// Files
	cout << "File I/O" << endl;
	cout << " -f <filename> \tselect input file for test" << endl;
	//	cout << " -o <filename> \tselect output file for test" << endl;
	cout << " -h \t\trun file as hexadecimal" << endl;
	cout << endl;

	// Analysis
	cout << "Analysis" << endl;
	cout << " -d #\t\tSpecify the number of sequences to read from file to test" << endl;
	cout << " -p \t\tRemove all numbers preceding the decimal point in the file.  \n\t\t3.14159 will remove the 3 and start on 1 being the 1st digit tested." << endl;
	cout << " -b # \t\tSpecify the maximum size of a sequence.  Depending on Next_Sequence, \n\t\tthe size may change, but this is the maximum it can be" << endl;
	cout << " -c # \t\tSpecify the maximum number of classes.  This is dependent on Sequence Value" << endl;
	cout << endl;

	// Logging
	cout << "Logging" << endl;
	cout << " -C #\t\tContiuous testing at intervals of #.  Every N digits will have a record in the log file." << endl;
	cout << endl;

	// Customize Sequence
	cout << "Customize Sequences" << endl;
	cout << " -N #\t\tSelect numbered Next Sequence" << endl;
	cout << "\t\t 1. Digit block \tsequences consist of nonoverlapping blocks of numbers" << endl;
	cout << "\t\t 2. Digit stream \tsliding window of sequences" << endl;
	cout << "\t\t 3. Random <not implemented>" << endl;
	cout << " -V #\t\tSelect numbered Sequence Value" << endl;
	cout << "\t\t 1. Digit Value \tThe numerical value based on the sequence block, base N" << endl;
	cout << "\t\t 2. Poker Value <not implemented>" << endl;
	cout << endl;
	

//	cout << " -t\t\tRun all tests to ensure program is correct (quiet)" << endl;
//	cout << " -T\t\tsame as -t except detailed" << endl;
}

void Command_Summarry( Command_Options co )
{

	cout << "Command help for nra.  This section may be out of date, check command.h file for use." << endl;
//	exit(1);
	#ifdef DEBUG
		cout << "Command Setup" << endl;
		cout << "\tRun Tests: " << ((co.opt_test) ? "TRUE" : "FALSE") << "\t\tDetail Tests: " << ((co.opt_detail) ? "TRUE" : "FALSE") << endl;
		cout << "\tRemove Pre Decimal: " << ((co.opt_pre) ? "TRUE" : "FALSE") << endl;

		cout << "\tNext Sequence: " << co.next_seq << endl;
		cout << "\tSequence Value: " << co.seq_val << endl;

		cout << "\tNumber of Sequences to Tests: " << co.number_sequences << endl;
		cout << "\tBlock Size: " << co.block_size << endl;

		cout << "\tInput File: " << co.input_file << endl;
	//	cout << "\tOutput File: " << ((co.opt_file) ? "TRUE" : "FALSE") << endl;
	//	cout << "\tOutput File: " << co.output_file << endl;
	//	cout << "\tSummary File: " << ((co.opt_summary) ? "TRUE" : "FALSE") << endl;
	//	cout << "\tSummary File: " << co.summary_file << endl;
	#endif

}

void Command_Arguments( int argc, char **argv )
{
	// must check
	cout << "Testing updated input needed" << endl;
	//exit(1);

	bool menu = false;		// default, no options use cams
	bool in_file = false;	// need input file to read

	Command_Options co;
	#ifdef DEBUG
		cout << "List Of Command Arguments" << endl;
	
		for ( int i = 0; i < argc; ++i )
			cout << "Command " << i << ":" << argv[i] << endl;
	#endif

	if (argc == 1)	// no arguments
	{
		Command_Help();
		exit(1);
	}

	// parse command arguments
	for ( int i = 0; i < argc; ++i )
	{

		if ( argv[i][0] == '-' )
		{
			menu = false;

			switch ( argv[i][1] )
			{
				// Next Sequence
				case 'N':										// select Next Sequence function
					co.next_seq = atoi( argv[++i] );
					break;

				// Sequence Value
				case 'V':										// select Sequence Value function
					co.seq_val = atoi( argv[++i] );
					break;		
								
				// Flag options
				case 'r':										// remove pre decimal
					co.opt_pre = true;
					break;
			
				case 'd':										// number of sequences to test
					co.number_sequences = atoi( argv[++i] );
					break;

				case 'b':										// select size of blocks, if variable must be maximum size
					co.block_size = atoi( argv[++i] );			// depends on Next Sequence
					break;

				case 'c':										// select the number of possible classed, default is the base
					co.max_class = atoi( argv[++i] );			// depends on Sequence Value
					break;
				
				case 'g':										// granularity of intermittent results
					co.opt_cont = true;							// default in number of sequences to test
					co.granularity = atoi( argv[++i] );
					break;
			






				case 'h':										// treat input file is hexadecimal and convert to binary on the fly
					co.opt_hex2bin = true;
					break;

				

			

		


				// specify file output
				case 'f':										// input file (required)
					co.input_file = argv[++i];
					in_file = true;
					break;

				case 'o':										// full output file
					//co.opt_file = true;
				//	co.output_file = argv[++i];
					break;

				case 'q':										// summary output file
					//co.opt_summary = true;
					//co.summary_file = argv[++i];
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
		co.opt_test = true;
		co.opt_detail = true;
	}
	else
	{

		if ( !in_file )
		{
			cout << "Error: Need an input file for command line. Use -f to specify" << endl;
			exit( 1 );
		}

		#ifdef DEBUG
			Command_Summarry( co );
		#endif


		Command_Execute( co );


	}
}

// Take command options and run program
void Command_Execute( Command_Options co )
{
	
	// check testing parameters
	if ( co.opt_test )
	{
		cout << "Testing Data Not Set up currently" << endl;
		//Full_Testing( co.opt_detail );
		return;
	}
	
	// pointer to store results
	unsigned long long int *results;	

	// setup analysis parameter from command line arguments
	Analysis_Parameters ap;
	
	ap.remove_predecimal = co.opt_pre;
	ap.number_of_digits_to_test = co.number_sequences;
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
		cout << "Continuous Testing: All digit counts from every " << co.granularity << " sequences will be tested." << endl;
		
		// setup output for continuous analysis
		ofstream outfile;

		if (ap.number_of_classes_possible > MAX_SCREEN_CLASSES)
		{
			cout << "Warning: Output may become very large.  The maximum number of classes that can be displayed onscreen is " << MAX_SCREEN_CLASSES << endl;
			cout << "Class Output will be recorded to file, no class output on screen." << endl;
		}

		// results will be appended to file every N = granularity
		results = Analyze_Number_Continuously( ns, sv, ap, co.granularity );
		outfile.close();
	}
	else
	{
		results = Analyze_Number( ns, sv, ap );
	}
	
	// display results to screen
	Display_Results( co, ap, results );
	
	delete[] results;			// clean up memory


}

void Set_Base( Command_Options co, Analysis_Parameters &ap )
{
	
	if ( co.opt_hex2bin )
		G_BASE = 2;
	else
		G_BASE = 10;
	

	// set base
	ap.number_of_classes_possible = (unsigned long long int) pow( G_BASE, ap.max_sequence_size );

	if	( ap.number_of_classes_possible >= 1410065408 || ap.max_sequence_size > MAX_SEQUENCE_SIZE ||							// number of classes is too large
		( co.opt_hex2bin && ap.max_sequence_size > MAX_BINARY ) || ( !co.opt_hex2bin & ap.max_sequence_size > MAX_DECIMAL)  )	// limits for binary and decimal size	
	{
		cout << "ERROR: Too many classes for the size of the sequence." << endl;
		cout << ap.number_of_classes_possible << " is too many classes to support.  Reduce the maximum number of classes or maximum sequence size to fix." << endl;
		cout << "The maximum size of the sequence is " << ap.max_sequence_size << " and must be less than " << MAX_SEQUENCE_SIZE << endl;
		cout << "A maximum sequence size of " << MAX_DECIMAL << " for decimal files and " << MAX_BINARY << " for hexadecimal to binary files." << endl;
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
			if ( co.opt_hex2bin )
				ns = &Get_Bin_Stream_Sequence;
			else 
				ns = &Get_Stream_Sequence;
			
			if ( co.opt_hex2bin )
				ns = &Get_Bin_Block_Sequence;
			else
				ns = &Get_Block_Sequence;
			break;

		// add additional case labels here
		case 2:
			cout << "Next Sequence 2 not implemented." << endl;
			exit(1);
			break;

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
			cout << "Sequence Value 2 not implemented." << endl;
			exit(1);
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
	if ( ap.number_of_classes_possible < MAX_SCREEN_CLASSES )
		Display_Results_Full( results, ap, cout );				// summary of result
	else
		Display_Results_Partial( results, ap, cout );			// partial results sent to screen

																// output final results to file
}

void Display_Results_Full( unsigned long long int *results, Analysis_Parameters &ap, ostream &out )
{
	unsigned long long int sum = 0;

	out << "Chi Squared\t| " << "Seqnc's\t";
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

	out << al.Chi_Squared() << "\t\t| " << ap.sequences_tested << "\t\t";
	if ( ap.sequences_tested >= 10000000 ) out << "\t";
	out << "|\t";

	for ( unsigned int i = 0; i < ap.number_of_classes_possible; ++i )
	{
		out << results[i] << "\t";
		if ( ap.sequences_tested >= 10000000 && results[i] < 10000000 ) out << "\t";
	}

	out << endl;

	// Differential
	unsigned long long int ex = ap.sequences_tested / ap.number_of_classes_possible;
	out << "\t\t| E(x) = " << ex << "\t";
	if (ap.sequences_tested >= 10000000) out << "\t";
	out << "|\t";

	for (unsigned int i = 0; i < ap.number_of_classes_possible; ++i)
	{
		if (results[i] > ex )
			out << "+" << results[i] - ex << "\t";
		else if (results[i] < ex )
			out << "-" << ex - results[i] << "\t";
		else
			out << "0" << "\t";
		
		if (ap.sequences_tested >= 10000000 && results[i] < 10000000) out << "\t";
	}

	out << endl;

}

void Display_Results_Partial( unsigned long long int *results, Analysis_Parameters &ap, ostream &out )
{
	Analyze_List al;
	al.Set_List( results, ap.number_of_classes_possible );

	out << "Seqnc's: " << al.Sum() << "\tChi-Squared: " << al.Chi_Squared() << endl;
}
