# Cosc326 Etude 7 Where In The World Is CS
from contextlib import nullcontext
import io
import sys
from tkinter import NONE
import re


# Disgusting globals
location_keywords = ["S", "N", "W", "E","NORTH", "WEST", "EAST","SOUTH", "DEGREES", "MINUTES", "SECONDS", "LATITUDE", "LONGITUDE"]
lattitude_keywords = ["N", "S", "NORTH", "SOUTH", "LATITUDE"]
longitude_keywords = ["W", "E", "WEST", "EAST", "LONGITUDE"]


#def read_lines():
    #for line in sys.stdin:
        #NONE
        
def sanatise_input(input: str) -> str:    
    # [-+]?(?:\d*\.\d+|\d+|[A-Za-z]+)
    # [0-9]{1,2}[:|°][0-9]{1,2}[:|'](?:\b[0-9]+(?:\.[0-9]*)?|\.[0-9]+\b)"?[N|S|E|W]
    input = input.upper()
    pattern = re.compile("[-+]?(?:\d*\.\d+|\d+|[A-Za-z]+)")
    
    # DOES NOT WORK DUE TO ASCII ENCONDING THINKS THAT THE DEGREES SYMBOL IS Â°
    DDMpattern = re.compile("[^ ][-+]?(?:\d*\.\d+|\d+|[A-Za-z]+|[\'\"\°]?)")
    
    numbers = pattern.findall(input)
    number_count = 0
    for i in numbers:
        if isfloat(i):
            number_count += 1
            
    if number_count == 2:
        # 2 Numbers: decimal degrees
        lattitude, longitude, label = decimal_degrees(numbers)
    elif number_count == 4:
        # 4 numbers degrees minutes
        lattitude, longitude, label = degrees_minutes(numbers)
    elif number_count == 6:
        lattitude, longitude, label = minutes_seconds(numbers)
    lattitude = round(lattitude,6)
    longitude = round(longitude,6)
    if invalid(lattitude,longitude)==True:
        print("Invalid! Lat:{} Long:{} Label: {}".format(lattitude,longitude,label))
    else:
        print("Lat:{} Long:{} Label:{}".format(lattitude,longitude,label))
        
            
def isfloat(value) -> bool:
    try: 
        float(value)
        return True
    except ValueError: 
        return False
    
def minutes_seconds(numbers):
    pass

    
    
    
def degrees_minutes(numbers): 
    # 4 Numbers 
    lattitude = 0
    longitude = 0
    tempnumber_index = 0
    ran = False
    label = ""
    tempnumber = nullcontext
    print(numbers)
    # ['40', '26.767', 'N', '79', '58.933', 'W', 'NORTHERN', 'CALIFORNIA']
    for i in range(2, len(numbers)):
        # Should be a direction 
        if (not ran and isfloat(numbers[2])):
            # if third is a number -- should be a direction
            # then first two are a coordinate
            tempnumber = float(numbers[0]) + float(numbers[1]) / 60
            tempnumber_index = i
            ran = True
            
        elif isfloat(numbers[i-2]) and isfloat(numbers[i-1]) and numbers[i] in location_keywords:
            # Paired coords
            # For instance 90 12.2333 N is a paired coord
            if numbers[i] in lattitude_keywords:
                # Check if coord pair is in south, if so its negative
                if numbers[i] == "SOUTH" or numbers[i] == "S" and float(numbers[i-2]) > 0:
                    lattitude += -1 * float(numbers[i-2])
                    lattitude += float(numbers[i-1]) / 60
                else:
                    lattitude += float(numbers[i-2])
                    # add decimal minutes
                    lattitude += float(numbers[i-1]) / 60        
            elif numbers[i] in longitude_keywords:
                # Check if coord pair is in the west, if so it needs to be negative
                if numbers[i] == "WEST" or numbers[i] == "W" and float(numbers[i-2]) > 0:
                    longitude += -1 * float(numbers[i-2])
                    longitude += float(numbers[i-1]) / 60
                else:
                    longitude += float(numbers[i-2])
                    # add decimal minutes
                    longitude += float(numbers[i-1]) / 60
        #if one pair is satisfied and the other pair dosent have a NESW flag, other numbers the other pair
        elif isfloat(numbers[i-1]) and isfloat(numbers[i-2]) and lattitude == 0 and longitude != 0:
            lattitude += float(numbers[i-2]) + (float(numbers[i-1]) / 60)
            break
        elif isfloat(numbers[i-1]) and isfloat(numbers[i-2]) and lattitude != 0 and longitude == 0:
            longitude += float(numbers[i-2]) + (float(numbers[i-1]) / 60)
            break
        # No markers, so this is the last set of numbers, so it is implied to be longitude
        elif isfloat(numbers[i-1]) and isfloat(numbers[i-2]) and tempnumber != nullcontext and longitude == 0 and i >= tempnumber_index + 2:
            longitude += float(numbers[i-2]) + (float(numbers[i-1]) / 60)
            break
        
    if tempnumber != nullcontext:
        if lattitude == 0: lattitude = tempnumber
        elif longitude == 0: longitude = tempnumber   
    for i in numbers:
        # Check for a label
        if isfloat(i) != True and i not in location_keywords:
            label += i + " "
    
    latt_degrees = False
    long_degrees = False
    
    # If no pairs have been satisfied, the first number is the lat, second is long
    # ['40', '26.767', 'N', '79', '58.933', 'W', 'NORTHERN', 'CALIFORNIA']
    if longitude == 0 and lattitude == 0:
        for i in numbers:
            if isfloat(i) and lattitude == 0 and latt_degrees == False:
                lattitude += float(i)
                latt_degrees = True
            # Add minutes ONCE degrees are added
            elif isfloat(i) and latt_degrees == True and long_degrees == False:
                lattitude += float(i) / 60
                latt_degrees = False
            elif isfloat(i) and lattitude != 0 and long_degrees == False and latt_degrees == False:
                longitude += float(i)
                long_degrees = True
            elif isfloat(i) and latt_degrees == False and long_degrees == True:
                longitude += float(i) / 60
                
    return lattitude, longitude, label

