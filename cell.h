#ifndef CELL_H
#define CELL_H

#include <QPushButton>
#include "game.h"


class Cell : public QPushButton
{
    Q_OBJECT

    int row;
    int coln;

    Game* game;
public:
    explicit Cell(const char*, QWidget* parent, int row, int coln, Game& game);

public slots:
    void CellClicked();
};

#endif // CELL_H
