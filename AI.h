#ifndef AI_H
#define AI_H

#include <vector>
#include <map.h>
#include <cell.h>
#include <time.h>
#include <QApplication>

int MaxDepth = 6;
std::vector<int> bestMove(2,-1);
std::vector<int> curMove(2);
int MaxScore = -100;
int curScore;

int MaxSimb = MapSize;


int va = 0;

int checkLine(std::vector<char> line)
{
    int simv = 1;
    for(int i = 1; i < MapSize; i++)
    {
        if(line[i - 1] != line[i])
        {
            simv = 1;
            continue;
        }
        else if(line[i] != ' ')
        {
            simv++;
            if(simv == MaxSimb)
            {
                switch(line[i])
                {
                case X:
                    return -10;
                    break;
                case O:
                    return 10;
                    break;
                default:
                    return 0;
                    break;
                }
            }
        }

    }
    return 0;

//            return 0;
}

int CheckGameOver(std::vector<std::vector<char> > Map)
{
    std::vector<char> diag1(MapSize);
    std::vector<char> diag2(MapSize);
    std::vector<char> line(MapSize); // линия
    int win;
    for(int i = 0; i < MapSize; i++) {
        for(int j = 0; j < MapSize; j++) // проверка столбцов
            line[j] = Map[j][i];
        win = checkLine(line);
        if(win != 0) return win;

        win = checkLine(Map[i]);
        if(win != 0) return win; // проверка рядов
    }
    for(int i = 0; i < MapSize; i++)
    {
        diag1[i] = Map[i][i];
        diag2[i] = Map[MapSize - i - 1][i];
    }
    win = checkLine(diag1);
    if(win != 0) return win;

    win = checkLine(diag2);
    if(win != 0) return win;

    return 0;
}


int MinMax(std::vector<std::vector<char> > map, bool IsAIMove, int depth)
{
    std::vector<std::vector<char> > tmpMap = map;
    std::vector<int> moves(MapSize*MapSize, -100);
    if(depth != 1)
    {
        for(int i = 0; i < MapSize; i++)
            for(int j = 0; j < MapSize; j++)
                if(tmpMap[i][j] == ' ')
                {
                    if(IsAIMove) tmpMap[i][j] = O;
                    else tmpMap[i][j] = X;
                    curScore = CheckGameOver(tmpMap);
                    if(curScore != 0)
                    {
                        moves[i*MapSize + j] = curScore * (depth - depth%2);
                        tmpMap[i][j] = ' ';
                        continue;
                    }
                    moves[i*MapSize + j] = MinMax(tmpMap, !IsAIMove, depth -1);

                    tmpMap[i][j] = ' ';
                }
        if(IsAIMove)
        {
            int Move = -110;
            for(int i = moves.size() - 1; i >= 0; i--)
            {
                if(Move <= moves[i] && moves[i] != -100)
                {
                    Move = moves[i];
                    if(depth == MaxDepth)
                    {
                        bestMove[1] = i%MapSize;
                        bestMove[0] = (i - (i%MapSize))/MapSize;
                    }
                }
            }
            return Move;
        }
        else
        {
            int Move = 110;
            for(int i = moves.size() - 1; i >= 0; i--)
            {
                if(Move >= moves[i] && moves[i] != -100)
                {
                    Move = moves[i];
                }
            }
            return Move;
        }
    }
    else
    {
        for(int i = 0; i < MapSize; i++)
            for(int j = 0; j < MapSize; j++)
                if(tmpMap[i][j] == ' ')
                {
                    if(IsAIMove) tmpMap[i][j] = O;
                    else tmpMap[i][j] = X;
                    curScore = CheckGameOver(tmpMap);
                    moves[i*MapSize + j] = curScore;


                    tmpMap[i][j] = ' ';
                }

        int minMove = 11;
        for(int i = moves.size() - 1; i >= 0; i--)
        {
            if(minMove >= moves[i] && moves[i] != -100)
            {
                minMove = moves[i];
            }
        }
        return minMove;
    }
}


