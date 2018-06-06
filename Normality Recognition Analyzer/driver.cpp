#include <fstream>
#include <iostream>
#include <string>
using namespace std;

#define DEVELOPMENT			// for development builds
//#define RELEASE			// for working releases
string VERSION;				// store current version of program

void Git_Init();
string Git_Version_Number();


int main()
{
	Git_Init();

	return 0;
}

void Git_Init()
{
	VERSION = Git_Version_Number();
	cout << "Normality Recognition Analyzer" << endl;
	
	#ifdef DEVELOPMENT
		cout << "Development Build: " << VERSION << endl;
	#else
		cout << "Release Version: " << VERSION << endl;
	#endif

	cout << "Author: Dr. Nicholas M. Richardson" << endl;



}
// This is used to keep track of revision numbers
// buildno.txt
string Git_Version_Number()
{
	// format of versions
	// <Version>.<Revision>.<Commit>.<Build>

	ifstream in("buildno.txt", ios::in);
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

	ofstream out("buildno.txt", ios::out);
	if (!out)
	{
		cout << "Unable to write buildno.txt" << endl;
		exit(1);
	}

	tmp = to_string(version);
	tmp += ".";
	tmp += to_string(revision);
	tmp += ".";

	// commit.txt should not be in repository.  When file is missing, commit version will be incremented. This may need to be adjusted manually
	in.open("commit.txt", ios::in);
	if (!in)
	{
		// need to increment commit
		commit = commit + 1;
		ofstream o("commit.txt", ios::out);
		o << commit;
		o.close();
	}

	tmp += to_string(commit);
	tmp += ".";
	tmp += to_string(++build);
	
	out << tmp << endl;
	out.close();

	return tmp;
}