
#include <stdio.h>
#include <stdlib.h>
#include "GameUtil.h"

void play_games(Game* game, int (**players)(Game *), int nGames) {
    int results[3];
    results[0] = results[1] = results[2] = 0;
    for (int i = 0; i < nGames; i++) {
        game->reset(game);
        while (!game->is_over(game))
            game->make_move(game, players[game->cur_player(game)](game));
        Outcome *outs = game->outcomes(game);
        printf("Game %d: %d\n", i, outs[0]);
        if (outs[0] == WIN)
            results[0]++;
        else if (outs[0] == DRAW)
            results[1]++;
        else if (outs[0] == LOSS)
            results[2]++;
        free(outs);
    }
    printf("Results:\n\n");
    printf("Wins:   %d\n", results[0]);
    printf("Draws:  %d\n", results[1]);
    printf("Losses: %d\n", results[2]);
}

void play_game(Game* game, int (**players)(Game *)) {
    game->reset(game);
    game->display(game);
    while (!game->is_over(game)) {
        game->make_move(game, players[game->cur_player(game)](game));
        game->display(game);
    }
}