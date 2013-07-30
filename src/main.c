
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "TicTacToe.h"
#include "Players.h"
#include "GameUtil.h"

int main (int argc, const char * argv[])
{
    srand(time(NULL));
    TicTacToe tic;
    init_tic(&tic);
    Game *game = (Game *) &tic;
    game->display(game);

    while (!game->is_over(game)) {
        game->make_move(game, rand() % game->num_moves(game));
//        game->display(game);
    }

    // Players
//    int (*players[2])(Game *game);
//    players[0] = randPlayer;
//    players[1] = randPlayer;
//    play_game((Game *) &tic, players);
    
    return 0;
}
