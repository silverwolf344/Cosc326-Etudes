#include "Integer.h"
#include <stdlib.h>
#include <string.h>
#include <cmath>
using namespace std;

// Using Char array, base 10, 
namespace cosc326 {

	const Integer BIGINTEGER_ZERO = Integer(0);

	Integer::Integer() {
		this->sign = true;
		this->numDigits = 0;
		this->capacity = 0;
		this->digits = nullptr;
	}

	Integer::Integer(const Integer& i) {
		*this=i;
	}
	/** 
	 * Takes a string in and turns into a char array
	 *  
	 **/
	Integer::Integer(const std::string& s) {
		int length = s.length();
		int numDigits = length;
		bool sign = true;
		if (s[0] == '-'){
			sign = false;
			numDigits--;
		}
		// Check for Empty String
		if (numDigits == 0){
			*this = BIGINTEGER_ZERO;
			return;
		}
		// Construct base
		Integer newInt;
		newInt.numDigits = numDigits;
		newInt.digits = new char[numDigits + 1];
		newInt.capacity = numDigits + 1;
		newInt.sign = sign;
		// Interate through string, store in a string reversed (explained in readme)
		for (int i = 0; i < numDigits; i++){
			char c = s[length - 1 - i];
			// Char between 0 and 9
			if (c >= '0' && c<= '9'){
				newInt.digits[i] = c - '0'; //Go from ASCII code to Numerical value
			} else {
				// isnt a digit
				*this = BIGINTEGER_ZERO;
			}

		}
		// End character so it dosent read past memory
		newInt.digits[-1] = '\0';
		*this = newInt;
	}
	/** 
	 * Takes an int in and turns into a char array
	 *  
	 **/
	Integer::Integer(const int& i) {
		int numDigits = 0;
		int tempCopy = i;
		bool sign = true;
		Integer newInt;
		if (tempCopy == 0){
			numDigits = 1;
		} else if (tempCopy < 0){
			sign = false;
			// Turn positive
			tempCopy = -1 * tempCopy;
		}
		// Iterate through base 10 to find number of digits
		for(;tempCopy > 0; numDigits++, tempCopy/=10);
		newInt.digits = new char[numDigits + 1];
		newInt.capacity = numDigits + 1;
		newInt.numDigits = numDigits;
		// Reset the copy
		tempCopy = i;
		// 12345 % 10 = 5 -> 12345/10 -> 1234 -> 1234 % 10 = 4 -> 1234 /= 10 = 123 -> 123 % 10 = 3 and so on
		for(int idx = 0; idx < numDigits; idx++, tempCopy /= 10){
			newInt.digits[idx] = tempCopy % 10;
		}
		newInt.digits[-1] = '\0';
		newInt.sign = sign;
		*this = newInt;
	}

	Integer::~Integer() {
		//std::cout<<"This shouldnt be running"<<std::endl;
		//delete[] this->digits;
	}

	Integer& Integer::operator=(const Integer& i) {
		this->sign = i.sign;
		this->numDigits = i.numDigits;
		this->digits = i.digits;
		this->capacity = i.capacity;
		return *this;
	}

	Integer Integer::operator-() const {
		Integer res = *this;
		if (res.sign == true) {
			res.sign = false;
		}else if (res.sign == false) {
			res.sign = true;
		}
		return res;
	}

	Integer Integer::operator+() const {
		return Integer(*this);
	}

	Integer& Integer::operator+=(const Integer& i) {
		*this = *this + i;
		return *this;
	}

	Integer& Integer::operator-=(const Integer& i) {
		*this = *this - i;
		return *this;
	}

	Integer& Integer::operator*=(const Integer& i) {
		*this = *this * i;
		return *this;
	}

	Integer& Integer::operator/=(const Integer& i) {
		*this = *this / i;
		return *this;
	}

	Integer& Integer::operator%=(const Integer& i) {
		*this = *this % i;
		return *this;
	}

