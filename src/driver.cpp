/// \file
/// @file
/// Normality Recognition Analyzer
/// \author Dr. Nicholas Richardson

#define _CRT_SECURE_NO_WARNINGS

#include <fstream>
#include <iostream>
#include <string>
#include <ctime>
using namespace std;

// Version Control Functions
string VERSION;				// store current version of program
void Git_Init();
string Git_Version_Number();



// Setting up program
#include "analysis\analysis_parameters.h"
#include "common\cams.h"

#include "testing\testing.h"
#include "testing\Read_Number-test.h" 

#include "Get_Next_Sequence.h"
#include "Get_Sequence_Value.h"

#include "Analyze Number.h"
#include "analysis\Analyze_List.h"

int main()
{
	// Initialize for Version Control
	Git_Init();

	cout << "Detailed Test: " << endl;
	Test_All( true );
	cout << endl;
	cout << "Summary Test" << endl;
	Test_All( false );
	Analysis_Parameters ap;
	Analyze_List al;

	unsigned long long int *results;

	

	time_t start = time(nullptr);
	cout << "Start Time: " << ctime( &start ) << endl;
	
	//ap.filename = "../data/Pi-Dec-1M.txt";
	ap.filename = "../../data/pi1billion.txt";
	ap.number_of_sequences_to_test = 10000;

	Display_AP( ap );
	results = Analyze_Number( Get_Block_Sequence, Get_Sequence_Digits_Base_10, ap );
	Display_AP( ap );
	
	cout << ap.digits_tested << "\t";
	for ( unsigned int i = 0; i < ap.total_number_of_classes; ++i )
		cout << results[i] << "\t";

	cout << "\t\t";
	al.Set_List( results, ap.total_number_of_classes );
	cout << al.Chi_Squared();
	cout << endl;
		
	//delete[] results;
	//exit( 1 );
	//ap.number_of_sequences_to_test = 1000;
	//Analyze_Number_Continuously( Get_Block_Sequence, Get_Sequence_Digits_Base_10, ap, 1, 25, cout);

	ofstream outfile( "../../logs/tmp123.txt", ios::out );
	Display_AP( ap );
	Analyze_Number_Continuously( Get_Block_Sequence, Get_Sequence_Digits_Base_10, ap, 1, 25, outfile );

	time_t end = time( nullptr );

	cout << "Start Time: " << ctime( &start );
	cout << "End Time: " << ctime( &end );
	cout << "Total Time: " << end - start << endl;
	cout << endl;
	//Analyze_Number( Get_Block_Sequence_Digits, Get_Sequence_Digits_Base_10, ap );

	//Analyze_Number( Get_Block_Sequence_Digits, Get_Sequence_Digits_Base_10, ap );
	
	/// CAMS 
	//ap = Setup_Parameters();				// TBD
	
	// Start Project
	/// select parallelization
	//Select_Parallel(ap);				// CAMS

	/// select constant to analyze
	//Select_Constant(ap);				// CAMS
	// pi, e, other, .. decimal/hex
	// file / generated
	// primes

	// setup get next digit


	/// select method how to analyze
	//Select_Analysis_Method(ap);		// CAMS
	// N-digit, poker, other ...
	// random search
	// check/compare
	// display only

	// setup get next group/class

	//cout << "Current Analysis Parameters" << endl;
	//Display_AP(ap);

	/// process
	// do analysis
	//Select_Process_Interval(ap);
	// one time run for N digits
	// report every kth digit ( complete analysis on up to k digits each time )
	// report every digit with continuous calculation ( save time, some calculations not possible ie median/mode)

	/// display results
	//Display_Results(ap);
	// chi, mead median, ....
	// other statistics based on classifications

	/// verify testing correct?
	return 0;
}

void Git_Init()
{
	VERSION = Git_Version_Number();
	cout << "Normality Recognition Analyzer" << endl;	
	cout << "Author: Dr. Nicholas M. Richardson" << endl;
	cout << "Development Build: " << VERSION << endl;
	cout << "----------------------------------" << endl << endl;


}
// This is used to keep track of revision numbers
// buildno.txt
string Git_Version_Number()
{
	// format of versions
	// <Version>.<Revision>.<Commit>.<Build>

	ifstream in("../../logs/buildno.txt", ios::in);
	if (!in)
	{
		cout << "Unable to open buildno.txt" << endl;
		exit(1);
	}
	int version;
	int revision;
	int commit;
	int build;
	string tmp;
	in >> version;
	in.get();
	in >> revision;
	in.get();
	in >> commit;
	in.get();
	in >> build;
	in.close();

	tmp = to_string(version);
	tmp += ".";
	tmp += to_string(revision);
	tmp += ".";
	tmp += to_string(commit);
	tmp += ".";
	tmp += to_string(++build);

	ofstream out("../../logs/buildno.txt", ios::out);
	if (!out)
	{
		cout << "Unable to write buildno.txt" << endl;
		tmp = "*.*.*.*";
	}
	else
	{
		out << tmp << endl;
		out.close();
	}

	return tmp;
}