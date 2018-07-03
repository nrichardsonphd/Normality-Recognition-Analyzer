#include "Analyze_List.h"



Analyze_List::Analyze_List()
{
	this->list = NULL;
	this->size = 0;
	this->median = false;
}


Analyze_List::~Analyze_List()
{
	if ( this->list != NULL )
		delete[] this->list;
}


void Analyze_List::Set_List( unsigned long long list_to_analyze[], int list_size )
{
	if ( this->list != NULL )
		delete[] this->list;

	this->size = list_size;
	this->list = new unsigned long long[this->size];
	
	for ( int i = 0; i < this->size; ++i )
		this->list[i] = list_to_analyze[i];

	this->expected = this->Expected_Value();
	this->median = false;
}

double Analyze_List::Expected_Value()
{
	this->expected = 0;
	for ( int i = 0; i < this->size; ++i )
		this->expected += this->list[i];

	this->expected /= this->size;

	return this->expected;
}


void Analyze_List::Display_Distribution( ostream &out )
{
	if ( this->size <= 10 )
	{
		out << "Digit\t";
		for ( int i = 0; i < this->size; ++i )
			out << i << "\t";
		out << endl << "\t";

		for ( int i = 0; i < this->size; ++i )
			out << this->list[i] << "\t";
	}
	else if ( this->size <= 10000 )
	{
		int col = 0;

		for ( int i = 0; i < this->size; ++i )
		{
			if ( this->list[i] > 0 )
			{
				if ( i < 10 )
					out << 0;
				if ( i < 100 )
					out << 0;
				out << i << ": ";

				if ( this->list[i] < 10 )
					out << 0;
				if ( this->list[i] < 100 )
					out << 0;
				out << this->list[i] << "\t";
				++col;


				if ( col % 7 == 0 )
					out << endl;
			}

		}
	}

	out << endl;
}

void Analyze_List::Display_Distribution()
{
	this->Display_Distribution( cout );
}

void Analyze_List::Summary( ostream &out )
{
	this->Display_Distribution();

	out << "*******************************************" << endl;
	out << "Sum: " << Sum() << "\r\n";
	//cout << "Sum^2: " << Sum_Squared() << "\t\t";
	//cout << "SumofSq: " << Sum_of_Squares() << endl;
	out << "Min: " << Min() << "\r\n";
	out << "Max: " << Max() << "\r\n";
	out << "Range: " << Range() << "\r\n";
	out << "Midrange: " << Mid_Range() << endl;
	
	out << "Mean: " << Mean() << "\r\n";
	
	//cout << "Median: " << Median() << "\t\t";
	//cout << "Q1: " << an.Q1() << endl;
	//cout << "Q3: " << an.Q3() << endl;

	out << "Var: " << Variance() << "\r\n";
	out << "Std: " << Standard_Deviation() << "\r\n";
	out << "Expected: " << this->expected << "\r\n";
	out << "Chi: " << Chi_Squared() << "\r\n";
	out << "*******************************************" << endl;
}

void Analyze_List::Summary()
{
	this->Summary( cout );
}

unsigned long long int Analyze_List::Sum()
{
	unsigned long long sum = 0;

	for ( int i = 0; i < this->size; ++i )
		sum += this->list[i];

	return sum;
}

unsigned long long int Analyze_List::Sum_Squared()
{
	return (unsigned long long int) pow( (double) this->Sum(), (double)2 );
}

unsigned long long int Analyze_List::Sum_of_Squares()
{
	unsigned long long sum = 0;

	for ( int i = 0; i < this->size; ++i )
		sum += this->list[i] * this->list[i];

	return sum;
}

unsigned long long Analyze_List::Min()
{
	unsigned long long min = this->list[0];

	for ( int i = 0; i < this->size; ++i )
	{
		if ( min > this->list[i] )
			min = this->list[i];
	}

	return min;
}

unsigned long long Analyze_List::Max()
{
	unsigned long long max = this->list[0];

	for ( int i = 0; i < this->size; ++i )
	{
		if ( max < this->list[i] )
			max = this->list[i];
	}

	return max;
}

unsigned long long int Analyze_List::Range()
{
	return this->Max() - this->Min();
}

double Analyze_List::Mid_Range()
{
	return (this->Max() + this->Min()) / 2.0;
}
/*
double Analyze_List::Q1()
{
	cout << "quartile not implemented" << endl; exit( 1 );
	if ( !this->median )
		Sort();
	
	if ( this->size % 4 == 0 )
		return this->list[this->size / 4];
	else if ( this->size % 4 == 1 )
		return this->list[this->size / 4];
	else if ( this->size % 4 == 2 )
		return this->list[this->size / 4];
	else if ( this->size % 4 == 3 )
		return this->list[this->size / 4];	

}
*/
/*
double Analyze_List::Median()
{
	if ( !this->median )
		Sort();
	//this->Display_Distribution();
	
	if ( this->size % 2 == 0 )
		return ( this->list[this->size / 2 - 1] + this->list[this->size / 2] ) / 2.0;
	else
		return (double) this->list[this->size / 2];
}
*/
/*
double Analyze_List::Q3()
{
	cout << "quartile not implemented" << endl; exit( 1 );
	if ( !this->median )
		Sort();
	

	
}
*/
void Analyze_List::Sort()
{
	unsigned long long tmp = 0;

	for ( int i =0; i < this->size - 1; ++i )
		for ( int j = i + 1; j < this->size; ++j )
			if ( this->list[i] > this->list[j] )
			{
				tmp = this->list[i];
				this->list[i] = this->list[j];
				this->list[j] = tmp;
			}

	this->median = true;
}

double Analyze_List::Mean()
{
	return (double) ( this->Sum() / ( double )this->size );
}



double Analyze_List::Standard_Deviation()
{
	return sqrt(this->Variance());
}

double Analyze_List::Variance()
{
	// sqrt(sum( x - mean)^2)/n-1
	// N - 1
	double mean = this->Mean();
	double sum = 0;

	for ( int i = 0; i < this->size; ++i )
		sum += pow(( this->list[i] - mean ),2);

	return sum / ( this->size - 1);
}

double Analyze_List::Chi_Squared()
{

	return this->Chi_Stream( this->list, this->size );;
}

// This will calculate chi squared from the list sent, no other operations used
double Analyze_List::Chi_Stream( unsigned long long digit_count[], int list_size )
{
	long long int sum = 0;
	double chi = 0;

	for ( int i = 0; i < list_size; ++i )
		sum += digit_count[i];
			
	double expected = (double) sum / list_size;

	for ( int j = 0; j < list_size; ++j )
	{
		chi = chi +( ( digit_count[j] - expected )*( digit_count[j] - expected ) ) / expected;
	}

	return chi;
		
}

// display a table with chi^2 and digit distribution, uses list sent only, list size is number of classes/digits
void Analyze_List::Display_Chi_Table( unsigned long long list_to_analyze[], int list_size )
{
	unsigned long long int sum = 0;
	
	for ( int i = 0; i < list_size; ++i )
		sum += list_to_analyze[i];

	double chi = this->Chi_Stream( list_to_analyze, list_size );

	printf( "%.3f", chi );
	cout << "\t| to " << sum << "\t\t| ";

	for ( int i = 0; i < list_size; ++i )
		cout << list_to_analyze[i] << "\t| ";
	



}