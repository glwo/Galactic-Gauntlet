// HighScoreManager.cpp
#include "HighScoreManager.h"
#include <fstream>
#include <algorithm>

HighScoreManager::HighScoreManager() : scores(3, 0) {
    loadScores();
}

void HighScoreManager::loadScores() {
    // Load scores from a file, handle file I/O errors.
    // Example: ifstream file("highscores.txt");
    // Read scores into the 'scores' vector.
}

void HighScoreManager::saveScores() {
    // Save scores to a file, handle file I/O errors.
    // Example: ofstream file("highscores.txt");
    // Write scores from the 'scores' vector.
}

void HighScoreManager::addScore(int newScore) {
    // Add a new score to the 'scores' vector.
    scores.push_back(newScore);
    // Sort scores in descending order.
    std::sort(scores.rbegin(), scores.rend());
    // Keep only the top three scores.
    scores.resize(3);
}

const std::vector<int>& HighScoreManager::getScores() const {
    return scores;
}
