/// @file
#include "analysis_parameters.h"

void Display_AP(Analysis_Parameters ap)
{
	cout << "Analysis Parameters" << endl;

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

	cout << "\tGet_Class_Identifier: " << ap.fp_desc_class_identifier << endl;
}
