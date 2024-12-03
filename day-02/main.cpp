#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

std::vector<int> reportVector;
std::vector<int> secondReportVector;

bool comp(int a, int b) {
    return a > b;
}

bool isSafe(std::vector<int> report) {
    if ((std::is_sorted(report.begin(), report.end(), comp) || std::is_sorted(
             report.begin(),
             report.end())) && std::adjacent_find(report.begin(), report.end()) == report.end()) {
        for (int i = 0; i < report.size() - 1; i++) {
            if (abs(report[i] - report[i + 1]) > 3) {
                return false;
            }
        }
        return true;
             }
    return false;
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

void secondTask(const std::string &inputFileName) {
    if (std::ifstream inputFile(inputFileName); inputFile.is_open()) {
        std::string line;
        int level;
        int safeReports = 0;


        while (getline(inputFile, line)) {
            std::stringstream sstream(line);

            while (sstream.rdbuf()->in_avail() != 0) {
                sstream >> level;
                secondReportVector.push_back(level);
            }

            if (isSafe(secondReportVector)) {
                safeReports++;
            } else {
                for (int i = 0; i < secondReportVector.size(); i++) {
                    std::vector<int> reportVectorCopy = secondReportVector;
                    reportVectorCopy.erase(reportVectorCopy.begin() + i);
                    if (isSafe(reportVectorCopy)) {
                        safeReports++;
                        break;
                    }
                    reportVectorCopy.clear();
                }
                secondReportVector.clear();
            }
            secondReportVector.clear();
        }
        std::cout << safeReports << std::endl;
    }
}

int main() {
    std::cout << "Advent of Code 2024 - Day 02" << std::endl;
    firstTask("C:/Users/zuzuz/CLionProjects/advent-of-code-2024/day-02/myInput.txt");
    secondTask("C:/Users/zuzuz/CLionProjects/advent-of-code-2024/day-02/myInput.txt");
    return 0;
}
