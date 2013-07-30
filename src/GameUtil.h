
#ifndef TicTacToeC_GameUtil_h
#define TicTacToeC_GameUtil_h

#include "games.h"

void play_game(Game *game, int (**players)(Game *));
void play_games(Game *game, int (**players)(Game *), int nGames);

#endif