int AlphaBeta(std::vector<std::vector<char> > map, bool IsAIMove,
                    int depth, int alpha, int beta)
{
  std::vector<std::vector<char> > tmpMap = map;

  if (depth == 0)
  {
      int tmp = CheckGameOver(tmpMap) * 10;
      return tmp;
  }
  int score;
  int free_moves = 0;

  if(IsAIMove)
  {
      for(int i = 0; i < MapSize; i++)
      {
          for(int j = 0; j < MapSize; j++)
          {
              if(tmpMap[i][j] == ' ')
              {
                  free_moves++;
                  tmpMap[i][j] = O; //
                  curScore = CheckGameOver(tmpMap);
                  if(curScore != 0)
                  {
                      if(depth == MaxDepth)
                      {
                          bestMove[0] = i;
                          bestMove[1] = j;
                      }
                      tmpMap[i][j] = ' ';
                      return curScore*10 * (depth - depth%2);
                  }
                  score = AlphaBeta(tmpMap, !IsAIMove, depth - 1, alpha, beta);
                  tmpMap[i][j] = ' ';

                  if(score > alpha)
                  {
                      alpha = score;
                      bestMove[0] = i;
                      bestMove[1] = j;
                  }
                  if(alpha >= beta)
                  {
                      return alpha;
                  }
              }
          }
      }
      if(free_moves == 0 && curScore == 0) return 0;
      return alpha;
  }
  else
  {
      for(int i = 0; i < MapSize; i++)
      {
          for(int j = 0; j < MapSize; j++)
          {
              if(tmpMap[i][j] == ' ')
              {
                  free_moves++;
                  tmpMap[i][j] = X;
                  curScore = CheckGameOver(tmpMap);
                  if(curScore != 0)
                  {
                      if(depth == MaxDepth)
                      {
                          bestMove[0] = i;
                          bestMove[1] = j;
                      }
                      tmpMap[i][j] = ' ';
                      return curScore*10 * (depth);
                  }
                  score = AlphaBeta(tmpMap, !IsAIMove, depth - 1, alpha, beta);
                  tmpMap[i][j] = ' ';
                  if(score < beta)
                      beta = score;
                  if(alpha >= beta)
                  {
                      return beta;
                  }
              }
          }
      }
      if(free_moves == 0 && curScore == 0) return 0;
      return beta;
  }
}


int AlphaBetaNoOpt(std::vector<std::vector<char> > map, bool IsAIMove,
                    int depth, int alpha, int beta)
{
  std::vector<std::vector<char> > tmpMap = map;

  if (depth == 0)
  {
      int tmp = CheckGameOver(tmpMap) * 10;
      return tmp;
  }
  int score;
  int free_moves = 0;
  for(int i = 0; i < MapSize; i++)
  {
              for(int j = 0; j < MapSize; j++)
              {
                  if(tmpMap[i][j] == ' ')
                  {
//                      va++;
                      free_moves++;
                      if(IsAIMove) tmpMap[i][j] = O; //
                      else tmpMap[i][j] = X;            // вынести
                      curScore = CheckGameOver(tmpMap);
                      if(curScore != 0)
                      {
                          if(depth == MaxDepth)
                          {
                              bestMove[0] = i;
                              bestMove[1] = j;
                          }
                          tmpMap[i][j] = ' ';
                          return curScore*10 * (depth - depth%2);
                      }
                      score = AlphaBeta(tmpMap, !IsAIMove, depth - 1, alpha, beta);
                      tmpMap[i][j] = ' ';

                      if(IsAIMove) // вынести
                      {
                          if(score > alpha)
                          {
                              alpha = score;
                              bestMove[0] = i;
                              bestMove[1] = j;
                          }
                          if(alpha >= beta)
                          {
                              return alpha;
                          }
                      }
                      else //
                      {
                          if(score < beta)
                              beta = score;
                          if(alpha >= beta)
                          {
                              return beta;
                          }
                      }
                  }
              }
  }
  if(free_moves == 0 && curScore == 0) return 0;
  if(IsAIMove)
    return alpha;
  else
      return beta;
}



void AIMove(std::vector<std::vector<char> > *map, State *state)
{
    std::vector<std::vector<char> > tmpMap = *map;

    clock_t start = clock();
    AlphaBeta(tmpMap, true, MaxDepth, INT_MIN, INT_MAX);
//    MinMax(tmpMap, true, MaxDepth);
    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    qDebug() << "\n\n>" << seconds;
//    qDebug() << va;


    int row = bestMove[0];
    int col = bestMove[1];

    if((*map)[row][col] != ' ') { // проверяем клетку в куторую ходим
        QMessageBox::critical(NULL, "Error",
                              "You cant move to used cell");
    }

    switch (*state) { // чей ход
    case X_MOVE:
        (*map)[row][col] = X;
        *state = O_MOVE;
        break;

    case O_MOVE:
        (*map)[row][col] = O;
        *state = X_MOVE;
        break;

    default:
        ;
    }

    bestMove[0] = bestMove[1] = -1;

    cells[row][col]->setText(QString((*map)[row][col]));
    cells[row][col]->setEnabled(false);
}


#endif // AI_H
