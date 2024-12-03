#include <fstream>
#include <iostream>
#include <ostream>
#include <regex>

std::vector<std::string> instructions;

void findInstructions(const std::string &inputFileName) {
    instructions.clear();
    if (std::ifstream inputFile(inputFileName); inputFile.is_open()) {
        std::string line;
        std::regex instructionRegex(R"(mul\(\d{1,3}\,\d{1,3}\))");

        while (getline(inputFile, line)) {
            auto wordsBegin = std::sregex_iterator(line.begin(), line.end(), instructionRegex);
            auto wordsEnd = std::sregex_iterator();

            for (std::sregex_iterator i = wordsBegin; i != wordsEnd; ++i) {
                const std::smatch& match = *i;
                std::string matchstr = match.str();
                std::cout << matchstr << std::endl;
                instructions.push_back(matchstr);
            }
        }
    }
}

int getMultiplicationResult(const std::vector<std::string>& instructionVector) {
    std::regex numberToMultiplyRegex("\\d{1,3}");
    int sum = 0;

    for (auto instruction: instructionVector) {
        auto wordsBegin = std::sregex_iterator(instruction.begin(), instruction.end(), numberToMultiplyRegex);
        auto wordsEnd = std::sregex_iterator();

        std::smatch match = *wordsBegin;
        std::smatch secondMatch = *(++wordsBegin);
        std::string matchstr = match.str();
        std::string secondmatchstr = secondMatch.str();

        sum += stoi(secondmatchstr) * stoi(matchstr);
    }

    return sum;
}

int main() {
    std::cout << "Advent of Code 2024 - Day 03" << std::endl;
    findInstructions("C:/Users/zuzuz/CLionProjects/advent-of-code-2024/day-03/myInput.txt");
    std::cout << getMultiplicationResult(instructions);
    return 0;
}
