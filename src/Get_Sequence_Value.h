#ifndef GET_SEQUENCE_VALUE_H
#define GET_SEQUENCE_VALUE_H
#include <string>
#include <iostream>
using namespace std;

#include "Sequence.h"

#define BINARY			2
#define DECIMAL			10
#define HEXADECIMAL		16

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// All functions here are to be used to be called for the Get Sequence Value
// All values should range from 0, 1, 2, ...., MAX_Value
// @param rn		number reading from
// @param digits	number of digits to take 
//		@note		this is a maximum, the function should deal with variable size classes

int Get_Sequence_Digits( Sequence s, int base );		// N digit groups
//int Get_Sequence_Poker( Read_Number rn, int digits );		// poker hand values











// Testing functions
bool Test_Sequence_Value( bool detailed );

bool Test_Digits( bool detailed );
#endif
