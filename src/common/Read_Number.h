#ifndef READ_NUMBER
#define READ_NUMBER

#include <string>
#include <fstream>
#include <iostream>
#include <cmath>
#include <cstdio>
using namespace std;



/// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @author Dr. Nicholas Richardson
/// @copyright TBD
/// @date	6-14-2018
/// @details
///		....
///		Read Number Class
///		....
/// @note
/// @warning
/// @bug
/// @todo
/// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class Read_Number
{
	public:
		Read_Number();
		Read_Number( string filename );
		~Read_Number();

		bool Set_File( string filename );							// filename with constant
		void Set_Stream( int buffer_size );							// how much to load from file into memory, default = 1; 1 character at a time

		bool Set_Constant( int Constant );							// choose a generated constant to use for new digits

		long long Get_Digits_Read();


		/////////////////////////////////////////////
		// return next digit in file.  
		//		Base 10		:	0 - 9
		//		Base 16		:	0 - 9, A - F, a - f; * will return number 0 - 15 as value
		//		Any '.' will be ignored.
		//		-1				end of file
		/////////////////////////////////////////////
		/// @ note Always Use Get_Next_Digit XOR Get_Next_Binary_Digit when reading one constant in a stream
		///			Do not swap between in same reading of number
		int Get_Next_Digit();										///< one digit at a time from number
		int Get_Next_Binary_Digit();								///< get the next binary digit, assumes a hex file

		void Remove_Decimal();		// remove digits until decimal

	private:
		string filename;						// filename of constant

		long long int digit_count;				// number of digits to read from file
		long long int digits_read;				// number of digits read already
		
		char *buffer;							// buffer to store digits in memory
		int buffer_pos;							// position in the buffer

		FILE *fp;								// point to current position in file


		char Get_Next_Stream_Char();// returns next char in stream, loads more if needed
		/// Set the size of stream for reading into memory
		const int STREAM_SIZE = 10000;		// Set for how much of file to load into memory


		/// store position for binary digits
		int position;
		int hex;

		bool gen_const;



};





#endif