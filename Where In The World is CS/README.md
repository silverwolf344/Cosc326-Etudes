# COSC326 Where in the world is CS

Cameron Moore-Carter 3270737
How To Run
Run the Python file (3.9.5), it reads from stdin, so you are able to pipe in documents in the terminal.
Enter all of your coordinates, the program will print out the Long, Lat and Label if correct and Unable to process if Incorrect.
Once finished make sure to use the EOF escape character (CTRL-Z + ENTER in VSCODE).
The program will then generate the geojson file for you.
Open it on https://geojson.io/ (top right -> open file) to view the features.

Notes:
If a coordinate is inputted with more than 6 decimal places, it is rounded up to the 6th decimal place.
If the coordinate has no markers for lat or longitude. It is assumed to be lattitude first and then longitude. With both being positive if no negative markers are placed.
The program assumes that you put the decimal first, then degrees if any, then seconds if any.
Due to utf8 encoding, I couldnt find the right ascii symbols to test for degrees as it was spitting out a
weird A character instead. It is documented in one of the comments in sanatize_input function.

TEST CASES (CORRECT):
45.855 South 170.502319 E Dunedin
34.034 118.2788 W Los Angeles
12 21 TEST
1 1
0 0
29.77 N -95.372 Houston
N S E W 23 W 12 N
23.6999 W, 50.5556 This is also a Label
40° 26.767' N 79° 58.933' W Northern California
40 26.767  -79 58.933  W Northern California No Lat Label
40 26.767  -79 58.933   Northern California No Markers
40° 26′ 46″ N 79° 58′ 56″ W
40 26 46 N 79 58 56 W No Symbols
40° 26′ 46″  -79° 58′ 56″ W No Lat Label
40° 26′ 46″  -79° 58′ 56″ No Markers
40° 26′ 46″
INCORRECT CASES:
Ha Tricked You!
1 1 1 1 1 1 1 1 1 1 1 (too many numbers)
0.0000 (too few numbers)
26.7' 80° 24" S 79° 58′ 56″ (symbols in wrong places)
