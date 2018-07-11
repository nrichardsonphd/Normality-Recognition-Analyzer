/// @file
#include "Analyze Number.h"

unsigned long long int *Get_Next_Set_Of_Sequences( Sequence( *Next_Sequence )(Read_Number &rn, int digits), unsigned int( *Sequence_Value )(Sequence s), 
													Analysis_Parameters &ap, Read_Number &rn, unsigned int number_of_sequences )
{
	unsigned long long int *tmp_results = new unsigned long long int[ap.total_number_of_classes];
	unsigned int value;
	Sequence group;

	// initialize results
	for ( unsigned int i = 0; i < ap.total_number_of_classes; ++i )
		tmp_results[i] = 0;

	int progress = ap.number_of_sequences_to_test * ap.max_sequence_size / 1000;
	int percent = progress * 100;
	int pct = 0;

	// run analysis of the digits
	for ( unsigned int i = 0; i < number_of_sequences; ++i )		// only test partial set of entire number
	{
		
		if ( ap.number_of_sequences_to_test * ap.max_sequence_size > 1000000 )
		{
			if ( ap.digits_tested % progress == 0 )
			{
				if ( ap.digits_tested % percent == 0 )
				{
					cout << pct << "% complete" << endl;
					pct += 10;
				}
				else
					cout << ".";
			}
		}

		// Get the next sequence
		group = Next_Sequence( rn, ap.max_sequence_size );

		// Get the sequence value
		value = Sequence_Value( group );

		if ( 0 <= value && value <= ap.total_number_of_classes )
			++tmp_results[value];
		else
		{
			cout << "ERROR: Sequence Value is out of range.  0 <= Value Returned <= Total Number of Classes.\nCheck that Sequence_Value is correct." << endl;
			exit( 1 );
			return tmp_results;
		}

		ap.sequences_tested++;		// count number of sequences tested
		ap.digits_tested += group.size;	// count number of digits tested
	}

	if ( ap.number_of_sequences_to_test > 1000000 )
		cout << "100% complete" << endl;

	return tmp_results;

}


// analyze a specific number
unsigned long long int *Analyze_Number( Sequence( *Next_Sequence )(Read_Number &rn, int digits), unsigned int( *Sequence_Value )( Sequence s ), Analysis_Parameters &ap )
{
	ap.sequences_tested = 0;
	ap.digits_tested = 0;

	unsigned long long int *results;// = new unsigned long long int[ap.total_number_of_classes];
	//unsigned int value;
	Sequence group;
	Read_Number rn;

	// setup read number input
	if ( ap.file_constant )
		rn.Set_File( ap.filename );		// set file to read from

	// remove digits in front of decimal if needed
	if ( ap.remove_predecimal )
		rn.Remove_Decimal();

	results = Get_Next_Set_Of_Sequences( Next_Sequence, Sequence_Value, ap, rn, ap.number_of_sequences_to_test );

	return results;
}



void Analyze_Number_Continuously(	Sequence( *Next_Sequence )(Read_Number &rn, int digits), unsigned int( *Sequence_Value )(Sequence s), 
									Analysis_Parameters &ap, unsigned int granularity, unsigned int progress, ostream &out )
{
	ap.sequences_tested = 0;
	ap.digits_tested = 0;

	Analyze_List al;
	unsigned long long int* results = new unsigned long long int[ap.total_number_of_classes];
	unsigned long long int* tmp_results;
	double max = 0, min = 1000, chisq;
	bool display = false;
	
//	unsigned int value;
	Sequence group;
	Read_Number rn;

	out << "Digits\t";
	for ( unsigned int i = 0; i < ap.total_number_of_classes; ++i )
		out << i << "\t";
	out << endl;

	// initialize results
	for ( unsigned int i = 0; i < ap.total_number_of_classes; ++i )
		results[i] = 0;

	// setup read number input
	if ( ap.file_constant )
		rn.Set_File( ap.filename );		// set file to read from

	// remove digits in front of decimal if needed
	if ( ap.remove_predecimal )			
		rn.Remove_Decimal();


	while ( ap.sequences_tested < ap.number_of_sequences_to_test )
	{
		tmp_results = Get_Next_Set_Of_Sequences( Next_Sequence, Sequence_Value, ap, rn, granularity );

		for ( unsigned int i = 0; i < ap.total_number_of_classes; ++i )
			results[i] += tmp_results[i];

		delete [] tmp_results;

		al.Set_List( results, ap.total_number_of_classes );
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
			for ( unsigned int j = 0; j < ap.total_number_of_classes; ++j )
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

	}

	out << "Maximum Chi-Squared: " << max << endl;
	out << "Minimum Chi-Squared: " << min << endl;
	out << endl;

	delete[] results;
}

