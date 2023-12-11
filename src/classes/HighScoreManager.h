// HighScoreManager.h

#ifndef HIGHSCOREMANAGER_H
#define HIGHSCOREMANAGER_H

#include <vector>
#include <utility>
#include <algorithm>
#include <iostream>

class HighScoreManager {
public:
    HighScoreManager();

    void addScore(const std::string& playerName, int newScore);

    const std::vector<std::pair<std::string, int>>& getScores() const;

private:
    std::vector<std::pair<std::string, int>> scoreEntries;
};

#endif // HIGHSCOREMANAGER_H
