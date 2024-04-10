#include "BigInteger.h"
#include <fstream>
#include <limits>
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input file> <output file>\n";
        return 1;
    }

    std::ifstream inputFile(argv[1]);
    std::ofstream outputFile(argv[2]);

    if (!inputFile.is_open() || !outputFile.is_open()) {
        std::cerr << "Error opening files.\n";
        return 1;
    }

    std::string lineA, lineB;
    std::getline(inputFile, lineA);
    inputFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(inputFile, lineB);

    BigInteger A(lineA);
    outputFile << A << "\n\n";

    BigInteger B(lineB);
    outputFile << B << "\n\n";

    BigInteger sum = A + B;
    outputFile << sum << "\n\n";

    BigInteger diff = A - B;
    outputFile << diff << "\n\n";

    BigInteger zero = A - A;
    outputFile << zero << "\n\n";

    BigInteger combo = A * 3 - B * 2;
    outputFile << combo << "\n\n";

    BigInteger product = A * B;
    outputFile << product << "\n\n";

    BigInteger squareA = A * A;
    outputFile << squareA << "\n\n";    

    BigInteger squareB = B * B;
    outputFile << squareB << "\n\n";

    BigInteger complex = A * A * A * A * 9 + B * B * B * B * B * 16;
    outputFile << complex << "\n";

    inputFile.close();
    outputFile.close();

    return 0;
}
