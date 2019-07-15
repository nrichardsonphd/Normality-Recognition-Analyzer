/// @file
#include "Analyze Number.h"

unsigned long long int *Get_Next_Set_Of_Sequences( Sequence( *Next_Sequence )(Read_Number &rn, int digits), unsigned int( *Sequence_Value )(Sequence s), 
													Analysis_Parameters &ap, Read_Number &rn, unsigned long long int number_of_digits, bool show_progress )
{
	unsigned long long int *tmp_results = new unsigned long long int[ap.number_of_classes_possible];
	unsigned long long int value;
	Sequence group;

	// initialize results
	for ( unsigned int i = 0; i < ap.number_of_classes_possible; ++i )
		tmp_results[i] = 0;

	// run analysis of the digits
	for (unsigned int i = 0; i < number_of_digits && ap.digits_tested < ap.number_of_digits_to_test && ap.sequences_tested < ap.number_of_sequences_to_test; ++i)		// only test partial set of entire number
	{
		// Get the next sequence
		group = Next_Sequence( rn, ap.max_sequence_size );

		// check if out of numbers
		for ( int j = 0; j < group.size; ++j )
		{
			if ( group.seq[j] == -1 )
			{
				cout << "Out of digits to test, finishing calculations." << endl;
				return tmp_results;
			}
		}

		// Get the sequence value
		value = Sequence_Value( group );

		if ( 0 <= value && value <= ap.number_of_classes_possible )
			++tmp_results[value];
		else
		{
			cout << "ERROR: Sequence Value is out of range.  0 <= Value Returned < Total Number of Classes.\nCheck that Sequence_Value is correct or you have the correct maximum number of classes." << endl;
			cout << "Recieved value " << value << " for sequence <= " << ap.number_of_classes_possible << endl;
			for ( int i = 0; i < group.size; ++i )
				cout << group.seq[i] << " ";
			cout << endl;
			exit( 1 );
			return tmp_results;
		}

		if ( show_progress )
		{
			if ( i % 2000000 == 0 )
				cout << ".";

			if ( i % 50000000 == 0 )
				cout << i / 1000000 << " million digits tested." << endl;
			
			
		}

		ap.sequences_tested++;			// count number of sequences tested
		ap.digits_tested += group.size;	// count number of digits tested
	}

	return tmp_results;

}


// analyze a specific number
unsigned long long int *Analyze_Number( Sequence( *Next_Sequence )(Read_Number &rn, int digits), unsigned int( *Sequence_Value )( Sequence s ), Analysis_Parameters &ap )
{
	ap.sequences_tested = 0;
	ap.digits_tested = 0;

	
	// init for sequence functions
	Initialize_Next_Sequence_Functions();

	unsigned long long int *results;// = new unsigned long long int[ap.number_of_classes_possible];
	//unsigned int value;
	Sequence group;
	Read_Number rn;

	// setup read number input
	if ( ap.file_constant )
		rn.Set_File( ap.filename );		// set file to read from

	// remove digits in front of decimal if needed
	if ( ap.remove_predecimal )
		rn.Remove_Decimal();

	results = Get_Next_Set_Of_Sequences( Next_Sequence, Sequence_Value, ap, rn, ap.number_of_sequences_to_test, true );


	ofstream local_out;
	if (ap.output_file != "")
	{
		local_out.open(ap.output_file, ios::app);
	}
	
	Constant_Analysis ca(ap);
	cout << "Analysis Results: " << endl;
	cout << "Full" << endl;	ca.Display_Full_Result(results, cout, true);  cout << endl;
	//cout << "Summary" << endl;  ca.Display_Summary_Result(results, cout); cout << endl;
	cout << "Continuous" << endl;  ca.Continuous_Analysis_Initial(results, cout); cout << endl;
	ca.Continuous_Analysis_Interval(results, cout);
	ca.Continuous_Analysis_Summary( results, cout );
	
	local_out << "Analysis Results: " << endl;
	local_out << "Full" << endl;	ca.Display_Full_Result(results, local_out, true);  local_out << endl;
	//local_out << "Summary" << endl;  ca.Display_Summary_Result(results, local_out); local_out << endl;
	local_out << "Continuous" << endl;  ca.Continuous_Analysis_Initial(results, local_out); local_out << endl;
	ca.Continuous_Analysis_Interval(results, local_out);
	ca.Continuous_Analysis_Summary(results, local_out);
	ca.Continuous_Analysis_Summary(results, local_out);
	
	local_out.close();

	return results;
}



