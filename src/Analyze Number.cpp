/// @file
#include "Analyze Number.h"

// analyze a specific number
void Analyze_Number( Sequence( *Next_Sequence )(Read_Number &rn, int digits), unsigned int( *Sequence_Value )( Sequence s ), Analysis_Parameters ap )
{
	int *results = new int[ap.number_of_classes];
	unsigned int value;
	Sequence group;
	Read_Number rn;

	// initialize results
	for ( int i = 0; i < ap.number_of_classes; ++i )
		results[i] = 0;
	
	// setup read number input
	if (ap.file_constant )
		rn.Set_File( ap.filename );		// set file to read from
	else if ( ap.generated_constant )
	{
		;	// TBD setup a generated constant
		cout << "Generated constants not implemented yet" << endl;
		exit( 1 );
	}
	else
	{
		cout << "Error with Analysis Parameters: Choose File or Generated Constant." << endl;
		exit( 1 );
	}

	// remove digits in front of decimal if needed
	if ( ap.remove_predecimal )
		rn.Remove_Decimal();

	// run analysis of the digits
	for ( int i = 0; i < ap.number_of_groups; ++i )
	{
		// Get the next sequence
		group = Next_Sequence( rn, ap.block_size );

		// Get the sequence value
		value = Sequence_Value( group );
		++results[value];
	}


	// Analyze the results
	cout << "Results go here" << endl;
	for ( int i = 0; i < ap.number_of_classes; ++i )
		cout << i << ": " << results[i] << "\t";
	cout << endl;

	delete[] results;
}
