title Normality Recognition Analyzer 0.3 Release Test
	
SET exe="nra.exe"
SET decfile=data\pi1b-dec.txt
SET hexfile=data\pi1b-hex.txt

SET decdigits=100000
SET hexdigits=40000

echo Testing

SET fileno=1

:: Decimal File block testing With predecimal
:: %exe% -d %digits% %options% -b %fileno% -f %decfile% -o "dec%fileno%.txt"
:: Set /a fileno=%fileno%+1


:: Decimal Testing
START "NRA-DECIMAL-1" %exe% -f %decfile% -o "dec.txt" -d %decdigits% -g 1 -b 1 -c 10


:: Hexadecimal Testing
START "NRA-HEX-1" %exe% -f %hexfile% -h -o "hex.txt" -d %hexdigits% -g 1 -b 1 -c 2

