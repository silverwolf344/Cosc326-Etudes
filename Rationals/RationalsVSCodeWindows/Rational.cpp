#include "Rational.h"
#include <cmath>
namespace cosc326 {

	Rational::Rational() {
		this->whole = Integer("0");
		this->numerator = Integer("0");
		this->denominator = Integer("0");
		this->pos = true;

	}

	Rational::Rational(const std::string& str) {
		Rational new_r;
		std::string rational_str = str;
		pos = true;
		if (str[0] == '-') {
			pos = false;
			rational_str = str.substr(1);
		}
		size_t frac_ind = rational_str.find('/');
		size_t decimal_ind = rational_str.find('.');

		if (decimal_ind != std::string::npos) {
			whole = Integer(rational_str.substr(0, decimal_ind));
			if (frac_ind != std::string::npos) {
				// There is decimal and slash
				// Delete decimal
				rational_str = rational_str.replace(decimal_ind,1,"");
				// Numerator is everything before slash
				numerator = Integer(rational_str.substr(0,frac_ind - 1));
				// Denom is everything after slash
				denominator = Integer(rational_str.substr(frac_ind));
				// Match number of digits to bring up to righ magnitude
				while (numerator.numDigits > denominator.numDigits){	
					denominator *= 10;
				}
				// Ignore wholenum for now
				whole = Integer(0);
			} 
			else {
				numerator = Integer(rational_str.substr(decimal_ind+1));
				denominator = Integer("1");
			}
		}
		else {
			whole = Integer("0");
			if (frac_ind !=std::string::npos) {
				numerator = Integer(rational_str.substr(0, frac_ind));
				denominator = Integer(rational_str.substr(frac_ind+1));
			}
			else {
				numerator = Integer(rational_str);
				denominator = Integer("1");
			}
		}

		new_r.whole = whole;
		new_r.numerator = numerator;
		new_r.denominator = denominator;
		new_r.pos = pos;
		*this = new_r;

	}

	Rational::Rational(const Rational& r) {
		*this = r;

	}

	Rational::Rational(const Integer& a) {
		Rational new_r;
		whole = Integer("0");
		pos = a.sign;
		numerator = a;
		denominator = Integer("1");

		new_r.whole = whole;
		new_r.pos = pos;
		new_r.numerator = numerator;
		new_r.denominator = denominator;
		*this = new_r;
	}

	Rational::Rational(const Integer& a, const Integer& b) {
		Rational new_r;
		whole = Integer("0");
		numerator = a;
		if (b.digits != 0) {
			denominator = b;
		}
		else {
			denominator = Integer("1");
		}
		if (a.sign == b.sign) {
			pos = true;
		}
		else {
			pos = false;
		}

		new_r.whole = whole;
		new_r.pos = pos;
		new_r.numerator = numerator;
		new_r.denominator = denominator;
		*this = new_r;


	}

	Rational::Rational(const Integer& a, const Integer& b, const Integer& c) {
		Rational a1 = Rational(a);
		Rational bc = Rational(b,c);

		*this = a1 + bc;
	}

	Rational::~Rational() {

	}

	Rational& Rational::operator=(const Rational& r) {
		this->pos = r.pos;
		this->numerator = r.numerator;
		this->denominator = r.denominator;
		this->whole = r.whole;
		return *this;
	}

	Rational Rational::operator-() const {
		Rational res = *this;
		res.pos = !(res.pos);
		return res;
	}

	Rational Rational::operator+() const {
		Rational res = *this;
		res.pos = true;
		return res;
		return Rational(*this);
	}

	Rational& Rational::operator+=(const Rational& r) {
		*this = *this + r;
		return *this;
	
	}


	Rational& Rational::operator-=(const Rational& r) {
		*this = *this - r;
		return *this;
	}

	Rational& Rational::operator*=(const Rational& r) {
		*this = *this * r;
		return *this;
	}

	Rational& Rational::operator/=(const Rational& r) {
		*this = *this / r;
		return *this;
	}

	Rational operator+(const Rational& lhs, const Rational& rhs) {
		Rational lhsCopy = lhs;
		Rational rhsCopy = rhs;
		Rational result;
		if(lhs.pos && !rhs.pos){
			//rhs is negative, so equal to lhs-rhs
			rhsCopy.pos = true;
			return (lhsCopy - rhsCopy);
		} else if (!lhs.pos && rhs.pos){
			//lhs is negative, so equal to rhs - lhs
			lhsCopy.pos = true;
			return (rhsCopy - lhsCopy);
		}
		// Both are same sign
		result.pos = lhs.pos;
		// Add wholenums
		result.whole = lhs.whole + rhs.whole;
		// Cases
		if (lhs.denominator == rhs.denominator){
			// Denominator is the same so just add the numerators and
			// whole numbers
			result.denominator = lhs.denominator;
			result.numerator = lhs.numerator + rhs.numerator;
			return(result);
		}
		// Different denominators :(, upscale to a factor of denominator and add them
		result.numerator = (lhs.numerator * rhs.denominator) + 
			(lhs.denominator * rhs.numerator);
		result.denominator = lhs.denominator * rhs.denominator;
		return result;
	}

