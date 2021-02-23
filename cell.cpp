#include "cell.h"
#include <QT>
#include "map.h"


Cell::Cell(const char* text, QWidget* parent, int row, int coln, Game& game) :
    QPushButton(text, parent), row(row), coln(coln), game(&game)
{
    if(text[0] == X || text[0] == O) // ���� ������ ���, ������ ����� ������
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
    setText(game->Move(row, coln)); // ������������� ����� � ������ ������ ��� � ������ ������
    setEnabled(false); // ������������� ������������� �������
}
