#include "HighScoreManager.h"
#include <iostream>

HighScoreManager::HighScoreManager() : 
  scores{0, 0, 0} {
}

void HighScoreManager::addScore(int newScore) {

  // Insert new score   
  std::cout << "Before: ";
  for(int score : scores) {
    std::cout << score << " "; 
  }
  std::cout << "\n";
  scores.push_back(newScore);
  
  // Sort and trim vector
  std::sort(scores.rbegin(), scores.rend()); 
  scores.resize(std::min(scores.size(), size_t(3)));

  std::cout << "After: ";
  for(int score : scores) {
    std::cout << score << " ";
  }
  std::cout << "\n";
}

const std::vector<int>& HighScoreManager::getScores() const {
  return scores;
}

