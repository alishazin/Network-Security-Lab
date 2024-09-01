#include <iostream>
using namespace std;

string railCipherEncrypt(string text, int key) {

    int l = text.length();
    string result;

    for (int i=0; i<key; i++) {

        int j;
        if (i == 0) {
            j = 0;
        } else if (i == key-1) {
            j = key - 1;
        } else {
            j = i;
        }

        int inv = 0;

        while (j < l) {

            result.push_back(text[j]);

            if (i == 0 || i == key-1) {
                j += key + (key - 2);
            } else {
                if (inv == 0) {
                    j += 2 * (key - (i+1));
                    inv = 1;
                } else {
                    j += 2 * i;
                    inv = 0;
                }
            }

        }

    }

    return result;

}

string railCipherDecrypt(string text, int key) {

    int l = text.length();
    string result(l, '*');
    
    int iter = 0;
    
    for (int i=0; i<key; i++) {

        int j;
        if (i == 0) {
            j = 0;
        } else if (i == key-1) {
            j = key - 1;
        } else {
            j = i;
        }

        int inv = 0;

        while (j < l) {

            result[j] = text[iter];
            iter++;

            if (i == 0 || i == key-1) {
                j += key + (key - 2);
            } else {
                if (inv == 0) {
                    j += 2 * (key - (i+1));
                    inv = 1;
                } else {
                    j += 2 * i;
                    inv = 0;
                }
            }

        }

    }

    return result;

}

int main() {

    int choice;
	int key;

	cout << "\nEnter the key: ";
	cin >> key;

	while (1) {
		cout << "\n\n1. Encrypt" << endl;
		cout << "2. Decrypt" << endl;
		cout << "3. Exit" << endl;

		cout << "Enter Choice: ";
		cin >> choice;

		string text;

		if (choice == 1) {
			cout << "\nEnter plaintext: ";
			std::getline(std::cin >> std::ws, text);
			cout << railCipherEncrypt(text, key);
		} else if (choice == 2) {
			cout << "\nEnter cipher: ";
			std::getline(std::cin >> std::ws, text);
			cout << railCipherDecrypt(text, key);
		} else if (choice == 3) {
			cout << "Exiting.." << endl;
			break;
		} else {
			cout << "Invalid Choice" << endl;
		}
	}

    return 0; 
}

/*
TOP ROW: start = 0, increment = k + (k - 2)
BOTTOM ROW: start = (k - 1), increment = k + (k - 2)
OTHER ROWS: start = r, inc1 = 2*(k-(r+1)), inc2 = 2*r
*/