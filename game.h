#ifndef GAME_H
#define GAME_H

#include <QString>
#include <vector>

const char X = 'X';
const char O = 'O';

enum State {
    X_MOVE,
    O_MOVE,
    X_WIN,
    O_WIN,
    DRAW
};

class Game
{
    State state;

public:
    Game();

    void newGame();

    std::vector<std::vector<char> > Map;


    const char* getCell(int i, int j);
    void resizeMap();
    void checkLine(std::vector<char> line);
    void checkGameOver();
    void gameOver();

    QString Move(int row, int col);
    State getState();

private:



};

#endif // GAME_H
