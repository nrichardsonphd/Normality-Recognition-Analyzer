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

		// Get the sequence value
		value = Sequence_Value( group );

		if ( 0 <= value && value <= ap.number_of_classes_possible )
			++tmp_results[value];
		else
		{
			cout << "ERROR: Sequence Value is out of range.  0 <= Value Returned < Total Number of Classes.\nCheck that Sequence_Value is correct." << endl;
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
														Analysis_Parameters &ap, unsigned int granularity, unsigned int progress, ostream &out )
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

	// initialize results
	for ( unsigned int i = 0; i < ap.number_of_classes_possible; ++i )
		results[i] = 0;

	// setup read number input
	if ( ap.file_constant )
		rn.Set_File( ap.filename );		// set file to read from

	// remove digits in front of decimal if needed
	if ( ap.remove_predecimal )			
		rn.Remove_Decimal();

	ca.Continuous_Analysis_Initial( results, out );

	int pctprogress = 0;// ap.number_of_sequences_to_test * ap.max_sequence_size / PROGRESS_MARKERS;
	int percent = pctprogress * 100;
	int pct = 0;

	while ( ap.digits_tested < ap.number_of_digits_to_test )
	{
		tmp_results = Get_Next_Set_Of_Sequences( Next_Sequence, Sequence_Value, ap, rn, granularity, false );

		for ( unsigned int i = 0; i < ap.number_of_classes_possible; ++i )
			results[i] += tmp_results[i];

		delete [] tmp_results;
		cout << "**********dsflkjhdfsakljafdsjlhklkjfadlkjhdfsajkhlfsdajhklsdfajhhjkdfsajhkfsdahjklfsdajhkl*******************";
		/*/if ( ap.number_of_sequences_to_test * ap.max_sequence_size >= MIN_PROGRESS_DISPLAY )
		{
			cout << "PROGRESS" << endl;
			exit( 1 );
			if ( ap.digits_tested % pctprogress == 0 )
			{
				if ( ap.digits_tested % percent == 0 )
				{
					cout << pct << "% complete" << endl;
					pct += 10;
				}
				else
					cout << ".";
			}
		}*/

		if ( ap.sequences_tested % progress == 0 )
			ca.Continuous_Analysis_Interval( results, out );


		/*

		double max = 0, min = 1000, chisq;
		bool display = false;

		al.Set_List( results, ap.number_of_classes_possible );
		chisq = al.Chi_Squared();

		if ( max < chisq )
		{
			max = chisq;
			display = true;
		}
		if ( min > chisq )
		{
			min = chisq;
			display = true;
		}

		if ( display || ap.sequences_tested % progress == 0 )
		{
			out << ap.digits_tested << "\t";
			for ( unsigned int j = 0; j < ap.number_of_classes_possible; ++j )
				out << results[j] << "\t";

			out << "\t\t";
			if ( abs( max - chisq ) < .00001 )
				out << "/\\";
			if ( abs( min - chisq ) < .00001 )
				out << "\\/";

			out << chisq;
			out << endl;

			display = false;
		}
		*/

	}

	ca.Continuous_Analysis_Summary( results, out );
	//out << "Maximum Chi-Squared: " << max << endl;
	//out << "Minimum Chi-Squared: " << min << endl;
	//out << endl;
	cout << "100% Complete Analysis." << endl;
	return results;
}

