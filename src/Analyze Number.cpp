/// @file
#include "Analyze Number.h"

// analyze a specific number
unsigned long long int *Analyze_Number( Sequence( *Next_Sequence )(Read_Number &rn, int digits), unsigned int( *Sequence_Value )( Sequence s ), Analysis_Parameters &ap )
{
	unsigned long long int *results = new unsigned long long int[ap.total_number_of_classes];
	unsigned int value;
	Sequence group;
	Read_Number rn;

	// initialize results
	for ( int i = 0; i < ap.total_number_of_classes; ++i )
		results[i] = 0;
	
	// setup read number input
	if ( ap.file_constant )
		rn.Set_File( ap.filename );		// set file to read from

	// remove digits in front of decimal if needed
	if ( ap.remove_predecimal )
		rn.Remove_Decimal();

	// run analysis of the digits
	for ( int i = 0; i < ap.number_of_sequences_to_test; ++i )
	{
		// Get the next sequence
		group = Next_Sequence( rn, ap.block_size );

		// Get the sequence value
		value = Sequence_Value( group );

		if ( 0 <= value && value <= ap.total_number_of_classes )
			++results[value];
		else
		{
			cout << "Error: Sequence Value is out of range" << endl;
			//exit( 1 );
			return results;
		}

		ap.blocks_tested_actual++;		// count number of sequences tested
		ap.digits_tested += group.size;	// count number of digits tested
	}


	return results;
}
