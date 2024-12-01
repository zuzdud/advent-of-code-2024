#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>


std::vector<int> firstVector;
std::vector<int> secondVector;
std::map<int, int> dict;

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

// second task
void readInputFileSecondTask(const std::string &inputFileName) {
    if (std::ifstream inputFile(inputFileName); inputFile.is_open()) {
        int secondNumber;
        int firstNumber;
        std::string line;
        while (getline(inputFile, line)) {
            std::stringstream sstream(line);
            sstream >> firstNumber >> secondNumber;

            firstVector.push_back(firstNumber);
            dict[secondNumber] = dict[secondNumber] + 1;
        }
    }
}

int getResultSecondTask() {
    int result = 0;
    for (int i : firstVector) {
        result += i * dict[i];
    }
    return result;
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

    // second task
    readInputFileSecondTask("C:/Users/zuzuz/CLionProjects/advent-of-code-2024/day-01/myInput.txt");
    std::cout << getResultSecondTask() << std::endl;

    return 0;
}