unsigned long long int * Analyze_Number_Continuously(	Sequence( *Next_Sequence )(Read_Number &rn, int digits), unsigned int( *Sequence_Value )(Sequence s), 
														Analysis_Parameters &ap, unsigned int granularity )
{
	// log files
	// screen - Progress + Final results
	// summary - digits X^2 Max/Min
	// full - Digits X^2 Digit Count Digit differential Max/Min
	// final - Final Results  (uses full calculations)
	ofstream summary_output, full_output, final_result, local_file;
	ap.sequences_tested = 0;
	ap.digits_tested = 0;
	cout << "Starting Analyze Number *************************" << endl;
	if (ap.output_file != "")
	{
		cout << "Full analysis redirect to local file: " << ap.output_file << endl;
		full_output.open(ap.output_file, ios::out);
	}
	else
	{
		cout << "Full analysis in log file: " << FULL_ANALYSIS << endl;
		full_output.open(FULL_ANALYSIS, ios::out);
	}
	
	summary_output.open(SUMMARY, ios::out);
	final_result.open(FINAL_ANALYSIS, ios::out);
	bool logs = true;

	if (!full_output || !summary_output || !final_result)
	{
		cout << "Error creating log files." << endl;
		logs = false;
		//exit(1);
	}

	Analyze_List al;
	unsigned long long int* results = new unsigned long long int[ap.number_of_classes_possible];
	unsigned long long int* tmp_results;

	Constant_Analysis ca_summary(ap);
	Constant_Analysis ca_full(ap);


//	unsigned int value;
	Sequence group;
	Read_Number rn;

	// init for sequence functions
	Initialize_Next_Sequence_Functions();

	// initialize results
	for ( unsigned int i = 0; i < ap.number_of_classes_possible; ++i )
		results[i] = 0;

	// setup read number input
	if ( ap.file_constant )
		rn.Set_File( ap.filename );		// set file to read from

	// remove digits in front of decimal if needed
	if ( ap.remove_predecimal )
		rn.Remove_Decimal();

	// Initialize any Analysis

	//***ca.Continuous_Analysis_Initial( results, out );
	//ca.Continuous_Analysis_Initial(results, full_output);
	
	// for full and summary output options
	bool digit_count = false;
	bool digit_diff = false;

	#ifdef DIGIT_COUNT
		digit_count = true;
	#endif

	#ifdef DIGIT_DIFFERENTIAL
		digit_diff = true;
	#endif

	ca_full.Output_Setup(true, digit_count, digit_diff, true, true);
	ca_summary.Output_Setup(true, false, false, true, true);

	if (logs)
	{
		ca_full.Continuous_Analysis_Initial(results, full_output);
		ca_full.Continuous_Analysis_Initial(results, final_result);
		ca_summary.Continuous_Analysis_Initial(results, summary_output);
	}


	int pct = 0;
	float tmp;

	
	while ( ap.digits_tested < ap.number_of_digits_to_test && ap.sequences_tested < ap.number_of_sequences_to_test )
	{
		// Calculate results for the next granularity set
		tmp_results = Get_Next_Set_Of_Sequences( Next_Sequence, Sequence_Value, ap, rn, granularity, false );

		// copy results
		for ( unsigned int i = 0; i < ap.number_of_classes_possible; ++i )
			results[i] += tmp_results[i];

		delete[] tmp_results;

		// Interval Analysis
		if (logs)
		{
			//***ca.Continuous_Analysis_Interval( results, out );
			ca_full.Continuous_Analysis_Interval(results, full_output);
			ca_summary.Continuous_Analysis_Interval(results, summary_output);
		}

		// calculate progress (percentage only)
		tmp = (float) ap.sequences_tested / (float) ap.number_of_sequences_to_test * (float) 100;

		if (pct + 1 < tmp )
		{
			++pct;
			cout << ".";
			if (pct % 10 == 0)
				cout << pct << "%" << endl;
		}
		
	}



	// Final Analysis
	cout << ".100% complete" << endl << endl;
	cout << "Analyze Number continuous Summarry" << endl;
	//****ca.Continuous_Analysis_Summary( results, out );
	
	
	if (logs)
	{
		ca_full.Continuous_Analysis_Summary(results, full_output);
		ca_full.Continuous_Analysis_Interval(results, final_result);		// last result only for final record
		ca_full.Continuous_Analysis_Summary(results, final_result);			// use full analysis for summary data
		ca_summary.Continuous_Analysis_Summary(results, summary_output);
	}
	
	// for testing
	ca_full.Continuous_Analysis_Summary(results, cout);
	

	if (logs)
	{
		summary_output.close();
		full_output.close();
		final_result.close();
	}

	local_file.close();

	return results;
}

