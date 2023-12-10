#include <vector>
#include <algorithm>

class HighScoreManager {

public:
  HighScoreManager();
  
  void addScore(int newScore);

  const std::vector<int>& getScores() const;

private:
  std::vector<int> scores;

};