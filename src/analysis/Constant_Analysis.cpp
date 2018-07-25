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
void Constant_Analysis::Continuous_Analysis_Interval( unsigned long long int *interval_results, ostream &out, bool full )
{
	this->Default_Interval( interval_results, out, full );


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
		for ( unsigned int i = 0; i < this->ap->number_of_classes_possible; ++i )
			out << i << "\t";
	out << endl;

	this->max = -1;
	this->min = 100000000000;

}

void Constant_Analysis::Default_Interval( unsigned long long int *initial_results, ostream &out, bool full )
{
	double chisq;

	al.Set_List( initial_results, this->ap->number_of_classes_possible );
	chisq = al.Chi_Squared();

	if ( this->max < chisq )
		this->max = chisq;
	if ( this->min > chisq )
		this->min = chisq;

	unsigned long long int sum = 0;
	for ( unsigned int j = 0; j < this->ap->number_of_classes_possible; ++j )
		sum += initial_results[j];
	
	if ( !full && sum == 1 )
		out << "Digits\t\tMin/Max" << endl;
	
	
	if ( full )
	{
		out << sum << "\t";

		//	out << ap.digits_tested << "\t";
		for ( unsigned int j = 0; j < this->ap->number_of_classes_possible; ++j )
			out << initial_results[j] << "\t";

		out << "\t\t";
		
		if ( abs( max - chisq ) < .00001 )
			out << "/\\";
		if ( abs( min - chisq ) < .00001 )
			out << "\\/";
		
		out << chisq << endl;
	}
	else if ( abs( max - chisq ) < .00001 || abs( min - chisq ) < .00001 )
	{
		out << sum << "\t\t";

		if ( abs( max - chisq ) < .00001 )
			out << "/\\";
		if ( abs( min - chisq ) < .00001 )
			out << "\\/";

		out << chisq << endl;
	}
		
}

void Constant_Analysis::Default_Summary( unsigned long long int *initial_results, ostream &out )
{
	out << "Final Results" << endl;

	out << "Minimum Chi-Squared: " << min << endl;
	out << "Maximum Chi-Squared: " << max << endl;

	out << endl << endl;
	
	double chisq;

	al.Set_List( initial_results, this->ap->number_of_classes_possible );
	chisq = al.Chi_Squared();

	out << "Final X^2 on " << this->ap->digits_tested << " digits with " << this->ap->number_of_digits_to_test << " sequences is " << chisq << endl;
	out << endl;
}

void Constant_Analysis::Display_Full_Result( unsigned long long int *results, ostream &out, bool class_list )
{
	this->Display_Summary( results, out );
	
	// show variance after standard deviation
	out << "Variance: " << al.Variance() << " ";

	// find minimum classes
	out << "Minimum classes: { ";
	unsigned long long int min = this->al.Min();
	for ( unsigned long long int i = 0; i < this->ap->number_of_classes_possible; ++i )
		if ( results[i] == min )
			out << i << " ";
	out << "} ";

	// find maximum classes
	out << "Maximum classes: { ";
	unsigned long long int max = this->al.Max();
	for ( unsigned long long int i = 0; i < this->ap->number_of_classes_possible; ++i )
		if ( results[i] == max )
			out << i << " ";
	out << "} ";

	// range and midrange
	out << "Midrange: " << this->al.Mid_Range() << "Range: " << this->al.Range();

	// display class results
	if ( class_list )
	{
		out << "Class List: { ";
		for ( unsigned int j = 0; j < this->ap->number_of_classes_possible; ++j )
			out << results[j] << "\t";
		out << "}";
	}

	out << endl;
}

void Constant_Analysis::Display_Summary_Result( unsigned long long int *results, ostream &out )
{
	this->Display_Summary( results, out );
	out << endl;
}

// private
void Constant_Analysis::Display_Summary( unsigned long long int *results, ostream &out )
{
	al.Set_List( results, this->ap->number_of_classes_possible );

	// Format of important data
	// Digits X^2 Min Max Mean StdDev
	out << "Digits: " << this->ap->digits_tested << "X^2: " << al.Chi_Squared() << "Minimum: " << al.Min() << "Maximum: " << al.Max()
		<< "Mean: " << al.Mean() << "Standard Deviation: " << al.Standard_Deviation();

}