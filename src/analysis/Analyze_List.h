#pragma once

#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;


/// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @author Dr. Nicholas Richardson
/// @copyright TBD
/// @date	7-12-2017
/// @details	This class is capable of ananyzing a list of numbers and perform some statistical operations.  A list is can be sent in to summarize and organize the numbers.  Call the function
///				Set_List to initialize the class, this function will copy the list into the class.  The copy is required for the operations of Median, Q1, and Q3.  
///	
///				Chi_Stream is the only function that does not need to be initialized.  This function should only be used when you are calculating Chi for several points in the list.  It is faster
///				to calculate chi on the fly than copying the list for a full analysis.
///
///	Notable functions
/// @note	SetList		-	This will copy the list sent into the class.  All other function operations will use this list.
///						Call this function again to perform operations on another list
///
/// @note	Chi_Stream	-	This function is capable streaming a list sent as a parameter.  This should only be used when 
///						the list is large where keeping a copy will not be feasible.  This function ingnores the currently
///						stored list in the class
///
/// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




class Analyze_List
{

	public:
		Analyze_List();
		~Analyze_List();

		// send list to analyze
		/// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// @details	The Set_List function initializes the class by copying the list sent.  After the list is copied, the other class functions may be called.  Each function will use the list
		///				in the class to determine the statistical operation answer.
		///
		///	@param		list_to_analyze[]	This is an array of data to be analyzed.  The array will be copied and will not be modified
		///	@param		list_size			Number of elements in the list.
		/// @param		epected_value		The expected size for each element in the list.  This is only used with chi squared calculations
		///
		/// @returns	void
		///
		/// @note		Calling this function a second time will overwrite the current list.  Any other functions calls will use the new list.
		/// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void Set_List( unsigned long long list_to_analyze[], unsigned long long int list_size );

		double Expected_Value();
		
		unsigned long long Sum();								///< sum of list
		unsigned long long Sum_Squared();						///< sum^2: sum list then square total
		unsigned long long Sum_of_Squares();					///< x1^2 + x2^2 + ... + xn^2: square each term then sum


		unsigned long long Min();								///< minimum of list
		unsigned long long Max();								///< maximum of list
		unsigned long long int Range();							///< range of list: Max - Min
		double Mid_Range();										///< Midrange of list: (Max + Min)/2

		double Mean();											///< mean of list
		double Standard_Deviation();							///< standard deviation
		double Variance();										///< Variance = std^2
		
		// *** TODO Q1 and Q3
		/// @details		Q1, Q3, and Median required to modify copy of list stored
		/// @todo			These are not implemented yet
		//	double Q1();				// 1st quartile value
		//	double Median();			// median value
		//	double Q3();				// 3rd quartile value
		

		/// @details Mode
		///	return true/false mode exists
		///	m1:	minimum value mode
		///	m2: maximum value mode
		///	If greater than 2 values have same maximum frequency, no mode exists.
		/// @todo			These are not implemented yet
		bool Mode( unsigned long long &m1, unsigned long long &m2 );

		
		
		/// @details	Calculate the chi squared value of the list.  The expected value used for each element is the Mean of the list.
		double Chi_Squared();								// calculate chi squared for list, uses mean for expected value of each element

		/// @details	Used to calculate several chi squared values without copying the list for storage.
		/// @note		Other functions will not work with this function's list
		double Chi_Stream( unsigned long long list_to_analyze[], unsigned long long int list_size );		// calculate chi squared only, no other operations
		void Display_Chi_Table( unsigned long long list_to_analyze[], int list_size );	// display a table with chi^2 and digit distribution
		
		/// @details Display a summary of the distribution
		void Display_Distribution( ostream &out );
		void Display_Distribution();
		void Summary( ostream &out );
		void Summary();

	private:
		unsigned long long *list;					///< keep a copy of a list of numbers
		unsigned long long  size;									///< size of the list
		double expected;								///< expected value used for chi squared
		bool median;								// flag to use when sorting list to find median

		/// @details		Used to sort the list when calculating Q1, Q3, or Median
		void Sort();								// used to sort for median
};

