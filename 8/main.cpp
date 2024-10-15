#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int gcd(int a, int b) {
		
	while (b != 0) {		
		int temp = b;
		b = a % b;
		a = temp;
	}
	
	return a;
}

int isPrime(int n) {

    int is_prime = 1;
    int i;

    // 0 and 1 are not prime numbers
    if (n == 0 || n == 1) {
        is_prime = 1;
    }

    // loop to check if n is prime
    for (i = 2; i <= n/2; ++i) {
        if (n % i == 0) {
            is_prime = 0;
            break;
        }
    }

    return is_prime;
}

int getNextPrime(int n) {
    while (1) {
        n = n+1;
        if (isPrime(n)) {
            return n;
        }
    }
}

void primeFactorization(int num, vector<int> &factors) {

    int cur_prime = 2;

    while (num != 1) {

        while (num % cur_prime != 0) {
            cur_prime = getNextPrime(cur_prime);
        }

        num = num / cur_prime;
        factors.push_back(cur_prime);
        cur_prime = 2;

    }

}

// Find the mod if the format is: x^y mod z
int powerMod(int x, int y, int z) {

    int hasAddition = 0;
    int initialX = x;
    vector<int> factorsY;
    primeFactorization(y, factorsY);

    if (factorsY.size() == 1) {
        hasAddition = 1;
        factorsY.clear();
        primeFactorization(y-1, factorsY);
    }

    int i=0;

    while (i < factorsY.size()) {

        if (factorsY[i] > 5) {
            x = powerMod(x, factorsY[i], z);
            // cout << "XX: " << x << endl;
        } else {
            x = pow(x, factorsY[i]);
        }
        if (x >= z) {
            x = x % z;
        }
        i++;
    }

    if (hasAddition) {
        x = x * initialX;
    }

    return x % z;

}

class RSA {

    public:

    int p, q, n, phi, e, d;

    RSA(int p, int q) {
        this->p = p;
        this->q = q;
        this->generateKeys();
    }

    void generateKeys() {

        this->n = this->p * this->q;
        this->phi = (this->p - 1) * (this->q - 1);

        // Finding e value (brute force method)
        for (int i=2; i<this->phi; i++) {
            if (gcd(this->phi, i) == 1) {
                this->e = i;
                break;
            }
        }

        // Finding d value
        for (int i=1; i<INT_MAX; i++) {
            if ((i * this->e) % this->phi == 1) {
                this->d = i;
                break;
            }
        }

    }

    void encrypt(string plaintext, long long cipher[]) {

        int l = plaintext.length();

        for (int i=0; i<l; i++) {
            cipher[i] = powerMod(plaintext[i], this->e, this->n);
        }

    }

    void decrypt(long long *cipher, long long plaintext[], int l) {

        for (int i=0; i<l; i++) {
            plaintext[i] = powerMod(cipher[i], this->d, this->n);
        }

    }

};

int main() {

    RSA rsa(11, 13);
    string a = "ALISHAZIN";
    int l = a.length();
    long long cipher[l];

    for (int i=0; i<l; i++) {
        cout << a[i];
    }
    cout << endl;

    rsa.encrypt(a, cipher);
    
    cout << "Cipher: " << endl;
    for (int i=0; i<l; i++) {
        cout << (char) cipher[i];
    }
    cout << endl;

    long long plaintext[l];

    rsa.decrypt(cipher, plaintext, l);

    for (int i=0; i<l; i++) {
        cout << (char) plaintext[i];
    }
    cout << endl;

    // cout << powerMod(65,103,143) << endl;

    return 0;
}