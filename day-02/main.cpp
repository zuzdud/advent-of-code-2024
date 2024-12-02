#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

std::vector<int> reportVector;

bool comp(int a, int b) {
    return a > b;
}

void firstTask(const std::string &inputFileName) {
    if (std::ifstream inputFile(inputFileName); inputFile.is_open()) {
        std::string line;
        int level;
        int safeReports = 0;

        while (getline(inputFile, line)) {
            std::stringstream sstream(line);
            int levelsCount = 0;

            while (sstream.rdbuf()->in_avail() != 0) {
                sstream >> level;
                levelsCount++;

                if (reportVector.empty()) {
                    reportVector.push_back(level);
                } else if (abs(reportVector.back() - level) <= 3 && reportVector.back() != level) {
                    reportVector.push_back(level);
                } else {
                    break;
                }
            }

            if (levelsCount > reportVector.size()) {
                reportVector.clear();
                continue;
            }

            if (std::is_sorted(reportVector.begin(), reportVector.end(), comp) || std::is_sorted(
                     reportVector.begin(), reportVector.end())) {
                safeReports += 1;
            }

            reportVector.clear();
        }
        std::cout << safeReports << std::endl;
    }
}

int main() {
    std::cout << "Advent of Code 2024 - Day 02" << std::endl;

    firstTask("C:/Users/zuzuz/CLionProjects/advent-of-code-2024/day-02/myInput.txt");
    return 0;
}
