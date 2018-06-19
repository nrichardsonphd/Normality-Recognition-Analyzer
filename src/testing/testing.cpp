#include "testing.h"
 
bool Test_All(bool detailed)
{
	bool pass = true;
	cout << "Testing All Units" << endl;

	if ( Test_Read_Number(detailed) )
		cout << "Read Number: PASSED" << endl;
	else
	{
		cout << "Read Number: FAILED" << endl;
		pass = false;
	}

	return pass;
}