	Integer operator+(const Integer& lhs, const Integer& rhs) {
		Integer result;
		Integer lhsCopy = Integer(lhs);
		Integer rhsCopy = Integer(rhs);
		if (lhsCopy.sign && !rhsCopy.sign) { // If rhs is negative its equal to lhs-rhs
			rhsCopy.sign = true;
			return (lhsCopy - rhsCopy);
		} else if (!lhsCopy.sign && rhsCopy.sign){ // Inverse of first case :)
			lhsCopy.sign = true;
			return (rhsCopy - lhsCopy);
		}
		int maxDigits = MAX(lhsCopy.numDigits, rhsCopy.numDigits) + 1; // Largest digit length + 1 (for overflow)
		// Allocate capacity
		result.digits = new char[maxDigits + 1];
		result.numDigits = maxDigits; 
		result.capacity = maxDigits + 1;
		bool overflow = false;
		int res;
		for (int i = 0; i < result.numDigits; i++){ // Go forward over numbers instead of backwards to carry over to higher magnitude term
			res = overflow ? 1 : 0; // Num to carry over into next magnitude
			if(i < lhsCopy.numDigits){
				res += lhsCopy.digits[i];
			}
			if (i < rhsCopy.numDigits){
				res += rhsCopy.digits[i];
			}
			if (res >= 10){
				overflow = true;
				res -= 10;
			} else {
				overflow = false;
			}

			result.digits[i] = res;
		}
		
		// remove leading 0's
		while(!result.digits[result.numDigits - 1]){ 
			result.numDigits--;
		}

		if (!lhs.sign && !rhs.sign){ // Both Negative -lhs + -rhs = -(lhs + rhs)
			result.sign = false;
		}
		result.digits[-1] = '\0';
		return result;
	}

	Integer operator-(const Integer& lhs, const Integer& rhs) {
		Integer result;
		Integer lhsCopy = lhs;
		Integer rhsCopy = rhs;
		bool comparison = lhsCopy == rhsCopy;
		if(comparison){ // The numbers are the same
			return BIGINTEGER_ZERO;
		}
		if (lhsCopy.sign && !rhsCopy.sign){ // lhs positive, rhs negative lhs - -rhs = lhs + rhs
			rhsCopy.sign = true;
			result = lhsCopy + rhsCopy;
			return result;
		} else if (!lhsCopy.sign && rhsCopy.sign){ // -lhs - rhs = -lhs + -rhs
			rhsCopy.sign = false;
			result = lhsCopy + rhsCopy;
			return result;
		} else if (!lhsCopy.sign && !rhsCopy.sign){ //-lhs - -rhs = -lhs + rhs = rhs - lhs
			lhsCopy.sign = true;
			rhsCopy.sign = true;
			return rhsCopy - lhsCopy; 
		} else { // Both positive, find maximum
			comparison = lhsCopy < rhsCopy; // If true, rhs is bigger
			if (comparison && lhsCopy.numDigits != rhsCopy.numDigits){
				// lhs - rhs = -(rhs - lhs)
				result = rhsCopy - lhsCopy;
				// Flip sign
				result.sign = !result.sign;
				return result;
			}
		}
		// If no if statements are satisfied, both are positive and lhs is larger
		int noDigits = lhsCopy.numDigits;
		result.digits = new char[noDigits + 1];
		result.numDigits = noDigits;
		bool underflow = false;
		int res;
		for (int i = 0; i < result.numDigits; i++){
			res = underflow ? -1 : 0; // Num to carry over into next magnitude
			if (i < lhsCopy.numDigits){
				res += lhsCopy.digits[i]; // Add lhs digit
			}
			if (i < rhsCopy.numDigits){
				res -= rhsCopy.digits[i];// Subtract rhs digit
			}

			if (res < 0){ // Res in negatives
				underflow = true;
				res +=10; // Add 10 to get remainder eg -2 to 8
			} else {
				underflow = false;
			}
			
			result.digits[i] = res;  // Set res as the digit
			
		}
		// Strip leading zeros
		while (!result.digits[result.numDigits - 1]){
			result.numDigits--;
		}
		// Escape char
		result.digits[-1] = '\0';
		return result;
	}

