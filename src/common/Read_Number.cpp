#include "Read_Number.h"



Read_Number::Read_Number()
{
	this->digits_read = 0;
	this->digit_count = 0;
	this->fp = NULL;
	this->buffer = new char[STREAM_SIZE];
	this->buffer_pos = STREAM_SIZE - 1;
	this->position = 0;
	this->hex = 0;
}

Read_Number::Read_Number( string filename)
{
	this->digits_read = 0;
	this->digit_count = 0;
	this->fp = NULL;
	this->buffer = new char[STREAM_SIZE];
	this->buffer_pos = STREAM_SIZE - 1;

	this->Set_File( filename );			// open file
	this->position = 0;
	this->hex = 0;
}



Read_Number::~Read_Number()
{
	if ( this->buffer != NULL )
		delete[] this->buffer;

	if ( this->fp )
		fclose( fp );
}


bool Read_Number::Set_File( string filename )
{
	this->filename = filename;
	//printf( "Opening file %s\n", this->filename.c_str() );

	if ( fp != NULL )					// close old file
		fclose( fp );

	this->digits_read = 0;
	this->buffer_pos = STREAM_SIZE - 1;
	this->position = 0;

	fopen_s(&fp, this->filename.c_str(), "r" );
	if ( !fp )
	{
		printf( "Error opening file %s.\n", this->filename.c_str() );
		return false;
	}

	//printf( "File %s opened.\n", this->filename.c_str() );	
	return true;
}

long long int Read_Number::Get_Digits_Read()
{
	return this->digits_read;
}

int Read_Number::Get_Next_Digit()
{
	char c = ' ';
	c = this->Get_Next_Stream_Char();	// grab next character in stream
	++this->digits_read;				// read one more digit

	if ( c >= '0' && c <= '9' )
		return (int) c - 48;			// ascii of 0 is 48
	
	if ( c >= 'A' && c <= 'F' )
		return (int) c - 65 + 10;		// ascii A is 65, add 10: 10 == A

	if ( c >= 'a' && c <= 'f' )
		return (int) c - 97 + 10;		// ascii of a is 97, add 10: 10 == a

	// not an actual digit, adjust count
	--this->digits_read;

	// skip the decimal
	if ( c == '.' )
	{
		return Get_Next_Digit();	// call function again to skip '.'
	}

	// end of file
	if ( c == '\0' )
	{
		//printf( "End of file reached.\n%lld digits read.\n", this->digits_read );
		return -1;
	}

	// unknown file format
	printf( "Unkown character %c in file at position %lld(+1).\nYou may want to use %lld(+1) as the maximum number of digits.\n", c, this->digits_read, this->digits_read - 1);
	printf( "*The +1 refers to the decimal that will not be counted in digits read.\n" );
	exit( 1 );
	
}

char Read_Number::Get_Next_Stream_Char()
{
	// check if need more from file
	if ( this->buffer_pos == STREAM_SIZE - 1)		// -1 compensates for '\0' at end of buffer
	{
		// load next block of file
		fgets( this->buffer, STREAM_SIZE, fp );
		this->buffer_pos = 0;
	}

	// return next character
	return this->buffer[this->buffer_pos++];


}

void Read_Number::Remove_Decimal()
{
	while ( this->Get_Next_Stream_Char() != '.' );
		//++digits_read;
	//++digits_read;
//	cout << "Start remove" << endl;
	//cout << this->Get_Next_Digit();
	//cout << this->Get_Next_Digit(); cout << this->Get_Next_Digit(); cout << this->Get_Next_Digit(); cout << this->Get_Next_Digit(); cout << this->Get_Next_Digit(); cout << this->Get_Next_Digit();

//	exit( 1 );
}

int Read_Number::Get_Next_Binary_Digit()
{
	if ( this->position % 4 == 0 )
	{
		this->position = 0;
		this->hex = this->Get_Next_Digit();

		if ( this->hex == -1 )		// end of file 
			return -1;
		

		//cout << "Hex digit: " << hex << "\t";
		//cout << ( hex & 8 ) << ( hex & 4 ) << ( hex & 2 ) << ( hex & 1 ) << endl;
	}

	++this->position;
	if ( this->hex & (int) pow( 2, 4 - this->position ) )	// correct little indian
		return 1;
	else
		return 0;

}






