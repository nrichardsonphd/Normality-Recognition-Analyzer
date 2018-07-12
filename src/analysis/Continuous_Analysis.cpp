#include "Continuous_Analysis.h"

// This is called after the 1st sequence is started
void Continuous_Analysis_Initial( unsigned long long int *initial_results, ostream &out )
{
	out << "Initial Results" << endl;
}

// This is called based on granularity of full test. Every N Sequences are called here
void Continuous_Analysis_Interval( unsigned long long int *interval_results, ostream &out )
{
	out << "Interval Results" << endl;
}

// This is called after all calculations are completed with the final results
void Continuous_Analysis_Summary( unsigned long long int *final_results, ostream &out )
{
	out << "Final Results" << endl;
}