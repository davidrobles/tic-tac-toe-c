
#include "TicTacToe.h"
#include <stdlib.h>

int wins[8] = {7, 56, 448, 73, 146, 292, 273, 84};

Game *copy(Game *game) {
    TicTacToe *newTic = (TicTacToe *) malloc(sizeof(TicTacToe));
    newTic->crosses = ((TicTacToe *) game)->crosses;
    newTic->noughts = ((TicTacToe *) game)->noughts;
    return (Game *) newTic;
}

int cur_player(Game *game) {
    return (empty_cells((TicTacToe *) game) + 1) % 2;
}

bool is_over(Game *game) {
    return num_moves(game) == 0;
}

void make_move(Game *game, int move) {
    if (move < 0 || move >= num_moves(game))
        printf("Illegal move\n");
    int *bit_ms = bit_moves((TicTacToe *) game);
    set_cur_board((TicTacToe *) game, cur_board((TicTacToe *) game) | bit_ms[move]);
    free(bit_ms);
}

int num_moves(Game *game) {
    return is_win((TicTacToe *) game) ? 0 : empty_cells((TicTacToe *) game);
}

Game *new_instance() {
    TicTacToe *tic = (TicTacToe *) malloc(sizeof(TicTacToe));
    init_tic(tic);
    return (Game *) tic;
}

int num_players() {
    return 2;
}

Outcome* outcomes(Game *game) {
    Outcome *outcomes = (Outcome *) malloc(sizeof(Outcome) * 2);
    if (!is_over(game)) {
        outcomes[0] = outcomes[1] = UNFINISHED;
    } else if (check_win(((TicTacToe *) game)->crosses)) {
        outcomes[0] = WIN;
        outcomes[1] = LOSS;
    } else if (check_win(((TicTacToe *) game)->noughts)) {
        outcomes[0] = LOSS;
        outcomes[1] = WIN;
    } else {
        outcomes[0] = outcomes[1] = DRAW;
    }
    return outcomes;
}

void reset(Game *game) {
    ((TicTacToe *) game)->crosses = ((TicTacToe *) game)->noughts = 0;
}

/////////////////
// Tic Tac Toe //
/////////////////

void init_tic(TicTacToe *tic) {
    tic->copy = copy;
    tic->crosses = tic->noughts = 0;
    tic->cur_player = cur_player;
    tic->display = display;
    tic->is_over = is_over;
    tic->outcomes = outcomes;
    tic->make_move = make_move;
    tic->new_instance = new_instance;
    tic->num_moves = num_moves;
    tic->num_players = num_players;
    tic->reset = reset;
}

int empty_cells(TicTacToe *tic) {
    return CELLS - count_bits(tic->crosses | tic->noughts);
}

int count_bits(int i) {
    i = i - ((i >> 1) & 0x55555555);
    i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
    return (((i + (i >> 4)) & 0x0F0F0F0F) * 0x01010101) >> 24;
}

int cur_board(TicTacToe *tic) {
    return cur_player((Game *) tic) == 0 ? tic->crosses : tic->noughts;
}

void set_cur_board(TicTacToe *tic, int board) {
    if (cur_player((Game *) tic) == 0)
        tic->crosses = board;
    else
        tic->noughts = board;
}

int* bit_moves(TicTacToe *tic) {
    int numMoves = num_moves((Game *) tic);
    int *legals = legal_moves(tic);
    int *bitMoves = (int *) malloc(sizeof(int) * numMoves);
    for (int i = 0; i < numMoves; i++)
        bitMoves[i] = (1 << legals[i]);
    free(legals);
    return bitMoves;
}

bool is_win(TicTacToe *tic) {
    return check_win(tic->crosses) || check_win(tic->noughts);
}

bool check_win(int board) {
    for (int i = 0; i < 8; i++)
        if ((board & wins[i]) == wins[i])
            return true;
    return false;
}

int* legal_moves(TicTacToe *tic) {
    int nMoves = num_moves((Game *) tic);
    int *moves = (int *) malloc(sizeof(int) * nMoves);
    if (nMoves > 0) {
        int legal = ~(tic->crosses | tic->noughts);
        for (int i = 0, count = 0; i < 9; i++)
            if (legal & (1 << i))
                moves[count++] = i;
    }
    return moves;
}

void display(Game *game) {
    if (is_over(game)) {
        printf("Game over!");
    } else {
        printf("Next player: %d\n", cur_player(game));
        printf("Legal moves: %d\n", num_moves(game));
        printf("Moves: [");
        int *moves = legal_moves((TicTacToe *) game);
        int nMoves = num_moves(game);
        for (int i = 0; i < nMoves; i++)
            printf("%d, ", moves[i]);
        free(moves);
        printf("]");
    }
    printf("\n\n");
    for (int i = 0; i < 9; i++) {
        if (((TicTacToe *) game)->crosses & (1 << i))
            printf(" X ");
        else if (((TicTacToe *) game)->noughts & (1 << i))
            printf(" O ");
        else
            printf(" - ");
        if (i % 3 == 2)
            printf("\n");
    }
    printf("\n");
    if (is_over(game)) {
        Outcome *outs = outcomes(game);
        printf("Player 1: ");
        print_outcome(outs[0]);
        printf("\nPlayer 2: ");
        print_outcome(outs[1]);
        free(outs);
        printf("\n");
    }
}

void print_outcome(Outcome outcome) {
    if (outcome == WIN)
        printf("Win");
    else if (outcome == LOSS)
        printf("Loss");
    else if (outcome == DRAW)
        printf("Draw");
    else if (outcome == UNFINISHED)
        printf("UNFINISHED");
}