	Rational operator-(const Rational& lhs, const Rational& rhs) {
        Rational lhsCopy = lhs;
        Rational rhsCopy = rhs;
        Rational result;
        if(!lhs.pos && !rhs.pos) {
            return (lhsCopy + rhsCopy);
        }
        else if (lhsCopy >= rhsCopy) {
            result.pos = true;
        }
        else {
            result.pos = false;
        }
        result.whole = lhs.whole - rhs.whole;
        if (lhs.denominator == rhs.denominator) {
            result.denominator = lhs.denominator;
            result.numerator = lhs.numerator - rhs.numerator;
            return result;
        }
        result.denominator = lhs.denominator * rhs.denominator;
        result.numerator = (lhs.numerator * rhs.denominator) - (rhs.numerator * lhs.denominator);
        return result;
    }

	Rational operator*(const Rational& lhs, const Rational& rhs) {
		Rational result;
		Rational lhsCopy = lhs;
		Rational rhsCopy = rhs;
		result.pos = true;
		if(rhs.pos != lhs.pos) {
			result.pos = false;
		}
		result.whole = lhs.whole * rhs.whole;
		result.numerator = lhs.numerator * rhs.numerator;
		result.denominator = lhs.denominator * rhs.denominator;
		return result;
	}

	Rational operator/(const Rational& lhs, const Rational& rhs) {
        Rational lhsCopy = lhs;
        Rational rhsCopy = rhs;
        Rational temp;
        temp.pos = true;
        if (rhs.pos != lhs.pos) {
            temp.pos = false;
        }
        temp.whole = rhs.whole * rhs.whole;
        temp.numerator = rhs.denominator;
        temp.denominator = rhs.numerator;
        return (temp * lhsCopy);
    }

	std::ostream& operator<<(std::ostream& os, const Rational& i) {
		if (!i.pos){
			os << '-';
		}
		Rational result = reduce(i);
		if (result.whole > 0){
			os << result.whole;
			os << ' ';
		}
		os << result.numerator;
		os << '/';
		os << result.denominator;
		return os;
	}
	std::istream& operator>>(std::istream& is, Rational& i) {
		std::string input;
		is >> input;
		i = Rational(input);
		return is;
	
	}

	bool operator<(const Rational& lhs, const Rational& rhs) {
		// Check signs
		if (lhs.pos && !rhs.pos){
			// lhs positive, rhs negative, lhs is bigger
			return false;
		} else if (!lhs.pos && rhs.pos){
			//lhs negative, rhs positive, rhs is bigger
			return true;
		} else if (!lhs.pos && !rhs.pos){
			//both negative, compare positive return opposite
			Rational lhsCopy = lhs;
			Rational rhsCopy = rhs;
			lhsCopy.pos = true;
			rhsCopy.pos = true;
			return !(lhsCopy < rhsCopy);
		}
		// Therefore both are positive, quick check for
		// equality and then check wholenum 
		if (lhs == rhs){
			return false;
		}
		if (lhs.whole < rhs.whole){
			return true;
		} else if (lhs.whole > rhs.whole){
			return false;
		}
		// Therefore both wholenumbers are the same, check numerator and denom
		// Larger numerators are better, whereas smaller denominators are better
		// Check denom first (smaller is better)
		if(lhs.denominator > rhs.denominator){
			return true;
		} else if (lhs.denominator < rhs.denominator){
			return false;
		}
		// Therefore both denominators are the same, check numerator 
		// Larger is better
		if (lhs.numerator < rhs.numerator){
			return true;
		} else if (lhs.numerator > rhs.numerator){
			return false;
		}
		// Worst case
		return false;
		
	}

	bool operator> (const Rational& lhs, const Rational& rhs) {
		if (lhs == rhs){
			return false;
		} else {
			return !(lhs < rhs);
		}
	}

	bool operator<=(const Rational& lhs, const Rational& rhs) {
		if (lhs == rhs){
			return true;
		} else {
			return(lhs < rhs);
		}
	}

	bool operator>=(const Rational& lhs, const Rational& rhs) {
		if (lhs == rhs){
			return true;
		} else {
			return (lhs > rhs);
		}
	}

	bool operator==(const Rational& lhs, const Rational& rhs) {
		if (lhs.whole == rhs.whole && lhs.numerator == rhs.numerator
		&& lhs.denominator == rhs.denominator){
			return true;
		}
		return false;
	}

	bool operator!=(const Rational& lhs, const Rational& rhs) {
		return !(lhs == rhs);
	}

	Rational reduce(const Rational& r){
        Rational rCopy = r;
        Integer num = rCopy.numerator;
        Integer denom = rCopy.denominator;
        Integer whole = rCopy.whole;
        while (num >= denom) {
            whole += Integer(1);
            num -= denom;
        }

        Integer simp = gcd(num, denom);
        num = num/simp;
        denom = denom/simp;
        rCopy.numerator = num;
        rCopy.denominator = denom;
        rCopy.whole = whole;
        return rCopy;
    }
}
