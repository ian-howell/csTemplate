/******************************************************************************
 * Programmer : Ian Howell
 * Date       : Aug 31, 2015
 * Description: This program reads in inputs from the user and then
 * 				creates a file from a template using that info
 *****************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <time.h>
using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;

// prints out a prompt for the user
void prompt();

// creates a string containing the entire conents
// of a C++ file using information provided by the user
string createFile(const string name, const string stuNum,
				const string sec, const string instruct,
				const string fileName, const string desc);

int main(int argc, char** argv)
{
	string name = "";
	string studentNumber = "";
	string section = "";
	string newFileName = "";
	string description = "";
	string instructor = "";

	// if only 1 argument is given in the command line
	if (argc == 1)
	{
		// get information from the user
		cout << "Enter your name\n";
		prompt();
		getline(cin, name);

		cout << "Enter your student number\n";
		prompt();
		cin >> studentNumber;

		cout << "Enter your section\n";
		prompt();
		cin >> section;

		cout << "Enter the name of the file\n";
		prompt();
		cin >> newFileName;

		cout << "Enter your instructor's name\n";
		prompt();
		cin >> instructor;

		// clear out the cin stream
		// description is just a convenient variable
		// to dump into
		getline(cin, description);
	}
	// if the user provided a homework number in the command line,
	// use these preformatted settings
	else if (argc == 2)
	{
		name = "Student Name";
		studentNumber = "12345678";
		section = "1";
		newFileName = argv[1]; 
		instructor = "Dr. Proffesor";
	}
	// if the user provides too many arguments
	else
	{
		cerr << "ERROR: Usage: " << argv[0] << " [file name]\n";
		exit(1);
	}



	ifstream exists(newFileName.c_str());
	string choice;
	if(exists >> choice)
	{
		cout << newFileName <<  " already exists, proceeding will overwrite.\n";
		cout << "Would you like to proceed? (y/n)\n";
		prompt();
		cin >> choice;

		if (choice == "n")
		{
			return 0;
		}
		else if (choice != "y")
		{
			cout << "Interpretting vague answer as no\n";
			return 0;
		}
		// clear out the cin stream
		// description is just a convenient variable
		// to dump into
		getline(cin, description);
	}

	// Get the description for this homework
	cout << "Enter a description for this file\n";
	prompt();
	getline(cin, description);

	// open a file stream
	ofstream newFile;
	string fileName = newFileName;
	newFile.open(fileName.c_str());

	// dump the formatted string into the file
	newFile << createFile(name, studentNumber, section, instructor,
		fileName, description) << endl;
	
	// close the file
	newFile.close();

	return 0;
}

void prompt()
{
	cout << ">>>";
}

string createFile(const string name, const string stuNum,
				const string sec, const string instruct,
				const string fileName, const string desc)
{
	string fileContents;
	// get current time in seconds from Unix Epoch
	time_t rawtime = time(NULL);
	// convert that time to a standard
	time(&rawtime);
	string date = ctime(&rawtime);
	date = date.substr(4,6) + ", " + date.substr(20, 4);

	// Template for program documentation
	fileContents = "/******************************************************\n";
	fileContents += " * Date      : " + date + "\n";
	fileContents += " * Programmer: " + name + "\n";
	fileContents += " * Student ID: " + stuNum + "\n";
	fileContents += " * Instructor: " + instruct + "\n";
	fileContents += " * Section ID: " + sec + "\n";
	fileContents += " * File title: " + fileName + "\n";
	fileContents += " * Description: " + desc + "\n";
	fileContents += " ****************************************************/\n\n";

	if (fileName == "main.cpp")
	{
		// Template for a basic C++ file
		fileContents += "#include <iostream>\n";
		fileContents += "using namespace std;\n";
		fileContents += "\n";
		fileContents += "int main()\n";
		fileContents += "{\n";
		fileContents += "\n\n\treturn 0;\n";
		fileContents += "}\n";
	}

	return fileContents;
}
