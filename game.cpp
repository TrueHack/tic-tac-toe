#include "game.h"
#include "map.h"
#include <QMessageBox>
#include <QTextStream>
#include <QDebug>
#include "AI.h"

Game::Game()
{
    newGame();
}

void Game::newGame()
{
    state = X_MOVE; // первыми ход€т ’
    resizeMap(); // провер€ем изменени€ в размерах карты

    for(int i = 0; i < MapSize; i++)
        for(int j = 0; j < MapSize; j++)
                Map[i][j] = ' '; // заполн€ем карту пустыми данными
}

void Game::resizeMap() // ресайз карты из чекбокса
{
    Map.resize(MapSize);

    for(int i = 0; i < MapSize; i++)
        Map[i].resize(MapSize);
}

const char* Game::getCell(int i, int j) { // получаем клетку по индексу
    static char buf[2]; //                      !!проверить объ€вление!!
    sprintf(buf, "%c", Map[i][j]);
    return buf;
}

QString Game::Move(int row, int col) // ход
{
    //    qDebug() << "move";
    if(Map[row][col] != ' ') { // провер€ем клетку в куторую ходим
        QMessageBox::critical(NULL, "Error",
                              "You cant move to used cell");
        return QString("!");
    }

    switch (state) { // чей ход
    case X_MOVE:
        Map[row][col] = X;
        state = O_MOVE;
        break;

    case O_MOVE:
        Map[row][col] = O;
        state = X_MOVE;
        break;

    default:
        return QString(" ");
    }
    checkGameOver(); // проверка победы
    if(state != DRAW && state != X_WIN && state != O_WIN)
    {
        AIMove(&Map, &state); // ход »»
        checkGameOver(); // проверка победы после хода »»
    }
    if(state == O_WIN)
    {
        qDebug() << "test123123";
    }
    return QString(Map[row][col]); // возвращаем значение в на карте дл€ записи в клетку
}


void Game::checkLine(std::vector<char> line)
{
    int simv = 1;
    for(int i = 1; i < MapSize; i++)
    {
        if(line[i - 1] == line[i] && line[i] != ' ')
        {
            simv++;
            if(simv == MaxSimb)
            {
                switch(line[i])
                {
                case X:
                    state = X_WIN;
                    break;
                case O:
                    state = O_WIN;
                    break;
                default:
                    return ;
                    break;
                }
            }
        }
        else
        {
            simv = 1;
            continue;
        }

    }
}

//void Game::checkLine(std::vector<char> line) { // проверка линии на полный р€д
//    for(int i = 1; i < MapSize; i++)
//        if(line[i - 1] != line[i])
//            return;

//    switch(line[0]) {
//    case X:
//        state = X_WIN;
//        break;

//    case O:
//        state = O_WIN;
//        break;

//    default:
//        break;
//    }
//}

void Game::checkGameOver() {
    std::vector<char> line(MapSize); // лини€

    for(int i = 0; i < MapSize; i++) // проверка основной диагонали
        line[i] = Map[i][i];

    checkLine(line);

    for(int i = 0; i < MapSize; i++) // проверка дополнительной диагорали
        line[i] = Map[MapSize - i - 1][i];
    checkLine(line);

    for(int i = 0; i < MapSize; i++) {
        for(int j = 0; j < MapSize; j++) // проверка столбцов
            line[j] = Map[j][i];
        checkLine(line);

    }

    for(int i = 0; i < MapSize; i++)
    {
        checkLine(Map[i]); // проверка р€дов
    }

    switch(state) {
    case X_WIN:
        gameOver(); // если кто то победил, вызываем gameOver
        return;
    case O_WIN:
        gameOver();
        return;

    default:
        ;
    }

    int empty = 0; // пустые клетки

    for(int i = 0; i < MapSize; i++)
        for(int j = 0; j < MapSize; j++)
            if(Map[i][j] == ' ')
                empty++;

//    qDebug() << "empty = " << empty;

    if(empty == 0) // если пустых не осталось, то ничь€
        state = DRAW;
        gameOver();
}

State Game::getState()
{
    return state;
}

void Game::gameOver()
{
    switch(state)
    {
    case X_WIN:
        qDebug() << "X_WIN"; // вывод победител€
        break;
    case O_WIN:
        qDebug() << "O_WIN";
        break;
    case DRAW:
        qDebug() << "DRAW";
        break;
    }

};
