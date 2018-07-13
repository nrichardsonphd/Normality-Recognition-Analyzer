/// @file
#ifndef ANALYZE_NUMBER_H
#define ANALYZE_NUMBER_H
#include <iostream>
#include <string>
using namespace std;

#include "analysis\analysis_parameters.h"
#include "common\Read_Number.h"
#include "Sequence.h"

#include "Get_Next_Sequence.h"
#include "Get_Sequence_Value.h"

#include "analysis\Analyze_List.h"

#include "analysis\Constant_Analysis.h"

#define MIN_PROGRESS_DISPLAY		1000000
#define PROGRESS_MARKERS			1000

// Discrete analysis
// analyze for N digits and gives results
// results are returned as an array, Each class value 0,1,2,..., N holds the number of sequences found in that class
unsigned long long int *Analyze_Number( Sequence ( *Next_Sequence )(Read_Number &rn, int digits),							// return sequence of numbers for next group
										unsigned int( *Sequence_Value )( Sequence s ),				// return value of sequence
										Analysis_Parameters &ap );									// stores various parameters about numbers and analysis, will hold number of sequences tested after


// Continuous analysis
// analyze every n (n>=1) digits and give results until N digits
unsigned long long int * Analyze_Number_Continuously( Sequence( *Next_Sequence )(Read_Number &rn, int digits),				// return sequence of numbers for next group
														unsigned int( *Sequence_Value )(Sequence s),				// return value of sequence
														Analysis_Parameters &ap, 									// stores various parameters about numbers and analysis
														unsigned int granularity, 									// how often to calculate results, only new max/min are displayed
														unsigned int progress,										// how often to display results
														ostream &out );												// output for logfile

unsigned long long int *Get_Next_Set_Of_Sequences( Sequence( *Next_Sequence )(Read_Number &rn, int digits), unsigned int( *Sequence_Value )(Sequence s), Analysis_Parameters &ap, Read_Number &rn, unsigned int number_of_sequences );

#endif