#include <fstream>
#include <iostream>
#include <ostream>
#include <regex>

std::string getMemory(const std::string &inputFileName) {
    std::string lines;
    if (std::ifstream inputFile(inputFileName); inputFile.is_open()) {
        std::string line;
        while (getline(inputFile, line)) {
            lines += line;
        }
    }
    return lines;
}

std::vector<std::string> findInstructions(std::string memory, const std::regex &instructionRegex) {
    std::vector<std::string> instructions;

    const auto wordsBegin = std::sregex_iterator(memory.begin(), memory.end(), instructionRegex);
    const auto wordsEnd = std::sregex_iterator();

    for (std::sregex_iterator i = wordsBegin; i != wordsEnd; ++i) {
        const std::smatch &match = *i;
        std::string matchstr = match.str();
        instructions.push_back(matchstr);
    }
    return instructions;
}

int getMultiplicationResult(std::string instruction) {
    std::regex numberToMultiplyRegex("\\d{1,3}");

    auto wordsBegin = std::sregex_iterator(instruction.begin(), instruction.end(), numberToMultiplyRegex);
    auto wordsEnd = std::sregex_iterator();

    const std::smatch match = *wordsBegin;
    const std::smatch secondMatch = *(++wordsBegin);
    const std::string matchstr = match.str();
    const std::string secondmatchstr = secondMatch.str();

    return stoi(secondmatchstr) * stoi(matchstr);
}

void firstTask(const std::string &inputFileName) {
    std::regex instructionRegex(R"(mul\(\d{1,3}\,\d{1,3}\))");
    const std::string memory = getMemory(inputFileName);
    std::vector<std::string> instructions = findInstructions(memory, instructionRegex);
    int sum = 0;
    for (const auto &instruction: instructions) {
        sum += getMultiplicationResult(instruction);
    }
    std::cout << sum << std::endl;
}

void secondTask(const std::string &inputFileName) {
    std::regex instructionRegex(R"(do\(\)|don\'t\(\)|mul\(\d{1,3}\,\d{1,3}\))");
    const std::string memory = getMemory(inputFileName);
    std::vector<std::string> instructions = findInstructions(memory, instructionRegex);
    int sum = 0;
    bool flag = true;
    for (const auto &instruction: instructions) {
        if (instruction == "don't()") {
            flag = false;
        } else if (instruction == "do()") {
            flag = true;
        } else {
            if (flag) {
                sum += getMultiplicationResult(instruction);
            }
        }
    }

    std::cout << sum << std::endl;
}

int main() {
    std::cout << "Advent of Code 2024 - Day 03" << std::endl;
    firstTask("C:/Users/zuzuz/CLionProjects/advent-of-code-2024/day-03/myInput.txt");
    secondTask("C:/Users/zuzuz/CLionProjects/advent-of-code-2024/day-03/myInput.txt");
    return 0;
}
