#ifndef CONSTANT_ANALYSIS_H
#define CONSTANT_ANALYSIS_H

#include <iostream>
using namespace std;

#include "Analyze_List.h"
#include "analysis_parameters.h"

// Place function in this file to be called during continuous analysis


///////////////////////////////////////////////////////////////////////////////////////////////////
// This class is designed to be editted by the user.  Any variables needed can be stored here
// as necessary.  The functions Initial, Interval, and Summary will be called when performing
// continuous analysis on user determined intervals
///////////////////////////////////////////////////////////////////////////////////////////////////

class Constant_Analysis
{
	public:
		Constant_Analysis();
		Constant_Analysis( Analysis_Parameters &ap );
		~Constant_Analysis();

		//////////////////////////////////////////////////////////////////////////
		// These 3 functions are used for continuous analysis
		// That is all numbers 1, 2, ... N are called and results are calculated each time
		// Useful for creating a graph of the prefix decimal and noting important digit count prefixes
		// such as max/min or turning points on a graph.
		/////////////////////////////////////////////////////////////////////////
		// Initialize continuous analaysis
		// This is called after the 1st sequence is started
		void Continuous_Analysis_Initial( unsigned long long int *initial_results, ostream &out );

		// This is called based on granularity of full test. Every N Sequences are called here
		// full is all information each time (true),
		// partial is only significant output to reduce file size (false)
		void Continuous_Analysis_Interval( unsigned long long int *interval_results, ostream &out_full, bool full );

		// This is called after all calculations are completed with the final results
		void Continuous_Analysis_Summary( unsigned long long int *final_results, ostream &out );

		/////////////////////////////////////////////////////////////////////////
		// These functions are for displaying a single result
		// Full displays all calculated information including size of each class
		// Summary only displays important data such as digits and chi squared only (saves memory)
		/////////////////////////////////////////////////////////////////////////
		
		// calculate all results and display one line
		// class_list TRUE: display class totals
		void Display_Full_Result( unsigned long long int *final_results, ostream &out, bool class_list  );
		
		// show only important results, remove all extra data
		// summary does not go to next line in output
		void Display_Summary_Result( unsigned long long int *final_results, ostream &out );
		

		private:

			Analyze_List al;
			Analysis_Parameters *ap;
			double max;
			double min;

			double max_chi;
			double min_chi;

			// these are for continuous analysis only
			void Default_Initial( unsigned long long int *initial_results, ostream &out );
			void Default_Interval( unsigned long long int *initial_results, ostream &out, bool full );
			void Default_Summary( unsigned long long int *initial_results, ostream &out );

			// this is for 1 record to display
			void Display_Summary( unsigned long long int *initial_results, ostream &out );


};


#endif
