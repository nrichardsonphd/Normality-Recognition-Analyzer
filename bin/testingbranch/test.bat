title Normality Recognition Analyzer 0.2b Release Test
	
SET exe="Normality Recognition Analyzer.exe"
SET decfile=pi1K-dec.txt
SET hexfile=pi1K-hex.txt
SET digits=1000
echo Testing

SET fileno=1

:: Decimal File block testing With predecimal
%exe% -d %digits% %options% -b %fileno% -f %decfile% -o "dec%fileno%.txt"
Set /a fileno=%fileno%+1

%exe% -d %digits% %options% -b %fileno% -f %decfile% -o "dec%fileno%.txt"
Set /a fileno=%fileno%+1

%exe% -d %digits% %options% -b %fileno% -f %decfile% -o "dec%fileno%.txt"
Set /a fileno=%fileno%+1

%exe% -d %digits% %options% -b %fileno% -f %decfile% -o "dec%fileno%.txt"
Set /a fileno=%fileno%+1

