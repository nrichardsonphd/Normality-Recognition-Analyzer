// Place function in this file to be called during continuous analysis

#ifndef CONTINUOUS_ANALYSIS_H
#define CONTINUOUS_ANALYSIS_H

#include <iostream>
using namespace std;

#include "Analyze_List.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
// This class is designed to be editted by the user.  Any variables needed can be stored here
// as necessary.  The functions Initial, Interval, and Summary will be called when performing
// continuous analysis on user determined intervals
///////////////////////////////////////////////////////////////////////////////////////////////////

class Constant_Analysis
{
	public:
		Constant_Analysis( unsigned int maximum_classes );


		void Set_Output_Stream( ostream &out );

		// Initialize continuous analaysis
		// This is called after the 1st sequence is started
		void Continuous_Analysis_Initial( unsigned long long int *initial_results );

		// This is called based on granularity of full test. Every N Sequences are called here
		void Continuous_Analysis_Interval( unsigned long long int *interval_results);

		// This is called after all calculations are completed with the final results
		void Continuous_Analysis_Summary( unsigned long long int *final_results );

	private:
		Analyze_List al;
		unsigned long long int max;
		unsigned long long int min;

		ostream out;

		void Default_Initial( unsigned long long int *initial_results );
		void Default_Interval( unsigned long long int *initial_results );
		void Default_Summary( unsigned long long int *initial_results );

};

#endif