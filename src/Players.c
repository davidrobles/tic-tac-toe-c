
#include <stdio.h>
#include <stdlib.h>
#include "Players.h"
#include <limits.h>

/////////////////
// MONTE CARLO //
/////////////////

int monteCarlo(Game *game) {
    int nMoves = game->num_moves(game);
    if (nMoves == 1)
        return 0;
    double outs[nMoves];
    for (int i = 0; i < nMoves; i++)
        outs[i] = 0;
    for (int i = 0; i < 10000; i++) {
        Game *new_game = game->copy(game);
        int move = i % nMoves;
        game->make_move(new_game, move);
        while (!game->is_over(new_game))
            game->make_move(new_game, rand() % game->num_moves(game));
        outs[move] += utility_func(new_game, game->cur_player(game));
    }
    int bestMove = -1;
    double bestScore = INT_MIN;
    for (int i = 0; i < nMoves; i++) {
        if (outs[i] > bestScore) {
            bestMove = i;
            bestScore = outs[i];
        }
    }
    return bestMove;
}

/////////////
// NEGAMAX //
/////////////

//int negamax(Game *game)
//{
//    Game *new_game = game->copy(game);
//    MoveScore *moveScore = negamax_search(new_game, 0, 25);
//    free(new_game);
//    int bestMove = moveScore->move;
//    free(moveScore);
//    return bestMove;
//}
//
//int *negamax_search(Game *game, int curDepth, int maxDepth)
//{
//    if (game->is_over(game) || curDepth == maxDepth) {
//        int *moveScore = (int *) malloc(sizeof(MoveScore));
//        moveScore[0] = -1;
//        moveScore[1] = utility_func(game, game->cur_player(game));
//        return moveScore;
//    }
//
//    int bestMove = -1;
//    double bestScore = INT_MIN;
//    int nMoves = game->num_moves(game);
//
//    for (int move = 0; move < nMoves; move++) {
//        Game *newGame = game->copy(game);
//        newGame->make_move(newGame, move);
//        int *recursedScore = negamax_search(newGame, curDepth + 1, maxDepth);
//        free(newGame);
//        double curScore = -recursedScore[1];
//        free(recursedScore);
//        if (curScore > bestScore) {
//            bestScore = curScore;
//            bestMove = move;
//        }
//    }
//
//    int *moveScore = (int *) malloc(2 * sizeof(int));
//    moveScore[0] = bestMove;
//    moveScore[1] = bestScore;
//
//    return moveScore;
//}

////////////////
// ALPHA BETA //
////////////////

//int alphaBeta(Game *game) {
//    Game *newGame = game->copy(game);
//    int *moveScore = abSearch(newGame, 0, -1000000, 1000000, 25);
//    free(newGame);
//    int bestMove = moveScore[0];
//    free(moveScore);
//    return bestMove;
//}
//
//int *abSearch(Game *game, int curDepth, int alpha, int beta, int maxDepth)
//{
//    if (game->is_over(game) || curDepth == maxDepth)
//    {
//        int *moveScore = (int *) malloc(sizeof(int) * 2);
//        moveScore[0] = -1;
//        moveScore[1] = utility_func(game, game->cur_player(game));
//        return moveScore;
//    }
//
//    int bestMove = -1;
//    double bestScore = -1000000;
//    int numberMoves = game->num_moves(game);
//
//    for (int i = 0; i < numberMoves; i++)
//    {
//        Game *newTic = game->copy(game);
//        game->make_move(newTic, i);
//        int *curMoveScore = abSearch(newTic, curDepth + 1, -beta, - ((alpha >= bestScore) ? alpha : bestScore), maxDepth);
//        free(newTic);
//        double curScore = -curMoveScore[1];
//        free(curMoveScore);
//
//        if (curScore > bestScore)
//        {
//            bestScore = curScore;
//            bestMove = i;
//
//            if (bestScore >= beta)
//            {
//                int *newMoveScore = (int *) malloc(2 * sizeof(int));
//                newMoveScore[0] = bestMove;
//                newMoveScore[1] = bestScore;
//                return newMoveScore;
//            }
//        }
//    }
//
//    int *newMoveScore = (int *) malloc(2 * sizeof(int));
//    newMoveScore[0] = bestMove;
//    newMoveScore[1] = bestScore;
//    return newMoveScore;
//}

double utility_func(Game *tic, int player) {
    if (!tic->is_over(tic))
        printf("Fucked!!!!!\n");
    Outcome *outs = tic->outcomes(tic);
    if (outs[player] == WIN) {
        free(outs);
        return 1.0;
    } else if (outs[player] == DRAW) {
        free(outs);
        return 0.0;
    } else if (outs[player] == LOSS) {
        free(outs);
        return -1.0;
    }
    printf("fucked!\n");
    free(outs);
    return 0.0;
}

int randPlayer(Game *game) {
    return rand() % game->num_moves(game);
}
