///////////////////////////////////////////////////////////////////////////////////////////////////
// Command Line Arguments
// This is a rough setup, no combining arguments
// Only use known sequence functions
// 
// nra.exe -{hrs} -{NVdbcg} # -o <full file output> -f <input file>
// nra.exe -N 2 -V 2 -r -g 5 -b 8 -r -o tmp.out -f ../../data/Pi1K-dec.txt 
//
// nra.exe				help menu
//
// -N #					Select numbered Next Sequence
//							0. Custom (user implemented CUSTOM_NEXT_SEQUENCE()
//							1. Digit block
//							2. Digit Stream
//							3. Random (not implemented)
//							4. etc ...	These are to be expanded by user research
//
// -V #					Select numbered Sequence Value
//							0. Custom (user implemented) CUSTOM_SEQUENCE_VALUE()
//							1. Number Value
//							2. Poker Value (not implemented)
//							3. etc ...	These are to be expanded by user research
//
// -r					remove predecimal
// -d #					Number of sequences to test 
// -b #					maximum size of each sequence ( dependent on Next_Sequence )
// -c #					number of classes ( dependent on Sequence_Value )
//
// -g #					Continuous Testing, # is for granularity how often to calculate results
//
// -f <filename>		input file, i.e. input.in: File should be in binary/Hexadecimal or decimal
// -h					hexadecimal input file, converted to binary on the fly
//
// -o <filename>		select output file for test, overide auto logs // currently full output
// -C					show digit counts in output file <TBD>			
// -D					show digit differential in output file <TBD>
// -M					record new min/max	<TBD>
// 
//
// -t					Diagnostic Test (not implemented)
// -T					Diagnostic Test (not implemented)
//
///////////////////////////////////////////////////////////////////////////////////////////////////