#ifndef GET_NEXT_DIGIT_H
#define GET_NEXT_DIGIT_H
#include <string>
#include <iostream>
using namespace std;

#include "common/Read_Number.h"
#include "Sequence.h"

/*
struct Sequence
{
	int size;
	int seq[10] = { 0 };
};

*/


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// All functions here are to be used to be called for the next class
// @param rn		number reading from
// @param digits	number of digits to take 
//		@note		this is a maximum, the function should deal with variable size classes
//		@note		Must use address for read number, not a copy of it
// These functions should 
	// 1. Read next sequence from the number
	// 2. Calculate a value 0, 1, 2, ..., MAX_CLASS_VALUE
Sequence Get_Block_Sequence( Read_Number &rn, int digits );
Sequence Get_Stream_Sequence( Read_Number &rn, int digits );


/// The Bin functions are used with hexadecimal files to read a binary sequence of digits
Sequence Get_Bin_Block_Sequence( Read_Number &rn, int digits );
Sequence Get_Bin_Stream_Sequence( Read_Number &rn, int digits );










// Testing functions
bool Test_Next_Sequence( bool detailed );

bool Test_Decimal_Sequence( bool detailed );
bool Test_Binary_Sequence( bool detailed );
#endif