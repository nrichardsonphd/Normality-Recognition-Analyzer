/// @file
#include "Analyze Number.h"

unsigned long long int *Get_Next_Set_Of_Sequences( Sequence( *Next_Sequence )(Read_Number &rn, int digits), unsigned int( *Sequence_Value )(Sequence s), 
													Analysis_Parameters &ap, Read_Number &rn, unsigned long long int number_of_digits, bool show_progress )
{
	unsigned long long int *tmp_results = new unsigned long long int[ap.number_of_classes_possible];
	unsigned int value;
	Sequence group;

	// initialize results
	for ( unsigned int i = 0; i < ap.number_of_classes_possible; ++i )
		tmp_results[i] = 0;

	// run analysis of the digits
	for ( unsigned int i = 0; i < number_of_digits; ++i )		// only test partial set of entire number
	{
		// Get the next sequence
		group = Next_Sequence( rn, ap.max_sequence_size );

		// check if out of numbers
		for ( int i = 0; i < group.size; ++i )
		{
			if ( group.seq[i] == -1 )
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
			cout << "Recieved value " << value << " for sequence ";
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

	Constant_Analysis ca(ap);

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
	ca.Continuous_Analysis_Initial( results, out );

	int pct = 0;
	float tmp;
	int step;

	if ( ap.number_of_digits_to_test >= 1000000000 )
		step = 1;
	else
		step = 2;

	while ( ap.digits_tested < ap.number_of_digits_to_test )
	{
		// Calculate results for the next granularity set
		tmp_results = Get_Next_Set_Of_Sequences( Next_Sequence, Sequence_Value, ap, rn, granularity, false );

		// copy results
		for ( unsigned int i = 0; i < ap.number_of_classes_possible; ++i )
			results[i] += tmp_results[i];

		delete [] tmp_results;
		
		// Interval Analysis
		ca.Continuous_Analysis_Interval( results, out ); 
		//cout << "\t\t**";

		// calculate progress
		tmp = (float) ap.sequences_tested / (float) ap.number_of_digits_to_test * (float) 100;
		
		if ( pct + step < ap.max_sequence_size * tmp )
		{

			if ( tmp > 100 )
				tmp = 100;	
			
			pct += step;
			cout << (int)(ap.max_sequence_size * tmp) << "% complete." << endl;
		}
		
		out << endl;
		//if ( ap.digits_tested > 900 )
			//exit( 1 );
	}

	// Final Analysis
	ca.Continuous_Analysis_Summary( results, out );
	
	return results;
}

