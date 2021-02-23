#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "game.h"
#include "vector"
#include "cell.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void resizeCells();
    std::vector<std::vector<Cell*> > getCellsArray();

private slots:

    void NewGame();
    void Update();

    void Win();

    void on_ButtonNewGame_clicked();

private:
    Ui::MainWindow *ui;
    Game game;

};

#endif // MAINWINDOW_H
