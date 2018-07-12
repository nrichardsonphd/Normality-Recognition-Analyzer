#include "Constant_Analysis.h"



Constant_Analysis::Constant_Analysis()
{
}

Constant_Analysis::Constant_Analysis(Analysis_Parameters &ap )
{
	this->ap = &ap;
}

Constant_Analysis::~Constant_Analysis()
{

}

// This is called after the 1st sequence is started
void Constant_Analysis::Continuous_Analysis_Initial( unsigned long long int *initial_results, ostream &out )
{
	this->Default_Initial( initial_results, out );

	// Add Code Here for initial results
	// Setup all variables in class that will be needed.
	// This function is called 1st
}

// This is called based on granularity of full test. Every N Sequences are called here
void Constant_Analysis::Continuous_Analysis_Interval( unsigned long long int *interval_results, ostream &out )
{
	this->Default_Interval( interval_results, out );

	// Add Code Here for each interval result
	// Update all variables as needed
	// Use this->out for any interval output
}

// This is called after all calculations are completed with the final results
void Constant_Analysis::Continuous_Analysis_Summary( unsigned long long int *final_results, ostream &out )
{
	this->Default_Summary( final_results, out );

	// Add Code Here for final summary of results
	// Final calculations are done here
}


void Constant_Analysis::Default_Initial( unsigned long long int *initial_results, ostream &out )
{
	out << "Initial Results Default Setup" << endl;


	out << "Digits\t";
		for ( unsigned int i = 0; i < this->ap->total_number_of_classes; ++i )
			out << i << "\t";
	out << endl;

	this->max = -1;
	this->min = 100000000000;

}

void Constant_Analysis::Default_Interval( unsigned long long int *initial_results, ostream &out )
{
	double chisq;
	bool display = false;

	al.Set_List( initial_results, this->ap->total_number_of_classes );
	chisq = al.Chi_Squared();

	if ( this->max < chisq )
	{
		this->max = chisq;
		display = true;
	}
	if ( this->min > chisq )
	{
		this->min = chisq;
		display = true;
	}

	if ( display ) //|| this->ap->sequences_tested % progress == 0 )
	{
		out << "Interval Results ";
//	out << ap.digits_tested << "\t";
	for ( unsigned int j = 0; j < this->ap->total_number_of_classes; ++j )
		out << initial_results[j] << "\t";

		out << "\t\t";
		if ( abs( max - chisq ) < .00001 )
		out << "/\\";
		if ( abs( min - chisq ) < .00001 )
		out << "\\/";

		out << chisq;
		out << endl;

		display = false;
	}
}

void Constant_Analysis::Default_Summary( unsigned long long int *initial_results, ostream &out )
{
	out << "Final Results" << endl;

	out << "Maximum Chi-Squared: " << max << endl;
	out << "Minimum Chi-Squared: " << min << endl;
	out << endl;
}