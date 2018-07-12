#ifndef GET_NEXT_DIGIT_H
#define GET_NEXT_DIGIT_H
#include <string>
#include <iostream>
using namespace std;

#include "common/Read_Number.h"
#include "Sequence.h"

// used for global/static variables in function. 
extern bool first;

// used to reset any global/static variables between testing different numbers
void Initialize_Next_Sequence_Functions();				

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// All functions here are to be used to be called for the next class
// @param rn		number reading from
//		@note		this is a maximum, the function should deal with variable size classes
//		@note		Must use address for read number, not a copy of it
// These functions should 
	// 1. Read next sequence from the number
	
// These will be used for function pointers
//Sequence Get_Block_Sequence_Digits( Read_Number &rn, int digits );

// These should be used as support functions
Sequence Get_Block_Sequence( Read_Number &rn, int digits );
Sequence Get_Stream_Sequence( Read_Number &rn, int digits );


/// The Bin functions are used with hexadecimal files to read a binary sequence of digits
Sequence Get_Bin_Block_Sequence( Read_Number &rn, int digits );
Sequence Get_Bin_Stream_Sequence( Read_Number &rn, int digits );










// Testing functions
bool Test_Next_Sequence( bool detailed );

bool Test_Decimal_Sequence( bool detailed );
bool Test_Binary_Sequence( bool detailed );

void Sequence_Test();

#endif
