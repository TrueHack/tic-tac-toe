#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "stdio.h"
#include <QDebug>
#include "map.h"

void MainWindow::resizeCells() { // ресайз массива с кнопками
    cells.resize(MapSize);

    for(int i = 0; i < MapSize; ++i)
        cells[i].resize(MapSize);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resizeCells();
    NewGame();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Update() // обновление и отрисовка кнопок
{
    int cellSize = 600/MapSize; // параметры
    int cellSpace = 6;
    int topSpace = 110;
    int leftSpace = 90;

    for(int i = 0; i < cells.size(); ++i)
        for(int j = 0; j < cells[i].size(); ++j)
        {
            if(cells[i][j] != NULL)
                delete cells[i][j]; // очищаем массив, на случай старой игры
        }
    resizeCells();

    for(int i = 0; i < MapSize; i++)
        for(int j = 0; j < MapSize; j++)
        {
            cells[i][j] = new Cell(game.getCell(i, j), this, i, j, game); // заполняем кнопками
            cells[i][j]->setGeometry(
                        (cellSize + cellSpace) * j + leftSpace, // задаем геометрию кнопок
                        (cellSize + cellSpace) * i + topSpace,
                        cellSize, cellSize);

            cells[i][j]->setVisible(true);
//            cells[i][j]->setLayout(ui->verticalLayout);

            connect(cells[i][j], SIGNAL(clicked()),
                    cells[i][j], SLOT(CellClicked())); // подключаем сигнал от нажатия на кнопку к функции

            connect(cells[i][j], SIGNAL(clicked()), this, SLOT(Win()));

        }

}

void MainWindow::Win()
{
    if(game.getState() == O_WIN)
    {
        ui->winLable->setText("O WIN");
    }
    else if(game.getState() == X_WIN)
    {
        ui->winLable->setText("X WIN");
    }
    else if(game.getState() == DRAW)
    {
        ui->winLable->setText("DRAW");
    }
}

void MainWindow::NewGame()
{
    MapSize = ui->comboBox->currentText().toInt();
    game.newGame();
    Update();
}

void MainWindow::on_ButtonNewGame_clicked()
{
    if(game.getState() == O_MOVE) return;
    NewGame();
}

std::vector<std::vector<Cell*> > MainWindow::getCellsArray()
{
    return cells;
}


