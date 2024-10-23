#include <iostream>
#include <cmath>

using namespace std;

void printBinary(const string& label, int num, int bits) {
    cout << label << " = ";
    for (int i = bits - 1; i >= 0; --i)
        cout << ((num >> i) & 1);
    cout << " (" << num << " in decimal)" << endl;
}

int boothsMultiplication(int M, int Q, int n) {
    int A = 0, Q_1 = 0, count = n;
    cout << "\nInitial values:\n";
    printBinary("A (Accumulator)", A, n);
    printBinary("Q (Multiplier)", Q, n);
    printBinary("M (Multiplicand)", M, n);
    cout << "Number of bits (n) = " << n << "\n";

    while (count--) {
        cout << "Iteration " << (n - count) << ":\n";
        if ((Q & 1) == 1 && Q_1 == 0) {
            A -= M; // A = A - M
            cout << "A = A - M\n";
        } else if ((Q & 1) == 0 && Q_1 == 1) {
            A += M; // A = A + M
            cout << "A = A + M\n";
        }
        printBinary("Updated A", A, n);
        printBinary("Updated Q", Q, n);
        
        Q_1 = Q & 1; // Save Q0 to Q-1
        Q = (Q >> 1) | ((A & 1) << (n - 1)); // Right shift Q
        A >>= 1; // Right shift A
        cout << "After Arithmetic Right Shift:\n";
        printBinary("A", A, n);
        printBinary("Q", Q, n);
        cout << "Q-1 = " << Q_1 << "\n";
    }
    return (A << n) | Q; // Combine A and Q
}

int main() {
    int multiplicand, multiplier;
    cout << "Enter the multiplicand (signed integer): ";
    cin >> multiplicand;
    cout << "Enter the multiplier (signed integer): ";
    cin >> multiplier;

    int numBits = max((int)log2(abs(multiplicand)) + 1, 
                      (int)log2(abs(multiplier)) + 1) + 1;

    // Adjust M and Q for two's complement representation
    int M = (multiplicand < 0) ? (~multiplicand + 1) & ((1 << numBits) - 1) : multiplicand;
    int Q = (multiplier < 0) ? (~multiplier + 1) & ((1 << numBits) - 1) : multiplier;

    int result = boothsMultiplication(M, Q, numBits);
    int finalResult = ((result & (1 << (numBits + numBits - 1))) ? result - (1 << (numBits + numBits)) : result);

    // Print the final result in both binary and decimal
    cout << "\nFinal Result: " << multiplicand << " * " << multiplier << " = " 
         << finalResult << " (in decimal)\n";
    cout << "Binary Result: ";
    printBinary("", result, numBits * 2);  // Printing the result in binary with 2 * numBits

    return 0;
}
