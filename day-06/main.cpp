#include <algorithm>
#include <fstream>
#include <iostream>
#include <ostream>
#include <set>
#include <vector>

using Matrix = std::vector<std::string>;

Matrix getMap(const std::string &inputFileName) {
    Matrix map;
    if (std::ifstream inputFile(inputFileName); inputFile.is_open()) {
        std::string line;
        while (getline(inputFile, line)) {
            map.push_back(line);
        }
    }
    return map;
}

void findObstacles(const Matrix &map, std::vector<std::pair<int, int> > &coordinates,
                   std::pair<int, int> &guardCoordinates) {
    for (int i = 0; i < map.size(); i++) {
        const std::string &line = map[i];
        for (int j = 0; j < line.size(); j++) {
            if (line[j] == '#') {
                coordinates.emplace_back(i, j);
            }
            if (line[j] == '^') {
                guardCoordinates = std::pair(i, j);
            }
        }
    }
}

std::set<std::pair<int, int> > findPatrolPath(std::pair<int, int> &guardCoordinates,
                                              const std::vector<std::pair<int, int> > &obstaclesCoordinates,
                                              const int maxLine, const int maxPosition) {
    std::set<std::pair<int, int> > patrolPath;
    char direction = 'U';

    while (guardCoordinates.first >= 0 && guardCoordinates.first < maxLine && guardCoordinates.second >= 0 &&
           guardCoordinates.second < maxPosition) {
        patrolPath.insert(guardCoordinates);

        if (direction == 'U') {
            guardCoordinates.first = guardCoordinates.first - 1;
        } else if (direction == 'D') {
            guardCoordinates.first = guardCoordinates.first + 1;
        } else if (direction == 'R') {
            guardCoordinates.second = guardCoordinates.second + 1;
        } else {
            guardCoordinates.second = guardCoordinates.second - 1;
        }

        if (std::find(obstaclesCoordinates.begin(), obstaclesCoordinates.end(), guardCoordinates) !=
            obstaclesCoordinates.end()) {
            if (direction == 'U') {
                guardCoordinates.first = guardCoordinates.first + 1;
                direction = 'R';
            } else if (direction == 'D') {
                guardCoordinates.first = guardCoordinates.first - 1;
                direction = 'L';
            } else if (direction == 'R') {
                guardCoordinates.second = guardCoordinates.second - 1;
                direction = 'D';
            } else {
                guardCoordinates.second = guardCoordinates.second + 1;
                direction = 'U';
            }
        }
    }

    return patrolPath;
}

std::set<std::pair<int, int> > findLoops(std::pair<int, int> &guardCoordinates,
                                         const std::vector<std::pair<int, int> > &obstaclesCoordinates,
                                         const int maxLine, const int maxPosition, bool &loop) {
    std::set<std::pair<int, int> > patrolPath;

    std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > steps;
    char direction = 'U';
    loop = false;
    while (guardCoordinates.first >= 0 && guardCoordinates.first < maxLine && guardCoordinates.second >= 0 &&
           guardCoordinates.second < maxPosition) {
        patrolPath.insert(guardCoordinates);
        std::pair root(guardCoordinates);

        if (direction == 'U') {
            guardCoordinates.first = guardCoordinates.first - 1;
        } else if (direction == 'D') {
            guardCoordinates.first = guardCoordinates.first + 1;
        } else if (direction == 'R') {
            guardCoordinates.second = guardCoordinates.second + 1;
        } else {
            guardCoordinates.second = guardCoordinates.second - 1;
        }

        if (std::find(obstaclesCoordinates.begin(), obstaclesCoordinates.end(), guardCoordinates) !=
            obstaclesCoordinates.end()) {
            if (direction == 'U') {
                guardCoordinates.first = guardCoordinates.first + 1;
                direction = 'R';
            } else if (direction == 'D') {
                guardCoordinates.first = guardCoordinates.first - 1;
                direction = 'L';
            } else if (direction == 'R') {
                guardCoordinates.second = guardCoordinates.second - 1;
                direction = 'D';
            } else {
                guardCoordinates.second = guardCoordinates.second + 1;
                direction = 'U';
            }
        } else {
            std::pair next(guardCoordinates);

            if (std::find(steps.begin(), steps.end(), std::pair(root, next)) != steps.end()) {
                loop = true;
                break;
            }
            steps.emplace_back(root, next);
        }
    }

    return patrolPath;
}

void firstTask(const std::string &inputFileName) {
    const Matrix map = getMap(inputFileName);

    std::vector<std::pair<int, int> > obstaclesCoordinates;
    std::pair<int, int> guardCoordinates;
    findObstacles(map, obstaclesCoordinates, guardCoordinates);

    const std::set<std::pair<int, int> > patrolPath = findPatrolPath(guardCoordinates, obstaclesCoordinates, map.size(),
                                                                     map[0].size());

    std::cout << patrolPath.size() << std::endl;
}

void secondTask(const std::string &inputFileName) {
    const Matrix map = getMap(inputFileName);

    std::vector<std::pair<int, int> > originalObstaclesCoordinates;
    std::pair<int, int> originalGuardCoordinates;

    findObstacles(map, originalObstaclesCoordinates, originalGuardCoordinates);

    const std::vector<std::pair<int, int> > obstaclesCoordinates = originalObstaclesCoordinates;
    const std::pair<int, int> guardCoordinates = originalGuardCoordinates;

    const std::set<std::pair<int, int> > patrolPath = findPatrolPath(originalGuardCoordinates,
                                                                     originalObstaclesCoordinates, map.size(),
                                                                     map[0].size());

    int loops = 0;
    for (auto pair: patrolPath) {
        std::vector<std::pair<int, int> > newObstacles = obstaclesCoordinates;
        std::pair<int, int> newGuard = guardCoordinates;
        newObstacles.push_back(pair);
        bool isloop = false;
        const std::set<std::pair<int, int> > newPatrolPath = findLoops(
            newGuard, newObstacles, map.size(),
            map[0].size(), isloop);
        if (isloop) {
            loops++;
        }
    }

    std::cout << loops << std::endl;
}


int main() {
    std::cout << "Advent of Code 2024 - Day 06" << std::endl;
    firstTask("C:/Users/zuzuz/CLionProjects/advent-of-code-2024/day-06/myInput.txt");
    secondTask("C:/Users/zuzuz/CLionProjects/advent-of-code-2024/day-06/myInput.txt");
    return 0;
}
