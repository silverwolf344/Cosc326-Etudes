# COSC326 Floating Point Etude

Instructions on how to run:
Code written by: Jakub Sawicki 5580766, Yashna Shetty 2901410, Cameron Moore-Carter 3270737, Remin Reji Mathew 2581103
Python was written in 3.7.2
Java and Python were used together to import and export the ibm floating points. Python was used as I (Cameron) struggled to find a
correct implementation for reading .bin files in java.
IMPORT

- Run floating.py
- Select precision and input filename
- The numbers should output to a formatted txt file called ibm.txt

EXPORT

- Run IbmTo754.java
- Select precision and output Filename
- The program will read the numbers from ibm.txt which was created by floating.py
- The program will print out converted doubles of the ibm floating point numbers to the console and then
- Write them to the specified output file.

TEST CASES:
IBM NUMBERS:
0100001001110110101000000000000000000000000000000000000000000000
1100001001110110101000000000000000000000000000000000000000000000
CONVERTS TO:
118.625
-118.625
CONVERTS TO:
0100000001011101101010000000000000000000000000000000000000000000
1100000001011101101010000000000000000000000000000000000000000000
