#include <iostream>
using namespace std;
// Function to perform the Extended Euclidean Algorithm
int extendedEuclidean(int a, int b, int &x, int &y) {
    // Base case: when b is 0, we have found the gcd and x, y for a
    if (b == 0) {	
        x = 1;
        y = 0;
        return a;
    }
    // Recursive step: apply the algorithm to the remainder
    int x1, y1;
    int gcd = extendedEuclidean(b, a % b, x1, y1);
    // Update x and y using the results from the recursive call
    x = y1;
    y = x1 - (a / b) * y1;
    return gcd;
}
// Function to calculate the multiplicative inverse of 'a' modulo 'm'
int multiplicativeInverse(int a, int m) {
    int x, y;
    int gcd = extendedEuclidean(a, m, x, y);
    // If gcd(a, m) is not 1, then the inverse doesn't exist
    if (gcd != 1) {
        cout << "Multiplicative inverse doesn't exist." << endl;
        return -1;
    }
    // Calculate the positive value of x as the multiplicative inverse
    int inverse = (x % m + m) % m;
    return inverse;
}
int main() {
    int a, b;
    cout << "Enter the first number: ";
    cin >> a;
    cout << "Enter the second number: ";
    cin >> b;
    int x, y; // Variables to store the solutions
    int gcd = extendedEuclidean(a, b, x, y);
    cout << "GCD of " << a << " and " << b << " is: " << gcd << endl;
    cout << "x: " << x << endl;
    int modInverse = multiplicativeInverse(a, b);
    if (modInverse != -1) {
        cout << "Multiplicative inverse of " << a << " in gf(" << b << ") is: " << modInverse << endl;
    }
    return 0;
}

