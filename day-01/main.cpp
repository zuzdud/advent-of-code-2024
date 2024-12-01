#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>


std::vector<int> firstVector;
std::vector<int> secondVector;

// first task
void readInputFileFirstTask(const std::string &inputFileName) {
    if (std::ifstream inputFile(inputFileName); inputFile.is_open()) {
        int secondNumber;
        int firstNumber;
        std::string line;
        while (getline(inputFile, line)) {
            std::stringstream sstream(line);
            sstream >> firstNumber >> secondNumber;

            firstVector.push_back(firstNumber);
            secondVector.push_back(secondNumber);
        }
    }
}

int getResultsFirstTask() {
    int result = 0;
    std::sort(firstVector.begin(), firstVector.end());
    std::sort(secondVector.begin(), secondVector.end());

    for (int i = 0; i < firstVector.size(); i++) {
        result += abs(firstVector[i] - secondVector[i]);
    }
    return result;
}
int main() {
    std::cout << "Advent of Code 2024 - Day 01" << std::endl;
    // first task
    readInputFileFirstTask("C:/Users/zuzuz/CLionProjects/advent-of-code-2024/day-01/myInput.txt");
    std::cout << getResultsFirstTask() << std::endl;

    return 0;
}