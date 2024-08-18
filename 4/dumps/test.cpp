// C++ program to find modular
// inverse of A under modulo M
#include <bits/stdc++.h>
using namespace std;

// A naive method to find modular
// multiplicative inverse of 'A'
// under modulo 'M'

int modInverse(int A, int M)
{
    for (int X = 1; X < M; X++)
        if (((A % M) * (X % M)) % M == 1)
            return X;
    return -1;
}

// Driver code
int main()
{
    int A = 19, M = 39;

    // Function call
    cout << modInverse(A, M);
    return 0;
}

