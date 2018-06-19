#ifndef GET_NEXT_DIGIT_H
#define GET_NEXT_DIGIT_H
#include <string>
#include <iostream>
using namespace std;

#include "common\Read_Number.h"


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// All functions here are to be used to be called for the next class
// @param rn		number reading from
// @param digits	number of digits to take 
//		@note		this is a maximum, the function should deal with variable size classes

int Get_Decimal_Class( Read_Number rn, int digits );
int Get_Binary_Class( Read_Number rn, int digits );











// Testing functions
bool Test_Next_Class( bool detailed );

bool Test_Decimal_Class( bool detailed );
bool Test_Binary_Class( bool detailed );
#endif
