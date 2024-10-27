#include <iostream>
#include <vector>
#include <cmath>
#include <random>
using namespace std;

long gcd(long long a, long long b) {	
	while (b != 0) {		
		long long temp = b;
		b = a % b;
		a = temp;
	}
	return a;
}

long int powerMod(int a, int b, int mod) {
    
    long long int t;
    if(b==1)
        return a;

    t = powerMod(a,b/2,mod);

    if(b%2==0)
        return (t*t)%mod;
    else
        return (((t*t)%mod)*a)%mod;
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

    int p, q;
    long long n, phi, e, d;

    RSA(int p, int q) {
        this->p = p;
        this->q = q;
        this->generateKeys();
    }

    void generateKeys() {

        this->n = this->p * this->q;
        this->phi = (this->p - 1) * (this->q - 1);

        vector<int> e_list;

        // Finding all possible e value (brute force method)
        for (long long i=2; i<this->phi; i++) {
            if (gcd(this->phi, i) == 1) {
                this->e = i;
                e_list.push_back(i);
            }
        }

        std::random_device rd; // obtain a random number from hardware
        std::mt19937 gen(rd()); // seed the generator
        std::uniform_int_distribution<> distr(0, e_list.size()-1); // define the range

        // Choosing a e value from the list
        this->e = e_list[distr(gen)];

        // Finding d value
        for (long long i=1; i<INT_MAX; i++) {
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

    RSA rsa(991, 997);

    string text = "Shazin 1029";
    cout << "Text: " << text << endl;
    for (int i=0; i<text.length(); i++) {
        cout << (int) text[i] << " ";
    }
    cout << endl << endl;

    vector<int> cipher;
    rsa.encrypt(text, cipher);

    cout << "Cipher: " << endl;
    printVector(cipher, 0);
    cout << endl;
        
    vector<int> plaintext;
    rsa.decrypt(cipher, plaintext);

    cout << "Plaintext: " << endl;
    printVector(plaintext, 1);
    printVector(plaintext, 0);

    return 0;
}