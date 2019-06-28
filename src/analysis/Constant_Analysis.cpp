#include "Constant_Analysis.h"



Constant_Analysis::Constant_Analysis()
{
}

Constant_Analysis::Constant_Analysis(Analysis_Parameters &ap )
{
	this->ap = &ap;

	// Display options
	this->chi_squared = true;
	this->digit_count = true;
	this->digit_differential = true;
	this->globals = true;
	this->locals = true;

	this->last_max = 0;
	this->new_maxes = 0;

	this->last_min = 0;
	this->new_mins = 0;


	this->local_mins = 0;
	this->local_maxes = 0;

	this->zero_x = 0;
}

Constant_Analysis::~Constant_Analysis()
{

}

void Constant_Analysis::Output_Setup(bool chi_squared, bool digit_count, bool digit_differential, bool global_maxmin, bool local_maxmin)
{
	this->chi_squared = chi_squared;
	this->digit_count = digit_count;
	this->digit_differential = digit_differential;
	this->globals = global_maxmin;
	this->locals = local_maxmin;

	if (this->ap->number_of_classes_possible > MAX_SCREEN_CLASSES)
		cout << "Warning: large number of classes to write digit counts to screen.";

	if (this->ap->number_of_classes_possible > MAX_INTERVAL_CLASSES)
	{
		cout << "Error: Too many classes for interval recording of digit count. Disabling";
		this->digit_count = false;
		this->digit_differential = false;
	}

	if (this->ap->number_of_classes_possible > MAX_TOTAL_CLASSES )
		cout << "Warning: large number of classes to write to file.";

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

	out << "Seqnc's\tX^2\t\t\t";
	


	
	if (this->globals)
		out << "/\\\\/\t";	
	
	if (this->digit_count || this->digit_differential)
	{
		out << "\t";
		for (unsigned int i = 0; i < this->ap->number_of_classes_possible; ++i)
			out << i << "\t";
		out << endl;	
	}
	if (this->digit_differential)
	{
		out << "\t\t\t\t\tE(X)+-\t";
		for (unsigned int i = 0; i < this->ap->number_of_classes_possible; ++i)
			out << ".\t";
		out << endl;
	}

	

	// global max/min
	this->max_chi = -1;
	this->min_chi = 100000000000;

	// local max/min
	this->last_chi = -1;
	this->current_chi = -1;
	this->next_chi = -1;

	out << endl;

}

void Constant_Analysis::Default_Interval(unsigned long long int* initial_results, ostream& out)
{
	double chisq;

	al.Set_List(initial_results, this->ap->number_of_classes_possible);
	chisq = al.Chi_Squared();

	// calculate digits // switch to ap digits tested
	//unsigned long long int sum = 0;
	//for (unsigned int j = 0; j < this->ap->number_of_classes_possible; ++j)
	//	sum += initial_results[j];
	//cout << sum << " ? " << this->ap->digits_tested << endl;
	//out << sum << "\t" << chisq << "\t";

	out << this->ap->sequences_tested << "\t" << fixed << setprecision(14) << chisq << "\t";
	if (chisq < .000000000001)
	{
		out << "=0";
		++this->zero_x;
	}
	else if (this->globals) 	// global minimum and maximum (nonzero minimum)
	{

		if (this->max_chi < chisq)
		{
			this->last_max = this->ap->digits_tested;
			this->new_maxes++;
			this->max_chi = chisq;
		}
		if (this->min_chi > chisq)
		{
			this->last_min = this->ap->digits_tested;
			this->new_mins++;
			this->min_chi = chisq;
		}

		if (abs(max_chi - chisq) < .00001)
			out << "/\\";
		if (abs(min_chi - chisq) < .00001)
			out << "\\/";
	}

	// any local minimum and maximums
	// these outputs are referring to the previous interval result (off by 1)
	if (this->locals)
	{
		this->next_chi = chisq;

		if (this->current_chi == this->last_chi || this->current_chi == this->next_chi)
			out << "==";
		else if (this->current_chi > this->last_chi && this->current_chi > this->next_chi)
		{
			out << "^";
			++this->local_maxes;
		}
		else if (this->current_chi < this->last_chi && this->current_chi < this->next_chi)
		{
			out << "v";
			++this->local_mins;
		}

		this->last_chi = this->current_chi;
		this->current_chi = this->next_chi;
		out << "\t";
	}

	// display digit counts
	if (this->digit_count)
	{
		out << "\t";
		for (unsigned int j = 0; j < this->ap->number_of_classes_possible; ++j)
			out << initial_results[j] << "\t";
		out << endl;
	}
	
	

	// display differentials from expected
	if (this->digit_differential )
	{
		if (this->digit_count)
			out << "\t\t\t\t\t";

		unsigned long long int expected = (long long) floor(this->ap->sequences_tested / this->ap->number_of_classes_possible);
		out << expected << "\t";
		
		for (unsigned int j = 0; j < this->ap->number_of_classes_possible; ++j)
		{
			if (initial_results[j] == expected)
				out << "0" << "\t";
			else if (initial_results[j] > expected)
				out << "+" << initial_results[j] - expected << "\t";
			else
				out << "-" << expected - initial_results[j] << "\t";
		}	

		out << endl;
	}


	if (!this->digit_count && !this->digit_differential)
		out << endl;
	
}
	

void Constant_Analysis::Default_Summary( unsigned long long int *initial_results, ostream &out )
{
	out << endl << endl;
	out << "Final Results" << endl;

	out << "Minimum Chi-Squared: " << this->min_chi << "\tPosition: " << this->last_min << "\t New minimums: " << this->new_mins << endl;
	out << "Maximum Chi-Squared: " << this->max_chi << "\tPosition: " << this->last_max << "\t New maximums: " << this->new_maxes << endl;

	out << "Local Minimums: " << this->local_mins << endl;
	out << "Local Maximums: " << this->local_maxes << endl;

	out << "X^2 == 0 times: " << this->zero_x << endl;
	
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
	out << "Digits: " << this->ap->digits_tested << "\tX^2: " << al.Chi_Squared() << "\tMinimum: " << al.Min() << "\tMaximum: " << al.Max()
		<< "\nMean: " << al.Mean() << "\tStandard Deviation: " << al.Standard_Deviation();

}