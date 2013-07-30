
#ifndef _games_h
#define _games_h

#include <stdbool.h>

typedef enum {
    WIN, DRAW, LOSS, UNFINISHED
} Outcome;

typedef struct Game {
    struct Game* (*copy)(struct Game *game);
    int (*cur_player)(struct Game *game);
    bool (*is_over)(struct Game *game);
    void (*make_move)(struct Game *game, int move);
    struct Game (*new_instance)(struct Game *game);
    int (*num_moves)(struct Game *game);
    int (*num_players)(struct Game *game);
    Outcome* (*outcomes)(struct Game *tic);
    void (*reset)(struct Game *game);
    void (*display)(struct Game *game);
} Game;

#endif
