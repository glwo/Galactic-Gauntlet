// HighScoreManager.cpp
#include "HighScoreManager.h"
#include <fstream>
#include <algorithm>

HighScoreManager::HighScoreManager() : scores(3, 0) {
    loadScores();
}

void HighScoreManager::loadScores() {
    std::ifstream file("../highscores.txt");
    if (file.is_open()) {
        scores.clear();
        int score;
        while (file >> score) {
            scores.push_back(score);
        }
        file.close();
        // Sort scores in descending order.
        std::sort(scores.rbegin(), scores.rend());
        // Keep only the top three scores.
        scores.resize(3);
    }
    // Handle file I/O errors if needed.
}

void HighScoreManager::saveScores() {
    std::ofstream file("../highscores.txt");
    if (file.is_open()) {
        // Write scores to the file.
        for (const auto& score : scores) {
            file << score << "\n";
        }
        file.close();
    }
    // Handle file I/O errors if needed.
}

void HighScoreManager::addScore(int newScore) {
    // Check if the new score is higher than the lowest current high score.
    if (newScore > scores.back()) {
        // Replace the lowest score with the new high score.
        scores.back() = newScore;
        // Sort scores in descending order.
        std::sort(scores.rbegin(), scores.rend());
        // Save the updated scores to the file.
        saveScores();
    }
}

const std::vector<int>& HighScoreManager::getScores() const {
    return scores;
}
