#ifndef LEVEL_MANAGER_H
#define LEVEL_MANAGER_H

class StatsManager {
private:
    long long score;
    int level;
    int linesCleared;
    
    static int linesPerLevel;
    static constexpr float baseSpeed = 1.0f; // Base speed for level 1
    static constexpr float speedIncrement = 0.1f; // Speed increment per level
    
public:

    static float scoreMult;

    StatsManager();

    int getScore() const;
    int getCurrentLevel() const;
    float getGameSpeed() const;
    int getLinesCleared() const;
    
    void levelUp();
    void increaseLinesCleared(int);
    void addScore(int);

    void reset();
};

#endif // LEVEL_MANAGER_H