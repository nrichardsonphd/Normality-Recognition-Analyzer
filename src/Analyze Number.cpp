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
	for ( unsigned int i = 0; i < number_of_digits && ap.digits_tested < ap.number_of_digits_to_test; ++i )		// only test partial set of entire number
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
			cout << "ERROR: Sequence Value is out of range.  0 <= Value Returned < Total Number of Classes.\nCheck that Sequence_Value is correct." << endl;
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

	results = Get_Next_Set_Of_Sequences( Next_Sequence, Sequence_Value, ap, rn, ap.number_of_digits_to_test, true );

	
	Constant_Analysis ca(ap);
	ca.Continuous_Analysis_Summary( results, cout );

	return results;
}



unsigned long long int * Analyze_Number_Continuously(	Sequence( *Next_Sequence )(Read_Number &rn, int digits), unsigned int( *Sequence_Value )(Sequence s), 
														Analysis_Parameters &ap, unsigned int granularity, ostream &out )
{
	ap.sequences_tested = 0;
	ap.digits_tested = 0;

	Analyze_List al;
	unsigned long long int* results = new unsigned long long int[ap.number_of_classes_possible];
	unsigned long long int* tmp_results;

	Constant_Analysis ca_full(ap);
	Constant_Analysis ca_partial( ap );
	ofstream partial_out( "../../logs/partial.txt", ios::out );

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
	ca_full.Continuous_Analysis_Initial( results, out );
	ca_partial.Continuous_Analysis_Initial( results, partial_out );

	int pct = 0;
	float tmp;

	
	while ( ap.digits_tested < ap.number_of_digits_to_test )
	{
		// Calculate results for the next granularity set
		tmp_results = Get_Next_Set_Of_Sequences( Next_Sequence, Sequence_Value, ap, rn, granularity, false );

		// copy results
		for ( unsigned int i = 0; i < ap.number_of_classes_possible; ++i )
			results[i] += tmp_results[i];

		delete[] tmp_results;

		// Interval Analysis
		ca_full.Continuous_Analysis_Interval( results, out, true );
		ca_partial.Continuous_Analysis_Interval( results, partial_out, false );

		// calculate progress
		tmp = (float) ap.sequences_tested / (float) ap.number_of_digits_to_test * (float) 100;

		if ( pct + 1 < ap.max_sequence_size * tmp )
		{

			if ( tmp > 100 )
				tmp = 100;

			pct += 1;
			if ( pct % 10 == 0 )
				cout << (int) (ap.max_sequence_size * tmp) << "% complete." << endl;
			else
				cout << "...";
		}

		//cout << endl;
	}

	// Final Analysis
	cout << "Analyze Number continuous Summarry" << endl;
	ca_full.Continuous_Analysis_Summary( results, out );
	ca_partial.Continuous_Analysis_Summary( results, partial_out );

	// force summary output to screen
	if ( &cout != &out )
		ca_full.Continuous_Analysis_Summary( results, cout );

	partial_out.close();
	
	return results;
}