	Integer operator*(const Integer& lhs, const Integer& rhs) {
		Integer lhsCopy = Integer(lhs);
		Integer rhsCopy = Integer(rhs);
		Integer result;
		Integer prod;
		int carry;

		if (lhsCopy == BIGINTEGER_ZERO || rhsCopy == BIGINTEGER_ZERO) {
			return BIGINTEGER_ZERO;
		}

		if (lhsCopy.numDigits == 1 && lhsCopy.digits[0] == 1) {
			result = rhsCopy;
			return result;
		}
		if (rhsCopy.numDigits == 1 && rhsCopy.digits[0] == 1) {
			result = lhsCopy;
			return result;
		}

		int noDigits = lhsCopy.numDigits + rhsCopy.numDigits + 1;
		int tmpanswer;
		
		result.digits = new char[noDigits + 1];
		result.numDigits = noDigits;
		result.capacity = noDigits + 1;

		// Set all digits to zero.
		for (int i = 0; i < noDigits; i++){
			result.digits[i] = 0;
		}
		result.digits[-1] = '/0';

		for (int i = 0; i < lhsCopy.numDigits; i++) {
			// For ever rhs digit:
			carry = 0;
			for (int j = 0; j < rhsCopy.numDigits; j++) {
				// For every rhs digit, get result, pipe overflow over to carry for next loop
				tmpanswer = lhsCopy.digits[i] * rhsCopy.digits[j];
				prod = Integer(tmpanswer);
				int addition = 0;
				if (prod.numDigits > 0) {
					addition = carry + prod.digits[0];
				}
				else {
					addition = carry;
				}
				if (addition >= 10) {
					carry = 1;
					addition -= 10;
				}
				else {
					carry = 0;
				}

				result.digits[i + j] += addition;

				if (result.digits[i+j] >= 10) {
					carry++;
					result.digits[i + j] -= 10;
				}

				int factor = 1;
				for (int k = 1; k < prod.numDigits; k++) {
					carry += prod.digits[k] * factor;
					factor *= 10;
				}
			}
			if (carry) {
				result.digits[i + rhsCopy.numDigits] += carry;
			}
		}
		while (!result.digits[result.numDigits - 1]){
			result.numDigits--;
		}
		//result.digits[-1] = '\0';
		return result;
	}
	// Long division
	// If big number, divide and conquor and then multiply result
	// (n/2) + (n/2)
	// asymptotically O(M(N)*log(N)) where M(N) is the time for an NxN multiplication
	Integer operator/(const Integer& lhs, const Integer& rhs) {
		Integer quotient = Integer("0");
        Integer lhsCopy = Integer(lhs);
        Integer rhsCopy = Integer(rhs);
        bool isTrue = false;
        if (rhsCopy.digits == 0) {
            std::cerr<< "Cannot divide by zero!"<<std::endl;
        }
        else if (lhsCopy.sign == false && rhsCopy.sign == false) {
            -lhsCopy;
            -rhsCopy;
        }
        else if (lhsCopy.sign == false && rhsCopy.sign == true) {
            -lhsCopy;
            isTrue = true;
        }
		// Check for intMax, any lhs less than 10 nums can be cast to Int, and then long divided etc etc
		/*
		if (rhsCopy.numDigits < 10){
			quotient = longDivision(lhsCopy, 2);
			return quotient;
		}*/
		// Extraordinarly inefficient for values such as 12343554364543 / 2, but efficient for 123574385435 / 12365781674287
        while (lhsCopy >= rhsCopy) {
            lhsCopy = lhsCopy - rhsCopy;
            quotient = quotient + Integer("1");
        }
        if (isTrue) {
            -quotient;
        }
        return quotient;
    }
	// Converts an Integer to an int, make sure to check that overflow wont occur before calling
	int toInt(Integer &i) {
		if (!i.numDigits){
			return 0;
		}
		int res = 0;
		for (int idx = 0; idx < i.numDigits; idx++){
			res += pow(i.digits[idx],idx);
		}
		if (!i.sign){
			res *= -1;
		}
		std::cout<<"Res:"<<res<< std::endl;
		return res;
	}
	// Reference : https://www.geeksforgeeks.org/divide-large-number-represented-string/
	Integer longDivision(Integer& lhs, int divisor){
		Integer result;
		string storage;
		Integer lhsCopy = lhs;
		int i = lhsCopy.numDigits;
		int prefix = lhsCopy.digits[i];
		// Find prefix for long division
		while (prefix < divisor && i <= 0) {
			prefix = prefix * 10 + lhsCopy.digits[i--];
		}
		while(i > 0){
			// Store result in answer
			storage += (prefix / divisor) + '0';
			// Take next digit
			prefix = (prefix % 10) * 10 + lhsCopy.digits[i--];
		}
		if (storage.length() == 0){
			return Integer(0);
		} else{
			return Integer(storage);
		}




	}
	Integer operator%(const Integer& lhs, const Integer& rhs) {
        Integer result;
        Integer lhsCopy = Integer(lhs);
        Integer rhsCopy = Integer(rhs);
        if (lhsCopy < rhsCopy) {
            result = lhsCopy;
        }
        else if (lhsCopy == rhsCopy) {
            result = Integer("0");
        }
        else {
            while (lhsCopy >= rhsCopy) {
                lhsCopy = lhsCopy - rhsCopy;
            }
            result = lhsCopy;
        }
        return result;
    }

