#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <iostream>
using namespace std;

#define MAX_SEQUENCE_SIZE 32
#define MAX_BINARY	30
#define MAX_DECIMAL 8

struct Sequence
{
	int size;
	int seq[MAX_SEQUENCE_SIZE] = { 0 };
};


void Display_Sequence( Sequence s );

#endif

