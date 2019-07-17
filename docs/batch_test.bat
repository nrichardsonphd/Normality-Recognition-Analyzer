title Normality Recognition Analyzer 0.3 Release Test
	
SET exe="nra.exe"
SET decfile=data\pi1b-dec.txt
SET hexfile=data\pi1b-hex.txt

SET decdigits=10000
SET bindigits=40000
SET seq_val=1
SET interval=1


:: Block Testing
SET next_seq=1

:: Decimal Testing
START "NRA-DECIMAL-1B" %exe% -N %next_seq% -V %seq_val% -r -d %decdigits% -b 1 -c 10 -g %interval% -f %decfile% -o "dec1b.txt"  
START "NRA-DECIMAL-2B" %exe% -N %next_seq% -V %seq_val% -r -d %decdigits% -b 2 -c 100 -g %interval% -f %decfile% -o "dec2b.txt"
START "NRA-DECIMAL-3B" %exe% -N %next_seq% -V %seq_val% -r -d %decdigits% -b 3 -c 1000 -g %interval% -f %decfile% -o "dec3b.txt"
START "NRA-DECIMAL-4B" %exe% -N %next_seq% -V %seq_val% -r -d %decdigits% -b 4 -c 10000 -g %interval% -f %decfile% -o "dec4b.txt"



:: Hexadecimal Testing
START "NRA-HEX-1B" %exe% -N %next_seq% -V %seq_val% -r -d %bindigits% -b 1 -c 2 -g %interval% -f %hexfile% -h -o "hex1b.txt"
START "NRA-HEX-2B" %exe% -N %next_seq% -V %seq_val% -r -d %bindigits% -b 2 -c 4 -g %interval% -f %hexfile% -h -o "hex2b.txt"
START "NRA-HEX-3B" %exe% -N %next_seq% -V %seq_val% -r -d %bindigits% -b 3 -c 8 -g %interval% -f %hexfile% -h -o "hex3b.txt"
START "NRA-HEX-4B" %exe% -N %next_seq% -V %seq_val% -r -d %bindigits% -b 4 -c 16 -g %interval% -f %hexfile% -h -o "hex4b.txt"
START "NRA-HEX-5B" %exe% -N %next_seq% -V %seq_val% -r -d %bindigits% -b 5 -c 32 -g %interval% -f %hexfile% -h -o "hex5b.txt"
START "NRA-HEX-6B" %exe% -N %next_seq% -V %seq_val% -r -d %bindigits% -b 6 -c 64 -g %interval% -f %hexfile% -h -o "hex6b.txt"
START "NRA-HEX-7B" %exe% -N %next_seq% -V %seq_val% -r -d %bindigits% -b 7 -c 128 -g %interval% -f %hexfile% -h -o "hex7b.txt"
START "NRA-HEX-8B" %exe% -N %next_seq% -V %seq_val% -r -d %bindigits% -b 8 -c 256 -g %interval% -f %hexfile% -h -o "hex8b.txt"



:: StreamTesting
SET next_seq=2

:: Decimal Testing
START "NRA-DECIMAL-1S" %exe% -N %next_seq% -V %seq_val% -r -d %decdigits% -b 1 -c 10 -g %interval% -f %decfile% -o "dec1s.txt"  
START "NRA-DECIMAL-2S" %exe% -N %next_seq% -V %seq_val% -r -d %decdigits% -b 2 -c 100 -g %interval% -f %decfile% -o "dec2s.txt"
START "NRA-DECIMAL-3S" %exe% -N %next_seq% -V %seq_val% -r -d %decdigits% -b 3 -c 1000 -g %interval% -f %decfile% -o "dec3s.txt"
START "NRA-DECIMAL-4S" %exe% -N %next_seq% -V %seq_val% -r -d %decdigits% -b 4 -c 10000 -g %interval% -f %decfile% -o "dec4s.txt"



:: Hexadecimal Testing
START "NRA-HEX-1S" %exe% -N %next_seq% -V %seq_val% -r -d %bindigits% -b 1 -c 2 -g %interval% -f %hexfile% -h -o "hex1s.txt"
START "NRA-HEX-2S" %exe% -N %next_seq% -V %seq_val% -r -d %bindigits% -b 2 -c 4 -g %interval% -f %hexfile% -h -o "hex2s.txt"
START "NRA-HEX-3S" %exe% -N %next_seq% -V %seq_val% -r -d %bindigits% -b 3 -c 8 -g %interval% -f %hexfile% -h -o "hex3s.txt"
START "NRA-HEX-4S" %exe% -N %next_seq% -V %seq_val% -r -d %bindigits% -b 4 -c 16 -g %interval% -f %hexfile% -h -o "hex4s.txt"
START "NRA-HEX-5S" %exe% -N %next_seq% -V %seq_val% -r -d %bindigits% -b 5 -c 32 -g %interval% -f %hexfile% -h -o "hex5s.txt"
START "NRA-HEX-6S" %exe% -N %next_seq% -V %seq_val% -r -d %bindigits% -b 6 -c 64 -g %interval% -f %hexfile% -h -o "hex6s.txt"
START "NRA-HEX-7S" %exe% -N %next_seq% -V %seq_val% -r -d %bindigits% -b 7 -c 128 -g %interval% -f %hexfile% -h -o "hex7s.txt"
START "NRA-HEX-8S" %exe% -N %next_seq% -V %seq_val% -r -d %bindigits% -b 8 -c 256 -g %interval% -f %hexfile% -h -o "hex8s.txt"





