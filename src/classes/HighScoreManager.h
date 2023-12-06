#include <vector>

class HighScoreManager {
public:
    HighScoreManager();
    void loadScores();
    void saveScores();
    void addScore(int newScore);
    const std::vector<int>& getScores() const;

private:
    std::vector<int> scores;
};