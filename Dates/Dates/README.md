# COSC326 Dates

Enter a date from stdin in the format day month year using exclusivly seperators (-,/, )  
The program will print out the date if it is valid or provide an error as to why the date is invalid.  
The file is a python 3.10.2 
You should be able to run it and have it read all lines from stdin
There are no extra packages needed you should just be able to run the program straight from the command line.  
You can also pipe in files...  

Test Cases:  
29 feB 2000  
29 Feb 2000  
29 2 1900  
29 Feb 1900 -- INVALID: 1900 is not a leap year  
29 REC 21  
['29', 'Rec', '21'] - INVALID: Rec Is not a valid month!  
31 4 44  
31 Apr 2044 -- INVALID: Day in Apr is invalid.  
12 200 1945  
['12', '200', '1945'] - INVALID: Month Number (200) is out of range!  
21-2/2-
21-2/2- - INVALID: More than one seperator used or invalid format! Please use only one seperator: ['-', '/','<space>'] 
/29/2
/29/2 - INVALID: Missing data values
2!-2-22
2! 2 22 - INVALID Please use correct data types for Day and Year
feb-19-2999
feb 19 2999 - INVALID Please use correct data types for Day and Year
1222222222222222-feg-21
1222222222222222-feg-21 - INVALID: Input Data is too long. Max Length: 10 characters
---
--- - INVALID: Missing data values
19/aug/1333<space>
19/aug/1333 - INVALID: Too Many Seperators