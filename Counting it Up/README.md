# README for Etude 6 - By Cameron Moore-Carter and Jakub Sawicki

Cameron Moore-Carter 3270737
Jakub Sawicki 5580766
All code was written in c++ and compiled using the g++ compiler obtained from the GNU compiler collection.

How to use:
User is prompted for the n/k values which are then entered from the terminal. The program then outputs the
answer of n given k to console. Should any value of 0 be entered for n | k then the program will always output
the value of 1 (n=0,k=0 is actually undetermined as forces division by 0). Should the value of 1 be entered for
n | k then the answer will be simply the value that is not 1. All other values that are entered will output a
correct n given k answer and the overflow of the long long class is accounted for by dividing the sums with the
gcd until the answer is derived.

Resources:
For this Etude we used resources such as gcd (euclidean algorithm) and many articles relating to overflow
and big integers from geeksforgeeks.
