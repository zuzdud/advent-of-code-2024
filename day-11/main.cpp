#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <vector>
#include <bits/stdc++.h>

std::vector<long long> getInitialArrangement(const std::string &inputFileName) {
    std::vector<long long> initialArrangement;
    if (std::ifstream inputFile(inputFileName); inputFile.is_open()) {
        std::string line;
        long long stone;
        getline(inputFile, line);
        std::stringstream sstream(line);
        while (sstream.rdbuf()->in_avail() != 0) {
            sstream >> stone;
            initialArrangement.push_back(stone);
        }
    }
    return initialArrangement;
}

int countDigits(const long long n) { return floor(log10(n) + 1); }

std::vector<long long> rearrangeStones(const std::vector<long long> &initialArrangement) {
    std::vector<long long> newArrangement;
    for (const auto i: initialArrangement) {
        int digits = countDigits(i);
        if (i == 0) {
            newArrangement.push_back(1);
        } else if (digits % 2 == 0) {
            int halfDigits = digits/2;
            std::string s = std::to_string(i);
            newArrangement.push_back(std::stoll(s.substr(0, halfDigits)));
            newArrangement.push_back(std::stoll(s.substr(halfDigits, halfDigits)));
        } else {
            newArrangement.push_back(i * 2024);
        }
    }
    return newArrangement;
}

void firstTask(const std::string &inputFileName) {
    std::vector<long long> initialVector = getInitialArrangement(inputFileName);
    for (int i = 0; i < 75; i++) {
        std::cout << i << std::endl;
        initialVector = rearrangeStones(initialVector);
    }
    std::cout << initialVector.size();
}

int main() {
    std::cout << "Advent of Code 2024 - Day 11" << std::endl;
    firstTask("C:/Users/zuzuz/CLionProjects/advent-of-code-2024/day-11/myInput.txt");
    return 0;
}
