/// @file
/// Constant Analyzer Menu System (CAMS)
/// \author Dr. Nicholas Richardson
#ifndef CAMS_H
#define CAMS_H
#include <iostream>
#include <fstream>
using namespace std;

#include "../setup.h"
#include "../analysis/analysis_parameters.h"

Analysis_Parameters Setup_Parameters();

void Select_Parallel(Analysis_Parameters ap);			// methods of parallelization
void Select_Constant(Analysis_Parameters ap);			// select number to be analyzed
void Select_Analysis_Method(Analysis_Parameters ap);	// select method of analysis
void Select_Process_Interval(Analysis_Parameters ap);	// select how often to calculate results during analysis
void Display_Results(Analysis_Parameters ap);			// displayy final results of analysis

#endif