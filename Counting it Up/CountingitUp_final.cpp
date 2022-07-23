// Counting it up Etude 6 by Jakub Sawicki and Cameron Moore-Carter
// User is requested by the program for the n and k values in order to
// calculate the n given k function. 

#include <iostream>

// Greatest common divisor function which is necessary for preventing overflow 
long gcd(long long i, long long j) {
    if (j != 0) {
        return gcd(j, i % j);
    } else {
        return i;
    }

}


/**
 * @brief Function takes user inputted n & k values and then firstly compares them to the basic cases.
 * The values are then taken and subject to factorial multiplication, which as a result is susceptible 
 * to product overflow thus our long long class overflow causing incorrect answers. We therefore use 
 * the GCD functionin order to condense the large values of n1 & k1 focusing only on the answer of n/k.
 * 
 * @param n The user picks the elements to choose from number.
 * @param k The user picks the elements chosen number.
 */
void N_given_K(long long n, long long k) {
    long long n1 = 1;
    long long k1 = 1;

    if (k > n - k)
      k = n - k;

    if (k == 0 | n == 0) {
        std::cout << "N given K answer: " << 0;
        return;
    } else if (k == 1) {
        std::cout << "N given K answer: " << n;
        return;
    } else if (n == 1) {
        std::cout << "N given K answer: " << k;
        return;
    } else {
        for (k; k != 0; k--) {
            n1 *= n;
            k1 *= k;

            long long divisor = gcd(n1, k1);

            n1 /= divisor;
            k1 /= divisor;
            n--;
        }

    std::cout << "N given K answer: " << n1;
    return;

    }
}



// Main class is responsible for prompting the user for input as well as calling the function of N_given_K
int main() {
    long long n;
    long long k;

    std::cout << "Type a N value:";
    std::cin >> n;
    std::cout << "Type a K value:";
    std::cin >> k;
    N_given_K(n,k);
    
}