/// @file
#include "analysis_parameters.h"


void Default_Parameters( Analysis_Parameters &ap )
{
	//int base = 10;															///< base number to be tested, usually decimal or Hex tp binary
//	ap.max_digits = 1000;												///< number of digits to test, truncated, original base
	ap.digits_tested = 0;												///< used to keep track of how many digits tested in sequences, calculate by #sequences * size of sequence - skipped
	ap.remove_predecimal = true;											///< bypass any digits before the decimal ****.start

	ap.max_sequence_size = 1;														///< number of digits to get for each class, 0 for variable size classes
//	ap.max_class_size = 1;													///< maximum size of a class, must be at least block_size
//	ap.total_number_of_classes = 10;												///< total number of classes possible
//	ap.number_of_sequences_to_test = 1000;										// number of sequences to analyze		Total digits / block size

	ap.sequences_tested = 0;											/// incremented on every sucessfully tested block

	ap.file_constant = true;												///< number in file
	ap.filename = "../data/Pi1K-dec.txt";
}

void Display_AP( Analysis_Parameters ap)
{
	Display_AP( ap, cout );
}


void Display_AP(Analysis_Parameters ap, ostream &out )
{
	//out << "*********************************************************************" << endl;
	out << endl;
	out << "Analysis of Parameters" << endl;

	out << "Description of test" << endl;
	out << "\tConstant: " << ap.desc_constant << endl;
	if ( ap.file_constant ) out << "\tFilename: " << ap.filename << endl;
	out << "\tNext Sequence: " << ap.desc_next_sequence << endl;
	out << "\tSequence Classification: " << ap.desc_classification << endl << endl;

	out << "Selected Options" << endl;
	out << "\tRemove pre decimal: " << ((ap.remove_predecimal == true) ? ("TRUE") : ("FALSE")) << endl;
	out << "\tMaximum Sequence Size: " << ap.max_sequence_size << endl;
	out << "\tNumber of Classes: " << ap.number_of_classes_possible << endl;
	out << "\tNumber of Digits to test: " << ap.number_of_digits_to_test << endl << endl;

	out << "Results of test" << endl;
	out << "\tDigits Tested: " << ap.digits_tested << endl;
	out << "\tSequences Tested: " << ap.sequences_tested << endl;





	//out << "*********************************************************************" << endl;
	out << endl;
	/*
	cout << "\tBase: " << ap.base;			cout << "\t\t\tTest Digits: " << ap.total_digits;			cout << "\t\t\tRemove pre decimal: " << ((ap.remove_predecimal==true) ? ("TRUE") : ("FALSE")) << endl;
	cout << endl;

	cout << "\tBlock size: " << ap.block_size;			cout << "\t\t\tMaximum Class Size: " << ap.max_class_size;			cout << "\t\t\tMaximum Number of Classes: " << ap.number_of_classes << endl;
	


	cout << endl << "\tmutually exclusive" << endl;
	cout << "\t\t[Block: " << ((ap.block == true) ? ("TRUE") : ("FALSE")) << endl;
	cout << "\t\t[Stream: " << ((ap.stream == true) ? ("TRUE") : ("FALSE")) << endl;

	cout << endl;
	cout << "\tmutually exclusive" << endl;
	cout << "\t\t[Generated Constant: " << ((ap.generated_constant == true) ? ("TRUE") : ("FALSE")) << endl;
	cout << "\t\t[\tGenerated Constant: " << ap.gen_const << endl;
	cout << "\t\t[File Constant: " << ((ap.file_constant == true) ? ("TRUE") : ("FALSE")) << endl;
	cout << "\t\t[\tFilename: " << ap.filename << endl;

	// Somehow indicate the function pointers
	cout <<  endl;
	cout << "\tGet_Next_Digit: " << ap.fp_desc_next_digit << endl;

	cout << "\tGet_Next_Class: " << ap.fp_desc_next_class << endl;

	/*
	ap.in->open("../logs/tmp.txt", ios::in);
	
	if (!ap.in)
	{
		cout << "unable" << endl;
	}
	else
		cout << "able" << endl;
	ap.in->close();
	*/
	/*
	fopen_s( &ap.fp , "../logs/tmp.txt", "r" );
	if ( ap.fp )
	{
		cout << "fp able" << endl;
	}
	else
		cout << "fp unable" << endl;
	
	char x;

	while ( !feof( ap.fp ) )
	{
		x = getc( ap.fp );
		cout << "x: " << x << endl;
	}

	cout << "x: " << endl;*/
	
	//fclose( ap.fp );
//	cout << "\tGet_Class_Identifier: " << ap.fp_desc_class_identifier << endl;
//	cout << endl;

	
}