def decimal_degrees(numbers):
    lattitude = 0
    longitude = 0
    label = ""
    tempnumber = nullcontext
    for i in range(1, len(numbers)):
        if isfloat(numbers[i-1]) and numbers[i] in location_keywords:
            # Paired coords, best case both numbers have pairs
            # For instance, 32.5 N, is a paired coord
            if numbers[i] in lattitude_keywords:
                
                # Check if coord pair is in south, if so its negative
                if numbers[i] == "SOUTH" or numbers[i] == "S" and float(numbers[i-1]) > 0:
                    lattitude += -1 * float(numbers[i-1])
                else:
                    lattitude += float(numbers[i-1])
                    
            elif numbers[i] in longitude_keywords:
                
                # Check if coord pair is in the west, if so it needs to be negative
                if numbers[i] == "WEST" or numbers[i] == "W" and float(numbers[i-1]) > 0:
                    longitude += -1 * float(numbers[i-1])
                else:
                    longitude += float(numbers[i-1])
                    
        # If one pair has already been satisfied, the other is this number
        elif isfloat(numbers[i-1]) and lattitude == 0 and longitude != 0:
            lattitude += float(numbers[i-1])
            break
        elif isfloat(numbers[i-1]) and lattitude != 0 and longitude == 0:
            longitude += float(numbers[i-1])
            break
        # This and Next is Numbers, hold onto number until something happens
        elif isfloat(numbers[i-1]) and isfloat(numbers[i]):
            tempnumber = float(numbers[i-1])
            
    if tempnumber != nullcontext:
        if longitude == 0: longitude = tempnumber
        elif lattitude == 0: lattitude = tempnumber
        
    for i in numbers:
        # Check for a label
        if isfloat(i) != True and i not in location_keywords:
            label += i + " "
    
    # If no pairs have been satisfied, the first number is the lat, second is long
    if longitude == 0 and lattitude == 0:
        for i in numbers:
            if isfloat(i) and lattitude == 0:
                lattitude += float(i)
            elif isfloat(i) and lattitude != 0:
                longitude += float(i)
    return lattitude, longitude, label

def invalid(lattitude, longitude) -> bool:
    if lattitude > 90 or lattitude < -90:
        return True
    elif longitude > 180 or longitude < -180:
        return True
    else:
        return False 

#When writing output, round up to 6 decimal places

input_file = open('coordinates.txt', 'r')
sys.stdin = io.StringIO(input_file.read())
lines = sys.stdin.readlines()
input_file.close()
for line in lines:
    l = line.strip()
    sanatise_input(l)

