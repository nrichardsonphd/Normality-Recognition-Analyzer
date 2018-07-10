#include "Get_Sequence_Value.h"

int Get_Sequence_Digits_Base_2( Sequence s )
{
	return Get_Sequence_Digits( s, 2 );
}

unsigned int Get_Sequence_Digits_Base_10( Sequence s )
{
	return Get_Sequence_Digits( s, 10 );
}


int Get_Sequence_Digits_Base_16( Sequence s )
{
	return Get_Sequence_Digits( s, (int)pow(16,s.size ));
}

int Get_Sequence_Digits( Sequence s, int base )
{
	// read each digit in s and build a number.
	// a digits in s should be in the base
	int tmp = 0;

	for ( int i = 0; i < s.size; ++i )
	{
		tmp += (int) pow( base, s.size - i - 1 ) * s.seq[i];
	}

	return tmp;
}







// Testing
bool Test_Sequence_Value( bool detailed )
{
	bool pass = true;
	
	if ( !Test_Digits( detailed ) )
		pass = false;

	return pass;
}

bool Test_Digits( bool detailed )
{
	bool pass = true;
	int tmp;
	Sequence s;
	s.size = 3;

	s.seq[0] = 1;
	s.seq[1] = 0;
	s.seq[2] = 0;
	tmp = Get_Sequence_Digits( s, BINARY );
	if ( tmp != 4 ) pass = false;
	if ( detailed )
		cout << "\tBinary value 3: 4 == " << tmp << endl;

	s.seq[0] = 1;
	s.seq[1] = 2;
	s.seq[2] = 3;
	tmp = Get_Sequence_Digits( s, DECIMAL );
	if ( tmp != 123 ) pass = false;
	if ( detailed )
		cout << "\tDecimal value 3: 123 == " << tmp << endl;

	s.seq[0] = 1;
	s.seq[1] = 2;
	s.seq[2] = 10;
	tmp = Get_Sequence_Digits( s, HEXADECIMAL );
	if ( tmp != 298 ) pass = false;
	if ( detailed )
		cout << "\tHexaDecimal value 3: 298 == " << tmp << endl;

	return pass;
}