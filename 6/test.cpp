#include <iostream>
#include <string>
#include <bitset>
using namespace std;
// Permutation and Compression P10
int permutationP10(int key) {
int result = 0;
result |= ((key >> 2) & 1) << 9;
result |= ((key >> 4) & 1) << 8;
result |= ((key >> 1) & 1) << 7;
result |= ((key >> 6) & 1) << 6;
result |= ((key >> 3) & 1) << 5;
result |= ((key >> 9) & 1) << 4;
result |= ((key >> 0) & 1) << 3;
result |= ((key >> 8) & 1) << 2;
result |= ((key >> 7) & 1) << 1;
result |= ((key >> 5) & 1) << 0;
return result;
}
// Left Circular Shift
int leftCircularShift(int key, int shift) {
return ((key << shift) | (key >> (10 - shift))) & 0x3FF;
}
// Permutation P8
int permutationP8(int key) {
int result = 0;
result |= ((key >> 5) & 1) << 7;
result |= ((key >> 2) & 1) << 6;
result |= ((key >> 6) & 1) << 5;
result |= ((key >> 3) & 1) << 4;

result |= ((key >> 7) & 1) << 3;
result |= ((key >> 4) & 1) << 2;
result |= ((key >> 9) & 1) << 1;
result |= ((key >> 8) & 1) << 0;
return result;
}
int main() {
cout << "Enter a 10-bit initial key (e.g., 1010000010): ";
string inputKey;
cin >> inputKey;
// Check if the input key has exactly 10 bits
if (inputKey.length() != 10 || inputKey.find_first_not_of("01") != string::npos) {
cerr << "Error: Please enter a valid 10-bit binary initial key." << endl;
return 1; // Exit with an error code
}
int initialKey = stoi(inputKey, 0, 2);
// Perform key generation
int p10Key = permutationP10(initialKey);
int leftPart = p10Key >> 5;
int rightPart = p10Key & 0x1F;
leftPart = leftCircularShift(leftPart, 1);
rightPart = leftCircularShift(rightPart, 1);
int shiftedKey = (leftPart << 5) | rightPart;
int subkey1 = permutationP8(shiftedKey);
leftPart = leftCircularShift(leftPart, 2);
rightPart = leftCircularShift(rightPart, 2);
shiftedKey = (leftPart << 5) | rightPart;
int subkey2 = permutationP8(shiftedKey);
cout << "Subkey 1: " << bitset<8>(subkey1) << endl;
cout << "Subkey 2: " << bitset<8>(subkey2) << endl;
return 0;
}