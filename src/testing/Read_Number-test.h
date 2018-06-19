#ifndef READ_NUMBER_TEST_H
#define READ_NUMBER_TEST_H
#include <cmath>
#include "../common/Read_Number.h"

// for testing functions in class
bool Test_Read_Number( bool detailed );

bool RN_Test_Nofile( string file, bool detailed );
bool RN_Test_Digit_Test( string file, bool detailed );
bool RN_Test_Decimal_Pre( string file, bool detailed );
bool RN_Test_Decimal_Remove( string file, bool detailed );
bool RN_Test_Binary( string file, bool detailed );






#endif
