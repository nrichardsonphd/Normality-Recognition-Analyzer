/// @file
/// @author Dr. Nicholas Richardson
#ifndef ANALYSIS_PARAMETERS
#define ANALYSIS_PARAMETERS
#include <string>
#include <iostream>
using namespace std;

struct Analysis_Parameters
{
	int base = 10;															///< base number to be tested, usually decimal or Hex tp binary
	int total_digits = 1000;												///< number of digits to test, truncated, original base
	bool remove_predecimal = true;											///< bypass any digits before the decimal ****.start

	int block_size = 1;														///< number of digits to get for each class, 0 for variable size classes
	int max_class_size = 1;													///< maximum size of a class, usually equal to block_size
	int number_of_classes = 10;												///< total number of classes possible


	/// @note: Block and stream are mutually exclusive
	bool block = true;														///< group by nonoverlapping blocks	14 15 92 65 ...
	
	/// @note: Block and stream are mutually exclusive
	bool stream = false;													///< slide group down number			14 41 59 92 ...
	
	/// @note: generation and files are mutually exclusive
	bool generated_constant = false;										///< Auto generated number
	std::string gen_const = "champerown\'s";
	
	/// @note: generation and files are mutually exclusive
	bool file_constant = true;												///< number in file
	std::string filename = "../data/Pi1K-dec.txt";

	/// function pointer to next digit
	string fp_desc_next_digit = "Grab 1 digit at a time sequentially";

	/// function pointer to next class
	string fp_desc_next_class = "Grab block of N digits";
	
	/// function pointer to class identifier
	string fp_desc_class_identifier = "Numerical Value";

};


void Display_AP(Analysis_Parameters ap);
#endif