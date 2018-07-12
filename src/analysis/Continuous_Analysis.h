// Place function in this file to be called during continuous analysis

#ifndef CONTINUOUS_ANALYSIS_H
#define CONTINUOUS_ANALYSIS_H

#include <iostream>
using namespace std;

#include "Analyze_List.h"

// Initialize continuous analaysis
// This is called after the 1st sequence is started
void Continuous_Analysis_Initial( unsigned long long int *initial_results, ostream &out );

// This is called based on granularity of full test. Every N Sequences are called here
void Continuous_Analysis_Interval( unsigned long long int *interval_results, ostream &out );

// This is called after all calculations are completed with the final results
void Continuous_Analysis_Summary(unsigned long long int *final_results, ostream &out);


#endif