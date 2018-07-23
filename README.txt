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
//			1. Digit blocks
// -V #		Select numbered Sequence Value
//			1. Number value
//			2. 
// -h		hexadecimal input file, convert to binary
//
// -d #		Number of digits to test
// -r		remove predecimal
// -b #		maximum size of each sequence
// -c #		maximum number of classes
// -s		stream digits with overlapping blocks (nonoverlapping is default)
// 
// -f <filename>		select input file for test
// -o <filename>		select output file for test
// -q <filename>		quiet summary, only digits and X^2, no class values
//
// -C #		Continuous Testing, # is for granularity
///////////////////////////////////////////////////////////////////////////////////////////////////
