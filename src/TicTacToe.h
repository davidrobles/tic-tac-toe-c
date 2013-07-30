
#ifndef _TIC_TAC_TOE_H_
#define _TIC_TAC_TOE_H_

#include <stdio.h>
#include <stdbool.h>
#include "games.h"

#define CELLS 9

typedef struct _TicTacToe {
    int crosses, noughts;
    // Game Interface
    Game* (*copy)(Game *game);
    int (*cur_player)(Game *game);
    bool (*is_over)(Game *game);
    void (*make_move)(Game *game, int move);
    Game* (*new_instance)();
    int (*num_moves)(Game *game);
    int (*num_players)();
    Outcome* (*outcomes)(Game *tic);
    void (*reset)(Game *game);
    void (*display)(Game *game);
} TicTacToe;

////////////////////
// Game Interface //
////////////////////

Game *copy(Game *game);
int cur_player(Game *game);
bool is_over(Game *game);
void make_move(Game *game, int move);
Game *new_instance();
int num_moves(Game *game);
int num_players();
Outcome* outcomes(Game *tic);
void reset(Game *game);
void display(Game *game);

// TicTacToe
void init_tic(TicTacToe *tic);
int* bit_moves(TicTacToe *tic);
bool check_win(int board);
int cur_board(TicTacToe *tic);
bool is_win(TicTacToe *tic);
int* legal_moves(TicTacToe *tic);
int count_bits(int i);
void print_outcome(Outcome outcome);
void set_cur_board(TicTacToe *tic, int board);
int empty_cells(TicTacToe *tic);

#endif
