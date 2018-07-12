Command Line Arguments

///////////////////////////////////////////////////////////////////////////////////////////////////
// Command Line Arguments
// This is a rough setup, no combining arguments
// Only use known sequence functions
// 
// nra.exe -t -T -N 2 -V 2 -p -s 5 -b 8 -f ../../data/Pi1K-dec.txt -r tmp.out
//
// -t		Run all tests to ensure program is correct (quiet)
// -T		same as -t except detailed
//
// -N #		Select numbered Next Sequence
// -V #		Select numbered Sequence Value
//
// -p		remove predecimal
// -s #		number of sequences to test
// -b #		size of each sequence
//
// -?		nonoverlapping blocks of digits
// -?		stream digits with overlapping blocks
// 
// -f <filename>		select input file for test
// -r <filename>		select output file for test
//
// -c		Continuous Testing
// -g #		granularity for continuous testing
///////////////////////////////////////////////////////////////////////////////////////////////////