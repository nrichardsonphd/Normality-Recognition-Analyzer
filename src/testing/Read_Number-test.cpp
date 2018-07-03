#include "Read_Number-test.h"
//////////////////////////////////////////////////////////////////
//// Testing fucntions below
//////////////////////////////////////////////////////////////////




bool Test_Read_Number( bool detailed )
{
	bool pass = true;	// Assume all tests are passed, set to false when failed
	string decimal_file = "../../data/testfiles/Pi1K-dec.txt";
	string hex2bin_file = "../../data/testfiles/hex2bin.txt";
	string digit_file = "../../data/testfiles/digit.txt";
	string no_file = "junk.does.not.exist.txt";

	if ( !RN_Test_Nofile( no_file, detailed ) )
		pass = false;

	if ( !RN_Test_Digit_Test( digit_file, detailed ) )
		pass = false;

	if ( !RN_Test_Decimal_Pre( decimal_file, detailed ) )
		pass = false;

	if ( !RN_Test_Decimal_Remove( decimal_file, detailed ) )
		pass = false;
	
	if ( !RN_Test_Binary( hex2bin_file, detailed ) )
		pass = false;

	return pass;
}


// File Not Found
bool RN_Test_Nofile( string file, bool detailed )
{
	string test_name = "Missing File";
	Read_Number rn;

	bool test = rn.Set_File( file );

	if ( detailed )
	{
		if ( !test )
			cout << "\t[TRUE]: " << test_name << endl;
		else
			cout << "\t[FALSE]: " << test_name << endl;
	}

	return !test;
}

// Wrong file format
bool RN_Test_Digit_Test( string file, bool detailed )
{
	string test_name = "Digit Test";
	Read_Number rn;
	int i = 0;

	bool test = rn.Set_File( file );

	while ( rn.Get_Digits_Read() < 22 )
	{
		if ( i == 16 )	// for 2nd set of lowercase hex digits
			i = i - 6;

		if ( rn.Get_Next_Digit() == i )
			++i;
		else
			test = false;
	}

	if ( detailed )
	{
		if ( test )
			cout << "\t[TRUE]: " <<  test_name << endl;
		else
			cout << "\t[FALSE]: " << test_name << endl;
	}

	return test;
}

// check decimal digits 
// keep pre decimal
// next digit x 1000
bool RN_Test_Decimal_Pre( string file, bool detailed )
{
	string test_name = "Decimal Digits Keep Pre Decimal";
	Read_Number rn;
	// digit counts from thestarman.pcministry.com/math/pi/RandPI.html
	// ** Added +1 for the 3 before decimal and go 1 digit extra
	const int pi_1001[10] = { 93, 116, 103, 103, 93, 97, 94,95, 101, 106 };
	int digits[10] = { 0 };

	bool test = rn.Set_File( file );

	// bucket count 1000 digits
	for ( int i = 0; i < 1001; ++i )
	{
		digits[rn.Get_Next_Digit()]++;
	}

	// check digits against known results
	for ( int k = 0; k < 10; ++k )
		if ( pi_1001[k] != digits[k] )
			test = false;

	if ( detailed )
	{
		if ( test )
			cout << "\t[TRUE]: " << test_name << endl;
		else
			cout << "\t[FALSE]: " << test_name << endl;
	}

	return test;
}

// check decimal digits
// remove pre decimal
// next digit x 1000
bool RN_Test_Decimal_Remove( string file, bool detailed )
{
	string test_name = "Decimal Digits Remove Pre Decimal";
	Read_Number rn;
	// digit counts from thestarman.pcministry.com/math/pi/RandPI.html
	const int pi_1000[10] = { 93, 116, 103, 102, 93, 97, 94,95, 101, 106 };
	bool test = rn.Set_File( file );
	int digits[10] = { 0 };

	test = rn.Set_File( file );
	rn.Remove_Decimal();			// remove all digits until decimal

									// bucket count 1000 digits
	for ( int i = 0; i < 1000; ++i )
	{
		digits[rn.Get_Next_Digit()]++;
	}

	for ( int k = 0; k < 10; ++k )
		if ( pi_1000[k] != digits[k] )
			test = false;

	if ( detailed )
	{
		if ( test )
			cout << "\t[TRUE]: " << test_name << endl;
		else
			cout << "\t[FALSE]: " << test_name << endl;
	}

	return test;
}

// check binary digits
bool RN_Test_Binary( string file, bool detailed )
{
	string test_name = "Binary Digits";
	Read_Number rn;
	const int bin[24] = { 0,0,0,0, 0,0,0,1, 0,0,1,0, 1,0,1,0, 1,0,1,1, 1,1,0,0 };		// 012ABc
	
	// pre decimal
	// next digit
	
	bool test = rn.Set_File( file );
	
	// check each bit and transfer between digits
	for ( int i = 0; i < 24; ++i )
	{
		
		if ( rn.Get_Next_Binary_Digit() != bin[i] )
			test = false;
		
	}

	if ( detailed )
	{
		if ( test )
			cout << "\t[TRUE]: " << test_name << endl;
		else
			cout << "\t[FALSE]: " << test_name << endl;
	}

	return test;
}


