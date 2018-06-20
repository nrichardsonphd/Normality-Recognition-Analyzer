#include "testing.h"
 
bool Test_All(bool detailed)
{
	bool pass = true;
	cout << "Testing All Units" << endl;

	
	
	if ( detailed )
	{
		Analysis_Parameters ap;
		cout << "Default Analysis Parameters" << endl;
		Display_AP( ap );
	}
	else
		cout << "Default Analysis Parameters" << endl;

	if ( detailed )
		cout << "Testing Read Number ................" << endl;

	if ( Test_Read_Number(detailed) )
		cout << "Read Number: [PASSED]" << endl;
	else
	{
		cout << "Read Number: [FAILED]" << endl;
		pass = false;
	}

	if ( detailed )
		cout << "Testing Get Next digit Decimal ................" << endl;

	if ( Test_Next_Sequence( detailed ) )
		cout << "Decimal Sequence: [PASSED]" << endl;
	else
	{
		cout << "Decimal Sequence: [FAILED]" << endl;
		pass = false;
	}


	if ( detailed )
		cout << "Testing Get Sequence Value ................" << endl;

	if ( Test_Sequence_Value( detailed ) )
		cout << "Sequence Value: [PASSED]" << endl;
	else
	{
		cout << "Sequence Value: [FAILED]" << endl;
		pass = false;
	}

	return pass;
}
