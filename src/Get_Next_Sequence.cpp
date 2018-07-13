#include "Get_Next_Sequence.h"

bool first = true;


void Initialize_Next_Sequence_Functions()
{
	first = true;
}




//Sequence Get_Block_Sequence_Digits( Read_Number &rn, int digits )
//{
	//return Get_Block_Sequence( rn, digits );
//}

// Grabs N digits in a row.  Next set will start after last digit, nonoverlapping
Sequence Get_Block_Sequence( Read_Number &rn, int digits )
{
	Sequence s;
	s.size = digits;
	
	for ( int i = 0; i < digits; ++i )
		s.seq[i] = rn.Get_Next_Digit();
	
	return s;
}

// Grab N digits in a row.  Next set starts at 2nd digit.  Overlapping
Sequence Get_Stream_Sequence( Read_Number &rn, int digits )
{
	// stream should remember the last digits - 1 used
	static Sequence s;

	if ( first )
	{	
		// First time setup initial sequence
		first = false;
		s.size = digits;
		
		for ( int i = 0; i < s.size; ++i )
			s.seq[i] = rn.Get_Next_Digit();
	}
	else
	{
		for ( int i = 0; i < s.size - 1; ++i )
			s.seq[i] = s.seq[i + 1];

		s.seq[s.size - 1] = rn.Get_Next_Digit();
	}
	
	
	return s;
}



Sequence Get_Bin_Block_Sequence( Read_Number &rn, int digits )
{
	Sequence s;
	s.size = digits;

	for ( int i = 0; i < digits; ++i )
		s.seq[i] = rn.Get_Next_Binary_Digit();

	return s;

}

Sequence Get_Bin_Stream_Sequence( Read_Number &rn, int digits )
{
	// stream should remember the last digits - 1 used
	static Sequence s;

	if ( first )
	{
		// First time setup initial sequence
		first = false;
		s.size = digits;

		for ( int i = 0; i < s.size; ++i )
			s.seq[i] = rn.Get_Next_Binary_Digit();
	}
	else
	{
		for ( int i = 0; i < s.size - 1; ++i )
			s.seq[i] = s.seq[i + 1];

		s.seq[s.size - 1] = rn.Get_Next_Binary_Digit();
	}

	return s;

}



///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
// Testing
bool Test_Next_Sequence( bool detailed )
{
	bool pass = true;

	if ( !Test_Decimal_Sequence(detailed) )
		pass = false;

	return pass;
}


bool Test_Decimal_Sequence( bool detailed )
{
	bool test = true;
	Sequence s;
	Read_Number rn;
	int tmp = 0;
	
	const int seq1[14] = { 0,0,1,1,2,2,3,3,10,10,11,11,12,12 };
	const int seq2[7] = { 0,11,22,33,110,121,132 };
	const int seq3[4] = { 1,122,340,1121 };
	const int seq4[3] = { 11,2233,11121 };

	rn.Set_File( "../../data/testfiles/sequence.txt" );
	
	for ( int k = 0; k < 14; ++k )
	{
		s = Get_Block_Sequence( rn, 1 );
		tmp = 0;

		for ( int i = 0; i < s.size; ++i )
		{
			tmp += (int) pow( 10, s.size - i - 1 ) * s.seq[i];
		}

		if ( tmp != seq1[k] )
			test = false;
	}

	if ( detailed )
	{
		if ( test )
			cout << "\t[TRUE]: Group Size 1" << endl;
		else
			cout << "\t[FALSE]: Group Size 1" << endl;
	}

	rn.Set_File( "../../data/testfiles/sequence.txt" );
	for ( int k = 0; k < 7; ++k )
	{
		s = Get_Block_Sequence( rn, 2 );
		tmp = 0;

		for ( int i = 0; i < s.size; ++i )
		{
			tmp += (int) pow( 10, s.size - i - 1 ) * s.seq[i];
		}

		if ( tmp != seq2[k] )
				test = false;
	}

	if ( detailed )
	{
		if ( test )
			cout << "\t[TRUE]: Group Size 2" << endl;
		else
			cout << "\t[FALSE]: Group Size 2" << endl;
	}

	rn.Set_File( "../../data/testfiles/sequence.txt" );
	for ( int k = 0; k < 4; ++k )
	{
		s = Get_Block_Sequence( rn, 3 );
		tmp = 0;

		for ( int i = 0; i < s.size; ++i )
		{
			tmp += (int) pow( 10, s.size - i - 1 ) * s.seq[i];
		}

		if ( tmp != seq3[k] )
			test = false;
	}

	if ( detailed )
	{
		if ( test )
			cout << "\t[TRUE]: Group Size 3" << endl;
		else
			cout << "\t[FALSE]: Group Size 3" << endl;
	}


	rn.Set_File( "../../data/testfiles/sequence.txt" );
	for ( int k = 0; k < 3; ++k )
	{
		s = Get_Block_Sequence( rn, 4 );
		tmp = 0;

		for ( int i = 0; i < s.size; ++i )
		{
			tmp += (int) pow( 10, s.size - i - 1 ) * s.seq[i];
		}

		if ( tmp != seq4[k] )
			test = false;
	}
	
	if ( detailed )
	{
		if ( test )
			cout << "\t[TRUE]: Group Size 4" << endl;
		else
			cout << "\t[FALSE]: Group Size 4" << endl;
	}


	return test;
}

bool Test_Binary_Sequence( bool detailed )
{
	return true;
}


void Sequence_Test()
{
	Sequence q;
	Read_Number rn;
/*	rn.Set_File( "../../data/Pi1K-dec.txt" );

	for ( int j = 0; j < 5; ++j )
	{
		q = Get_Block_Sequence( rn, 5 );
		cout << "Q " << j << " => ";
		Display_Sequence( q );


	}
	cout << endl;

	rn.Set_File( "../../data/Pi1K-dec.txt" );
	Initialize_Next_Sequence_Functions();

	for ( int j = 0; j < 5; ++j )
	{
		q = Get_Stream_Sequence( rn, 5 );
		cout << "Q " << j << " => ";
		Display_Sequence( q );
	}
	cout << endl;
	*/
	rn.Set_File( "../../data/Pi1K-hex.txt" );
	Initialize_Next_Sequence_Functions();

	for ( int j = 0; j < 5; ++j )
	{
		q = Get_Bin_Block_Sequence( rn, 5 );
		cout << "Q " << j << " => ";
		Display_Sequence( q );
	}
	cout << endl;

	rn.Set_File( "../../data/Pi1K-hex.txt" );
	Initialize_Next_Sequence_Functions();

	for ( int j = 0; j < 5; ++j )
	{
		q = Get_Bin_Stream_Sequence( rn, 5 );
		cout << "Q " << j << " => ";
		Display_Sequence( q );
	}
	cout << endl;
}

