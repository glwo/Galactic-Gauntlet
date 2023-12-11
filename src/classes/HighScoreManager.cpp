#include "HighScoreManager.h"

HighScoreManager::HighScoreManager() {
    // Initialize with default entries
    scoreEntries = {{"Player1", 0}, {"Player2", 0}, {"Player3", 0}};
}

void HighScoreManager::addScore(const std::string& playerName, int newScore) {
    // Insert new score and name
    scoreEntries.push_back({playerName, newScore});

    // Sort in descending order based on scores
    std::sort(scoreEntries.begin(), scoreEntries.end(),
              [](const auto& a, const auto& b) { return a.second > b.second; });

    // Trim to max size of 3
    scoreEntries.resize(std::min(scoreEntries.size(), size_t(3)));

    // Display the updated scores
    std::cout << "High Scores:\n";
    for (const auto& entry : scoreEntries) {
        std::cout << entry.first << ": " << entry.second << "\n";
    }
}

const std::vector<std::pair<std::string, int>>& HighScoreManager::getScores() const {
    return scoreEntries;
}

