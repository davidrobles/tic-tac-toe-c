
#ifndef _PLAYERS_H_
#define _PLAYERS_H_

#include "games.h"

typedef struct MoveScore {
    int move;
    double score;
} MoveScore;

int randPlayer(Game *game);
int *abSearch(Game *game, int curDepth, int alpha, int beta, int maxDepth);
//int alphaBeta(Game *game);
double utility_func(Game *game, int player);
int monteCarlo(Game *game);
//int negamax(Game *game);
//int *negamaxSearch(Game *game, int curDepth, int maxDepth);

#endif
