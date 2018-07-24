///////////////////////////////////////////////////////////////////////////////////////////////////
// Command Line Arguments
// This is a rough setup, no combining arguments
// Only use known sequence functions
// 
// nra.exe -t -T -N 2 -V 2 -p -s 5 -b 8 -f ../../data/Pi1K-dec.txt -r tmp.out
//
// -t					Run all tests to ensure program is correct (quiet)
// -T					same as -t except detailed
//
// -N #					Select numbered Next Sequence
//						1. Digit blocks
//							2.
//
// -V #					Select numbered Sequence Value
//							1. Number value
//							2. 
//
// -h					hexadecimal input file, converted to binary on the fly
// -d #					Number of digits to test ( binary or decimal )
// -r					remove predecimal
// -b #					size of each sequence
// -s					stream digits with overlapping blocks (nonoverlapping is default)
// -c #					number of classes ( default is 2^n (hex) or 10^n(dec) where n is size of sequence )
//
// -C #					Continuous Testing, # is for granularity how often to calculate results
// -F					select full results for continuous testing, default is only important results
//
// -f <filename>		select input file for test
// -o <filename>		select output file for test
// -q <filename>		quiet summary, only digits and X^2, no class values
//
///////////////////////////////////////////////////////////////////////////////////////////////////