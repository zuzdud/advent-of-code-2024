#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>

void getPageOrderingRules(const std::string &inputFileName, std::unordered_map<int, std::vector<int> > &rules,
                          std::vector<std::vector<int> > &pagesToProduce) {
    std::string lines;
    if (std::ifstream inputFile(inputFileName); inputFile.is_open()) {
        std::string line;
        while (getline(inputFile, line)) {
            std::istringstream ss(line);
            std::string value;
            if (std::string key; std::getline(ss, key, '|') && std::getline(ss, value)) {
                rules[std::stoi(key)].push_back(std::stoi(value));
            } else {
                if (!key.empty()) {
                    std::vector<int> pages;
                    std::stringstream test(key);
                    std::string segment;

                    while (std::getline(test, segment, ',')) {
                        pages.push_back(std::stoi(segment));
                    }
                    pagesToProduce.push_back(pages);
                }
            }
        }
    }
}

bool isCorrectlyOrdered(const std::vector<int> &update, std::unordered_map<int, std::vector<int> > &rules) {
    for (int i = 1; i < update.size(); i++) {
        int key = update[i];
        std::vector<int> rule = rules[key];

        for (int j = 0; j < i; j++) {
            if (std::find(rule.begin(), rule.end(), update[j]) != rule.end()) {
                return false;
            }
        }
    }
    return true;
}

void changeOrder(std::vector<int> &update, std::unordered_map<int, std::vector<int> > &rules) {
    for (int i = 1; i < update.size(); i++) {
        int key = update[i];
        std::vector<int> rule = rules[key];

        for (int j = 0; j < i; j++) {
            if (std::find(rule.begin(), rule.end(), update[j]) != rule.end()) {
                const int temp = update[j];
                update[j] = key;
                update[i] = temp;
                break;
            }
        }
    }
}

void firstPart(const std::string &inputFileName) {
    std::unordered_map<int, std::vector<int> > rules;
    std::vector<std::vector<int> > pagesToProduce;
    getPageOrderingRules(inputFileName, rules, pagesToProduce);

    int sum = 0;
    for (const auto &update: pagesToProduce) {
        if (isCorrectlyOrdered(update, rules)) {
            sum += update[update.size() / 2];
        }
    }
    std::cout << sum << std::endl;
}

void secondPart(const std::string &inputFileName) {
    std::unordered_map<int, std::vector<int> > rules;
    std::vector<std::vector<int> > pagesToProduce;
    getPageOrderingRules(inputFileName, rules, pagesToProduce);

    int sum = 0;
    for (auto &update: pagesToProduce) {
        if (!isCorrectlyOrdered(update, rules)) {
            while(!isCorrectlyOrdered(update, rules)) {
                changeOrder(update, rules);
            }
            sum += update[update.size() / 2];
        }
    }
    std::cout << sum << std::endl;
}

int main() {
    std::cout << "Advent of Code 2024 - Day 05" << std::endl;
    firstPart("C:/Users/zuzuz/CLionProjects/advent-of-code-2024/day-05/myInput.txt");
    secondPart("C:/Users/zuzuz/CLionProjects/advent-of-code-2024/day-05/myInput.txt");
    return 0;
}
