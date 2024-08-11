#include <iostream>
#include <string>
using namespace std;

class CaesarCipher {

	void getStartAndEnd(int code, int &start, int &end) {
	
		if (code >= 65 && code <= 90) {
			start = 65;
			end = 90;
		} else if (code >= 97 && code <= 122) {
			start = 97;
			end = 122;
		} else {
			start = end = 0;
		}
	
	}

	public:
		
	int key;
		
	CaesarCipher(int key) {
		this->key = key % 26;
	}	
	
	string encrypt(string text) {
		
		int start;
		int end;
		string cipher;
	
		for (int i=0; i<text.length(); i++) {
			
			int code = (char) text[i];
			this->getStartAndEnd(code, start, end);
		
			if (start != 0) {			
				code = start + (((code + this->key) - start) % 26);
			}
				
			cipher.push_back((char) code);
			
		}
		
		return cipher;
	
	}
	
	string decrypt(string text) {
		
		int start;
		int end;
		string plaintext;
	
		for (int i=0; i<text.length(); i++) {
			
			int code = (char) text[i];
			this->getStartAndEnd(code, start, end);
			
			if (start != 0) {
				code = end - ((end - (code - this->key)) % 26);
			}	
			
			plaintext.push_back((char) code);
			
		}
		
		return plaintext;
	
	}
	
};

int main() {
	
	// 65 to 90
	// 97 to 122
	// 32 for space

	int choice;
	int key;

	cout << "\nEnter key: ";
	cin >> key;
	CaesarCipher cc(key);

	while (1) {
		cout << "\n1. Encrypt" << endl;
		cout << "2. Decrypt" << endl;
		cout << "3. Exit" << endl;

		cout << "Enter Choice: ";
		cin >> choice;

		string text;

		if (choice == 1) {
			cout << "\nEnter plaintext: ";
			std::getline(std::cin >> std::ws, text);
			cout << "Cipher: " << cc.encrypt(text) << endl;
		} else if (choice == 2) {
			cout << "\nEnter cipher: ";
			std::getline(std::cin >> std::ws, text);
			cout << "Plaintext: " << cc.decrypt(text) << endl;
		} else if (choice == 3) {
			cout << "Exiting.." << endl;
			break;
		} else {
			cout << "Invalid Choice" << endl;
		}
	}


    return 0;
}
