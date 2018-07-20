/// @file
#ifndef SETUP_H
#define SETUP_H
#include <iostream>
#include <string>
using namespace std;

#define RELEASE "0.2b"				// Release version
#define DEBUG						// Debug mode for development



const int CONSTANTS = 3;

// Constant location in CONSTANTS_FILES
#define CUSTOM_FILE	0
#define PI			1
#define E			2

// Add new constants here

extern string CONSTANTS_FILES[CONSTANTS]; 

#endif