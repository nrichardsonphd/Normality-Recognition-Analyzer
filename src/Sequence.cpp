#include "Sequence.h"


void Display_Sequence( Sequence s )
{
	cout << "Sequence: " << s.size << " :: ";
	for ( int i = 0; i < s.size; ++i )
		cout << s.seq[i] << " ";
	cout << endl;
}