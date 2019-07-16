#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main()
{
	string infile = "../../data/pi1M-dec.txt";				// input file
	string outfile = "../../logs/pi-3.txt";					// output file
	int groupings = 3;										// group size
	int skip_first = 2;										// ignore the 1st n characters of file
	int max_digits = 100;									// maximum number of digits to read
	cout << "Digit Grouping" << endl;

	ifstream in(infile, ios::in);
	ofstream out(outfile, ios::out);

	if (!in || !out)
	{
		cout << "Error opening file" << endl;
		exit(1);
	}

	for (int i = 0; i < skip_first; ++i)
		in.get();

	char c;
	int g = 0;

	while (!in.eof() && g < max_digits )
	{
		c = in.get();
		++g;

		out << c;

		if (g % groupings == 0)
			out << " ";
	}

	//out << "..." << endl;

	in.close();
	out.close();

	return 0;
}