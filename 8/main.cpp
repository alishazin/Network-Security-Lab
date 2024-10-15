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

// Given a number, it will find the next prime number
int getNextPrime(int n) {
    while (1) {
        n = n+1;
        if (isPrime(n)) {
            return n;
        }
    }
}

// Generate an array consisting prime factors of a given number
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
int powerMod(long long x, int y, int z) {

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

void printVector(vector<int> vec, int as_char) {

    for (int i=0; i<vec.size(); i++) {
        if (as_char) {
            cout << (char) vec[i];
        } else {
            cout << vec[i] << " ";
        }
    }
    cout << endl;

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
                
        cout << "p: " << this->p << endl;
        cout << "q: " << this->q << endl;
        cout << "n: " << this->n << endl;
        cout << "phi: " << this->phi << endl;
        cout << "e: " << this->e << endl;
        cout << "d: " << this->d << endl << endl;

    }

    void encrypt(string plaintext, vector<int> &cipher) {

        int l = plaintext.length();

        for (int i=0; i<l; i++) {
            cipher.push_back(powerMod(plaintext[i], this->e, this->n));
        }

    }

    void decrypt(vector<int> cipher, vector<int> &plaintext) {

        int l = cipher.size();

        for (int i=0; i<l; i++) {
            plaintext.push_back(powerMod(cipher[i], this->d, this->n));
        }

    }

};

int main() {

    RSA rsa(17, 19);

    string text = "shazin 1029";
    cout << "Text: " << text << endl << endl;

    vector<int> cipher;
    rsa.encrypt(text, cipher);

    cout << "Cipher: " << endl;
    // printVector(cipher, 1);
    printVector(cipher, 0);
    cout << endl;
        
    vector<int> plaintext;
    rsa.decrypt(cipher, plaintext);

    cout << "Plaintext: " << endl;
    printVector(plaintext, 1);
    printVector(plaintext, 0);

    return 0;
}