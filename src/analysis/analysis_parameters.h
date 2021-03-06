/// @file
/// @author Dr. Nicholas Richardson
#ifndef ANALYSIS_PARAMETERS
#define ANALYSIS_PARAMETERS
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

//#include "../Get_Next_Sequence.h"

//typedef int(*Get_Next_Digit)(string file);


struct Analysis_Parameters
{
	// used to count as testing
	unsigned int digits_tested = 0;											///< used to keep track of how many digits tested in sequences, calculate by #sequences * size of sequence - skipped
	unsigned int sequences_tested = 0;										/// incremented on every sucessfully tested block
	
	// used as parameters
	bool remove_predecimal = true;											///< bypass any digits before the decimal ****.start
	unsigned int max_sequence_size = 1;										///< number of digits to get for each class, 0 for variable size classes
	unsigned long long int number_of_classes_possible = 10;					///< total number of classes possible
	unsigned int number_of_sequences_to_test = 1000;						///< number of sequences to analyze		Total digits / block size
	unsigned long long int number_of_digits_to_test = 1*1000;					///< number of digits to test ( must be less than size*sequences )
	

	bool file_constant = true;												///< number in file
	std::string filename = "../data/Pi1K-dec.txt";

	string output_file = "";												// output file

	/// function pointer to next sequence description
	string desc_next_sequence = "Description of how to get next sequence of digits";
	
	/// function pointer to class value description
	string desc_classification = "Description of classifications of sequences";
	
	string desc_constant = "Description of constant being tested";

	/// @note: Block and stream are mutually exclusive
	//bool block = true;														///< group by nonoverlapping blocks	14 15 92 65 ...
	
	/// @note: Block and stream are mutually exclusive
	//bool stream = false;													///< slide group down number			14 41 59 92 ...
	
	/// @note: generation and files are mutually exclusive
	//bool generated_constant = false;										///< Auto generated number
	//std::string gen_const = "champerown\'s";
	
	/// @note: generation and files are mutually exclusive
	//bool start_reading = false;												///< flag used to signal file has started to be read
	//FILE *fp;																///< track progress through constant file
	


};



void Default_Parameters(Analysis_Parameters &ap);
void Open_File(Analysis_Parameters ap);
void Display_AP(Analysis_Parameters ap);
void Display_AP( Analysis_Parameters ap, ostream &out );


// Add functions to setup specific variables for different constants, bases, block sizes, options, etc
#endif