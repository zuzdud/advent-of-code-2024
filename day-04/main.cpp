#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using Matrix = std::vector<std::string>;

Matrix getWordSearch(const std::string &inputFileName) {
    Matrix wordSearch;
    if (std::ifstream inputFile(inputFileName); inputFile.is_open()) {
        std::string line;
        std::string firstLine;
        while (getline(inputFile, line)) {
            if (wordSearch.empty()) {
                firstLine = "..." + std::string(line.size(), '.') + "...";
                wordSearch.push_back(firstLine);
                wordSearch.push_back(firstLine);
                wordSearch.push_back(firstLine);
            }
            wordSearch.push_back("..." + line + "...");

        }
        wordSearch.push_back(firstLine);
        wordSearch.push_back(firstLine);
        wordSearch.push_back(firstLine);
    }
    return wordSearch;
}

bool searchRight(const Matrix &wordSearch, const int rootLine, const int rootPosition) {
    if (wordSearch[rootLine][rootPosition + 1] == 'M' && wordSearch[rootLine][rootPosition + 2] == 'A' && wordSearch[
            rootLine][rootPosition + 3] == 'S') {
        return true;
    }
    return false;
}

bool searchLeft(const Matrix &wordSearch, const int rootLine, const int rootPosition) {
    if (wordSearch[rootLine][rootPosition - 1] == 'M' && wordSearch[rootLine][rootPosition - 2] == 'A' && wordSearch[
            rootLine][rootPosition - 3] == 'S') {
        return true;
    }
    return false;
}

bool searchDown(const Matrix &wordSearch, const int rootLine, const int rootPosition) {
    if (wordSearch[rootLine + 1][rootPosition] == 'M' && wordSearch[rootLine + 2][rootPosition] == 'A' && wordSearch[
            rootLine + 3][rootPosition] == 'S') {
        return true;
    }
    return false;
}

bool searchUp(const Matrix &wordSearch, const int rootLine, const int rootPosition) {
    if (wordSearch[rootLine - 1][rootPosition] == 'M' && wordSearch[rootLine - 2][rootPosition] == 'A' && wordSearch[
            rootLine - 3][rootPosition] == 'S') {
        return true;
    }
    return false;
}

bool searchRightUp(const Matrix &wordSearch, const int rootLine, const int rootPosition) {
    if (wordSearch[rootLine - 1][rootPosition + 1] == 'M' && wordSearch[rootLine - 2][rootPosition + 2] == 'A' &&
        wordSearch[
            rootLine - 3][rootPosition + 3] == 'S') {
        return true;
    }
    return false;
}

bool searchLeftUp(const Matrix &wordSearch, const int rootLine, const int rootPosition) {
    if (wordSearch[rootLine - 1][rootPosition - 1] == 'M' && wordSearch[rootLine - 2][rootPosition - 2] == 'A' &&
        wordSearch[
            rootLine - 3][rootPosition - 3] == 'S') {
        return true;
    }
    return false;
}

bool searchRightDown(const Matrix &wordSearch, const int rootLine, const int rootPosition) {
    if (wordSearch[rootLine + 1][rootPosition + 1] == 'M' && wordSearch[rootLine + 2][rootPosition + 2] == 'A' &&
        wordSearch[
            rootLine + 3][rootPosition + 3] == 'S') {
        return true;
    }
    return false;
}

bool searchLeftDown(const Matrix &wordSearch, const int rootLine, const int rootPosition) {
    if (wordSearch[rootLine + 1][rootPosition - 1] == 'M' && wordSearch[rootLine + 2][rootPosition - 2] == 'A' &&
        wordSearch[
            rootLine + 3][rootPosition - 3] == 'S') {
        return true;
    }
    return false;
}

int countOccurences(const Matrix &wordSearch) {
    int occurences = 0;
    for (int i = 3; i < wordSearch.size() - 3; i++) {
        const std::string& line = wordSearch[i];
        int res = 0;
        while ((res = line.find('X', res + 1)) !=
               std::string::npos) {

            if (res >= 3 && res <= line.size() - 3) {
                if (searchDown(wordSearch, i, res)) occurences++;
                if (searchUp(wordSearch, i, res)) occurences++;
                if (searchLeft(wordSearch, i, res)) occurences++;
                if (searchRight(wordSearch, i, res)) occurences++;
                if (searchRightDown(wordSearch, i, res)) occurences++;
                if (searchRightUp(wordSearch, i, res)) occurences++;
                if (searchLeftDown(wordSearch, i, res)) occurences++;
                if (searchLeftUp(wordSearch, i, res)) occurences++;
            }
        }
    }
    return occurences;
}

void firstTask(const std::string &inputFileName) {
    const Matrix wordSearch = getWordSearch(inputFileName);
    std::cout << countOccurences(wordSearch) << std::endl;
}


int main() {
    std::cout << "Advent of Code 2024 - Day 04" << std::endl;
    firstTask("C:/Users/zuzuz/CLionProjects/advent-of-code-2024/day-04/myInput.txt");
    return 0;
}
