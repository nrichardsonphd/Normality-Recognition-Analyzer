#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
	cout << "File Merger" << endl;

	// open file with list of filenames
	ifstream in_list( "../../data/tmp/merge_list.txt", ios::in );
	if ( !in_list )
	{
		cout << "Could not open merge_list file" << endl;
		exit( 1 );
	}

	// 1st file is output file
	string outfile;
	in_list >> outfile;

	cout << outfile << endl << endl;

	// output all files into 1 large file
	outfile = "../../data/tmp/" + outfile;
	ofstream out( outfile, ios::out );
	
	string file;
	char tmp;
	
	// run through all files in list
	while ( in_list >> file )
	{
		cout << file << endl;
		file = "../../data/tmp/" + file;

		ifstream infile( file, ios::in );
		

		while ( infile >> tmp )
		{
			out << tmp;
		}

		infile.close();
	}
	
	out.close();



	return 0;
}