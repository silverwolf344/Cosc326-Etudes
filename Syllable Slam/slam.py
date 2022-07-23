import sys
import re

def count_y(syllable_count:int, word:str, vowels:str) -> int:
    """Special case for if a y is present

    Args:
        syllable_count (int): num of syllables
        word (str): word to check
        vowels (str[]): str list of vowels
    Returns:
        int: 1 or more if special case is met
    Yashna Shetty
    """
    if 'y' not in word: 
        return syllable_count
    
    if syllable_count == 0:
        for letter in word:
            if letter == "y":
                syllable_count += 1

    else:
        position = word.find('y')
        if word[position - 1] in vowels:
            return syllable_count
        else:
            return syllable_count + 1
####        if (word[-1] == "y"):
####            for vowel in vowels:
####                if(word[-2] == vowel):
####                    return syllable_count 
            # If last letter is a y and second to last letter isnt a vowel
####    return syllable_count + 1
                
def written_rules(word: str) -> int:
    """Counts vowels, adds 1 to the syllable count for each vowel.

    Args:
        word (str): word to check

    Returns:
        int: number of syllables
    Yashna Shetty
    """

    vowels = ["a", "e", "i", "o", "u"]

    syllables = 0

    for letter in word.lower():

        if letter in vowels:

            syllables += 1



    if word.lower()[-1] == "e":
        
        if syllables > 1:

            syllables -= 1

    return syllables


    
def triph_and_diph(word: str) -> int:
    """Checks the word for Triphthongs and Diphthongs  \n
    b. Subtract 1 for each Triphthongs and diphthongs in the word.

    Args:
        word (str): The word to check

    Returns:
        int: a negative number based on the written method rules
    Cameron Moore-Carter && Jakob Sawicki
    """
    number_of = 0 # Default case
    

    # Got rid of "oy" due to errors
    diph_list = ["oi", "ou", "igh", "ey", 
                 "ay", "ai", "ow", "oa", "ea", "ee", "ie", "oo", "ue"] #added some Diphthongs
    triph_list = ["our", "ire",] # fire, dire, ireland
    special_case_2 = "are" # flare, mare etc, basically just check for string with more than 3 characters, diph
    #### pattern = "[^aeiouAEIOU\s][a-zA-Z]*(ure|uri|ury)" # Checks for constenant before ure, uri, ury. Special Case 1
    for diph in diph_list:
        number_of -= word.count(diph)
    for triph in triph_list:
        number_of -= word.count(triph)
    # Check Special_Case_2
    if len(word) >= 3:
        number_of -= word.count(special_case_2)
    #### Check Special_Case_1
    #### number_of -= len(re.findall(pattern, word))

    # Checks to see if remove dip/tri will leave at 0
    if number_of < 0 and number_of + 2 == syllable_count:
        number_of += 1

    return number_of

vowels = ["a", "e", "i", "o", "u"]

for line in sys.stdin:
    line = line.rstrip().lower()
    syllable_count = 0
    syllable_count += written_rules(line)
    syllable_count = count_y(syllable_count, line, vowels)
    syllable_count += triph_and_diph(line)
    if syllable_count < 0:
        syllable_count = 0
    print("{}".format(syllable_count))
    