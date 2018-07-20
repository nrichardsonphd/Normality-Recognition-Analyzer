title Normality Recognition Analyzer 0.2b Release Test
	
SET exe="Normality Recognition Analyzer - 0.2b release.exe"
SET testfile=pi1K.txt
SET digits=1000
SET options="-r"
echo Testing

SET fileno=1

%exe% -d %digits% %options% -f %testfile% -o "batch_output%fileno%.txt"
Set /a fileno=%fileno%+1
%exe% -d %digits% %options% -f %testfile% -o "batch_output%fileno%.txt"