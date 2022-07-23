### Cameron Moore-Carter 3270737 COSC326
from datetime import datetime
import calendar
import sys
from string import capwords
    
    
def read_dates():
    """Checks for seperator validity and reads the dates in from input
    """
    
    for line in sys.stdin:
        total_sep = line.count(' ') + line.count('-') + line.count('/')
        if total_sep > 2:
            print("{} - INVALID: Too Many Seperators".format(line.rstrip()))
            continue
        line = line.rstrip()
        if (len(line) <= 5): # If line has less than six characters. As smallest length of a valid date is 6 characters (d-m-yy)
            print("{} - INVALID: Missing data values".format(line))
            continue
        elif(len(line) > 11): # If line has more than 11 characters. As largest length of a valid date is 11 characters (dd-mmm-yyyy) || (02-feb-2001)
            print("{} - INVALID: Input Data is too long. Max Length: 11 characters".format(line))
            continue
        # Quick check for more than three seperators 
        
        # Splits three lists to check for more than one seperator
        slash = line.split("/")
        dash = line.split("-")
        space = line.split(" ")
        # Check only one seperator was used
        if (len(dash) == 3 and len(slash) == 1 and len(space) == 1):            
            date = format_date(dash)
        elif (len(slash) == 3 and len(dash) == 1 and len(space) == 1):
            date = format_date(slash)
        elif (len(space) == 3 and len(slash) == 1 and len(dash) == 1):
            date = format_date(space)
        else:
            print("{} - INVALID: More than one seperator used or invalid format! Please use only one seperator: ['-', '/','<space>'] ".format(line))
            continue
        
        # As long as date is not none (eg an error has been detected and printed), print out the correctly formatted date 
        if(date != None): print(printdate(date))
    
    
    
    
    
def leap_year(year: int) -> bool:
    """Uses calendars "is_leap" function to validate leap year passed to function.

    Args:
        year (int): The year to check

    Returns:
        bool: true or false depending on the year passed in
    """
    return calendar.isleap(year)



def printdate(date: list) -> str:
    """Simply formats the date list as a string

    Args:
        date (list): the date list

    Returns:
        str: Dormatted string of dates to fit doc
    """
    return "{} {} {}".format(date[0], date[1], date[2])
      
def format_date(date: list):
    """Performs all sorts of checks/sanitisation and formats the date list
    
    Checks the list for correct type, and validates the date if inputted correctly before
    returning the newly formatted list. Will also print out errors if the date is invalid.

    Args:
        date (list): the seperated list of dates

    Returns:
        list: Returns None if the date is invalid or the formatted date if valid.
    """
    # Abbreviated Month list from calendar module
    months = calendar.month_abbr
    # More Sanitisation to check if correct date type has been passed
    if(not date[0].isdigit() or not date[2].isdigit()):
        print("{} - INVALID Please use correct data types for Day and Year".format(printdate(date)))
        return None
    # Check if Month is string or digit
    if(len(date[1]) <= 3):
        if(date[1].isdigit()):
            # Check if Month is between 1 and 12
            if(len(date[1]) == 2 and 10 <= int(date[1]) <= 12):
                # Index search the month list and replaces the month int with the abbreviated month
                date[1] = months[int(date[1])]
            elif(len(date[1]) <= 2 and 1 <= int(date[1]) <= 9):
                # Strip 0 from month and index place its correct abbreviated month
                # Eg 02 --> 2 --> Feb
                date[1] = months[int(date[1].strip("0"))]
            else:
                print("{} - INVALID: Month Number ({}) is out of range!".format(printdate(date), date[1]))
                return None
                
        else: # Month is a string
            # Capatalise month eg fEb --> Feb
            # Check for if month is in correct format (has to be all in same case or in capwords case)
            if(date[1] != date[1].upper() and date[1] != date[1].lower() and date[1] != capwords(date[1])):
                print("{} - INVALID: Month was not inputted in correct format".format(date))
                return None
            else:
                date[1] = capwords(date[1]) 
            if date[1] not in months:
                # String passed in not a month
                print("{} - INVALID: {} Is not a valid month!".format(date, date[1]))
                return None
    else:
        # Month is more than 3 characters, which is invalid
        print("{} - INVALID: {} Is not a valid month!".format(date, date[1]))
    monthtype = "%b"
    
    
    # Days (1 or 01)
    if(len(date[0]) == 1):
        # Adds a 0 to the day for correct format eg 1 --> 01
        date[0] = "0{}".format(date[0])
    daytype = "%d"
    
    # Years
    if(len(date[2]) == 2):
        # If last two year digits have been provided, check what century it is
        if(int(date[2]) > 49):
            date[2] = "19{}".format(date[2])
        else:
            date[2] = "20{}".format(date[2])
    yeartype = "%Y"
    
    # Check if year is valid
    if(int(date[2]) > 3000 or int(date[2]) < 1753):
            print("{} -- INVALID: {} Year Out Of Range".format(printdate(date), date[2]))
            return None
    if ((int(date[0])) == 29 and date[1] == "Feb"):
        if(leap_year(int(date[2])) == False):
            print("{} -- INVALID: {} is not a leap year".format(printdate(date), date[2]))
            return None
        
    
    # Try Date, all other invalid means month or date is wrong
    try:
        dateobj = datetime.strptime("{} {} {}".format(date[0], date[1], date[2]),"{} {} {}".format(daytype, monthtype, yeartype))
    except:
        print("{} -- INVALID: Day in {} is invalid.".format(printdate(date),date[1]))
        return None
    return date
        
    

    
read_dates()