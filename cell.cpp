#include "cell.h"
#include <QT>
#include "map.h"


Cell::Cell(const char* text, QWidget* parent, int row, int coln, Game& game) :
    QPushButton(text, parent), row(row), coln(coln), game(&game)
{
    if(text[0] == X || text[0] == O) // если ничего нет, кнопку можно нажать
        setEnabled(false);
    QFont f("Roman");
    f.setPixelSize(600/MapSize - 20);
    f.bold();
    f.AllUppercase;

    setFont(f);
}


void Cell::CellClicked()
{
    if(game->getState() == O_MOVE) return;
    setText(game->Move(row, coln)); // устанавливаем текст и заодно делаем ход в индекс кнопки
    setEnabled(false); // устанавливаем невозможность нажатия
}
