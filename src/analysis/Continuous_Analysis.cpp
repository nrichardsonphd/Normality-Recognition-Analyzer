#include "Continuous_Analysis.h"





// This is called after the 1st sequence is started
void Constant_Analysis::Continuous_Analysis_Initial( unsigned long long int *initial_results )
{
	this->Default_Initial(initial_results);

	// Add Code Here for initial results
	// Setup all variables in class that will be needed.
	// This function is called 1st
}

// This is called based on granularity of full test. Every N Sequences are called here
void Constant_Analysis::Continuous_Analysis_Interval( unsigned long long int *interval_results )
{
	this->Default_Interval(interval_results);

	// Add Code Here for each interval result
	// Update all variables as needed
	// Use this->out for any interval output
}

// This is called after all calculations are completed with the final results
void Constant_Analysis::Continuous_Analysis_Summary( unsigned long long int *final_results )
{
	this->Default_Summary( final_results );

	// Add Code Here for final summary of results
	// Final calculations are done here
}


void Constant_Analysis::Default_Initial( unsigned long long int *initial_results )
{
	out << "Initial Results" << endl;
}

void Constant_Analysis::Default_Interval( unsigned long long int *initial_results )
{
	out << "Interval Results" << endl;
}

void Constant_Analysis::Default_Summary( unsigned long long int *initial_results )
{
	out << "Final Results" << endl;
}