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
    state = X_MOVE; // ������� ����� �
    resizeMap(); // ��������� ��������� � �������� �����

    for(int i = 0; i < MapSize; i++)
        for(int j = 0; j < MapSize; j++)
                Map[i][j] = ' '; // ��������� ����� ������� �������
}

void Game::resizeMap() // ������ ����� �� ��������
{
    Map.resize(MapSize);

    for(int i = 0; i < MapSize; i++)
        Map[i].resize(MapSize);
}

const char* Game::getCell(int i, int j) { // �������� ������ �� �������
    static char buf[2]; //                      !!��������� ����������!!
    sprintf(buf, "%c", Map[i][j]);
    return buf;
}

QString Game::Move(int row, int col) // ���
{
    //    qDebug() << "move";
    if(Map[row][col] != ' ') { // ��������� ������ � ������� �����
        QMessageBox::critical(NULL, "Error",
                              "You cant move to used cell");
        return QString("!");
    }

    switch (state) { // ��� ���
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
    checkGameOver(); // �������� ������
    if(state != DRAW && state != X_WIN && state != O_WIN)
    {
        AIMove(&Map, &state); // ��� ��
        checkGameOver(); // �������� ������ ����� ���� ��
    }
    if(state == O_WIN)
    {
        qDebug() << "test123123";
    }
    return QString(Map[row][col]); // ���������� �������� � �� ����� ��� ������ � ������
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

//void Game::checkLine(std::vector<char> line) { // �������� ����� �� ������ ���
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
    std::vector<char> line(MapSize); // �����

    for(int i = 0; i < MapSize; i++) // �������� �������� ���������
        line[i] = Map[i][i];

    checkLine(line);

    for(int i = 0; i < MapSize; i++) // �������� �������������� ���������
        line[i] = Map[MapSize - i - 1][i];
    checkLine(line);

    for(int i = 0; i < MapSize; i++) {
        for(int j = 0; j < MapSize; j++) // �������� ��������
            line[j] = Map[j][i];
        checkLine(line);

    }

    for(int i = 0; i < MapSize; i++)
    {
        checkLine(Map[i]); // �������� �����
    }

    switch(state) {
    case X_WIN:
        gameOver(); // ���� ��� �� �������, �������� gameOver
        return;
    case O_WIN:
        gameOver();
        return;

    default:
        ;
    }

    int empty = 0; // ������ ������

    for(int i = 0; i < MapSize; i++)
        for(int j = 0; j < MapSize; j++)
            if(Map[i][j] == ' ')
                empty++;

//    qDebug() << "empty = " << empty;

    if(empty == 0) // ���� ������ �� ��������, �� �����
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
        qDebug() << "X_WIN"; // ����� ����������
        break;
    case O_WIN:
        qDebug() << "O_WIN";
        break;
    case DRAW:
        qDebug() << "DRAW";
        break;
    }

};
