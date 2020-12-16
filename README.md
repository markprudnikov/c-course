$ cat test.txt

1 2

4 3

5 5

$ ./lab_05 loadtext test.txt savetext out.txt

$ cat out.txt

1 2

4 3

5 5

$ ./lab_05 loadtext test.txt count

3

$ ./lab_05 loadtext test.txt print "[%d, %d] "

[1, 2] [4, 3] [5, 5] 

$ ./lab_05 loadtext test.txt print "[%d, %d]"

[1, 2][4, 3][5, 5]

$ ./lab_05 loadtext test.txt savebin out.bin

$ hexdump -C out.bin

00000000  01 00 00 02 00 00 04 00  00 03 00 00 05 00 00 05  |................|

00000010  00 00                                             |..|

00000012

$ ./lab_05 loadbin out.bin print "%d %d "

1 2 4 3 5 5