	// Output 
	std::ostream& operator<<(std::ostream& os, const Integer& i) {
		if (!i.numDigits){
			os << "0";
			return os;
		}
		if(i.sign == false){
			os << "-";
		} 
		char c;
		// Digit index moves backwards through numbers
		for (int idx = i.numDigits - 1; idx >= 0; idx--){
			// add '0' to go from char int value to ASCII character
			c = i.digits[idx] + '0';
			os << c;
		}
		return os;
	}
	// Input, passes as string to string consturctor
	std::istream& operator>>(std::istream& is, Integer& i) {
		std::string input;
		is >> input;
		i = Integer(input);
		return is;
	}

	bool operator<(const Integer& lhs, const Integer& rhs) {
		// Check signs
		if (lhs.sign && !rhs.sign){ // lhs true, rhs false then..
			return false;
		} else if (!lhs.sign && rhs.sign){ // lhs false, rhs true then..
			return true;
		} else if (!lhs.sign && !rhs.sign){ // both negative, compare the positives, return the inverse
			Integer lhscopy = Integer(lhs);
			Integer rhscopy = Integer(rhs);
			lhscopy.sign = true;
			rhscopy.sign = true;
			return !(lhscopy < rhscopy);
		}
		// Both Positive, quick check for num of Digits
		if (lhs.numDigits > rhs.numDigits) {
			return false;
		} else if (lhs.numDigits < rhs.numDigits) { 
			return true;
		} 
		// Same num of digits
		// Compare from highest magnitude of Digits
		int i = lhs.numDigits;
		while (i--){
			if (lhs.digits[i] > rhs.digits[i]){
				return false;
			} else if (lhs.digits[i] < rhs.digits[i]) {
				return true;
			}
		}
		// all digits equal
		return false;
	}

	bool operator> (const Integer& lhs, const Integer& rhs) {
		if (lhs == rhs){
			return false;
		} else {
			return !(lhs < rhs);
		}
	}

	bool operator<=(const Integer& lhs, const Integer& rhs) {
		if (lhs == rhs){ // Quick check for efficiency
			return true;
		} else if (lhs < rhs){
			return true;
		} else {
			return false;
		}
		
		
	}

	bool operator>=(const Integer& lhs, const Integer& rhs) {
		if (lhs == rhs){
			return true;
		} else {
			return (lhs > rhs);
		}
	}
	// Equality Operator
	bool operator==(const Integer& lhs, const Integer& rhs) {
		if (lhs.numDigits != rhs.numDigits) {
			return false;
		} 
		int i = lhs.numDigits;
		// Iterate through every digit
		while (i--){
			if (lhs.digits[i] != rhs.digits[i]){
				return false;
			}
		}
		// Same num
		return true;
	}

	bool operator!=(const Integer& lhs, const Integer& rhs) {
		return !(lhs == rhs);
	}


	Integer gcd(const Integer& a, const Integer& b) {
        Integer aCopy = a;
        Integer bCopy = b;
        Integer temp;
        while(bCopy != BIGINTEGER_ZERO) {
            temp = bCopy;
            bCopy = (aCopy % bCopy);
            aCopy = temp;
        }
        return aCopy;
    }

}
