#include <iostream>
#include <cmath>

void printBinary(const std::string& label, int num, int bits) {
    std::cout << label << " = ";
    for (int i = bits - 1; i >= 0; --i)
        std::cout << ((num >> i) & 1);
    std::cout << " (" << num << " in decimal)" << std::endl;
}

int boothsMultiplication(int M, int Q, int n) {
    int A = 0, Q_1 = 0, count = n;
    std::cout << "\nInitial values:\n";
    printBinary("A (Accumulator)", A, n);
    printBinary("Q (Multiplier)", Q, n);
    printBinary("M (Multiplicand)", M, n);
    std::cout << "Number of bits (n) = " << n << "\n";

    while (count--) {
        std::cout << "Iteration " << (n - count) << ":\n";
        if ((Q & 1) == 1 && Q_1 == 0) {
            A -= M; // A = A - M
            std::cout << "A = A - M\n";
        } else if ((Q & 1) == 0 && Q_1 == 1) {
            A += M; // A = A + M
            std::cout << "A = A + M\n";
        }
        printBinary("Updated A", A, n);
        printBinary("Updated Q", Q, n);
        
        Q_1 = Q & 1; // Save Q0 to Q-1
        Q = (Q >> 1) | ((A & 1) << (n - 1)); // Right shift Q
        A >>= 1; // Right shift A
        std::cout << "After Arithmetic Right Shift:\n";
        printBinary("A", A, n);
        printBinary("Q", Q, n);
        std::cout << "Q-1 = " << Q_1 << "\n";
    }
    return (A << n) | Q; // Combine A and Q
}

int main() {
    int multiplicand, multiplier;
    std::cout << "Enter the multiplicand (signed integer): ";
    std::cin >> multiplicand;
    std::cout << "Enter the multiplier (signed integer): ";
    std::cin >> multiplier;

    int numBits = std::max((int)std::log2(std::abs(multiplicand)) + 1, 
                            (int)std::log2(std::abs(multiplier)) + 1) + 1;

    // Adjust M and Q for two's complement representation
    int M = (multiplicand < 0) ? (~multiplicand + 1) & ((1 << numBits) - 1) : multiplicand;
    int Q = (multiplier < 0) ? (~multiplier + 1) & ((1 << numBits) - 1) : multiplier;

    int result = boothsMultiplication(M, Q, numBits);
    std::cout << "\nFinal Result: " << multiplicand << " * " << multiplier << " = " 
              << ((result & (1 << (numBits + numBits - 1))) ? result - (1 << (numBits + numBits)) : result) << std::endl;
    
    return 0;
}
