#include <iostream>
using namespace std;

#include "../common/Read_Number.h"

int main()
{
	cout << "File Display" << endl;


	Read_Number rn;
	rn.Set_File( "../../data/Pi1K-hex.txt" );
	int b;
	int digits = 0;
	int st = 0;

	rn.Get_Next_Binary_Digit();		// offset
	rn.Get_Next_Binary_Digit();

	do
	{
		b = rn.Get_Next_Binary_Digit();
		cout << b;
		++digits;

		//if ( digits % 5 == 0 )
		//	cout << " ";

		if ( b == 1 )
		{
		//	if ( st > 3 )
				cout << " :: \tST: " << st << "\t Digits: " << digits << endl;
			
			st = 0;
		}
		else
			++st;
	}
	while ( b != -1 && digits < 100 );

	return 0;
}