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

// Discrete analysis
// analyze for N digits and gives results
void Analyze_Number( Sequence ( *Next_Sequence )(Read_Number &rn, int digits),							// return sequence of numbers for next group
					 unsigned int( *Sequence_Value )( Sequence s ),				// return value of sequence
					 Analysis_Parameters ap );									// stores various parameters about numbers and analysis


// Continuous analysis
// analyze every n (n>=1) digits and give results until N digits
void Analyze_Number_Continuously( Sequence( *Next_Sequence )(Read_Number &rn),				// return sequence of numbers for next group
								  unsigned int( *Sequence_Value )( Sequence s ),				// return value of sequence
								  Analysis_Parameters ap );									// stores various parameters about numbers and analysis


#endif