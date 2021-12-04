#include "player.h"
#include "board.h"
#include <stdbool.h>
#include <stdio.h>
#include <malloc.h>
#include <vcruntime_string.h>
#include "engine.h"
#include "ai.h"

/*
 * Private types
 */
typedef struct {
    board_ptr board;
    bool isRunning;
    player_t currentPlayer;
    player_t winningPlayer;
    bool isHuman[2];
} gamestate_t;

typedef gamestate_t *gamestate_ptr;

/*
 * Private function declaration
 */
void play_turn(gamestate_ptr gamestate);
tile_t get_move(gamestate_ptr gamestate);
bool is_current_player_human(gamestate_ptr gamestate);
tile_t get_human_move(gamestate_ptr gamestate);
tile_t get_ai_move(gamestate_ptr gamestate);
bool is_valid_move(gamestate_ptr gamestate, uint_fast8_t tile);
void process_gamestate(gamestate_ptr gamestate);
void print_game_result(gamestate_ptr gamestate);
gamestate_ptr create_gamestate(board_ptr board, bool player_one_is_human, bool player_two_is_human);
void destroy_gamestate(gamestate_ptr gamestate);

/*
 * Public functions
 */
void run_game() {
    tile_t tiles[BOARD_SIZE] = {0};
    board_ptr board = create_board(tiles);
    gamestate_ptr gamestate = create_gamestate(board, false, true);

    print_board(board);
     while (gamestate->isRunning) {
        play_turn(gamestate);
    }
    print_game_result(gamestate);
    destroy_gamestate(gamestate);
    destroy_board(board);
}

/*
 * Private functions
 */

gamestate_ptr create_gamestate(board_ptr board, bool player_one_is_human, bool player_two_is_human) {
    gamestate_ptr gamestate = malloc(sizeof(gamestate_t));

    gamestate->board = board;
    gamestate->isRunning = true;
    gamestate->currentPlayer = (board->remainingTiles % 2 == 0) ? PLAYER_O : PLAYER_X;
    gamestate->winningPlayer = NO_PLAYER;

    bool isHuman[] = {player_one_is_human, player_two_is_human};
    memcpy(gamestate->isHuman, isHuman, sizeof(bool[2]));

    return gamestate;
}

void destroy_gamestate(gamestate_ptr gamestate) {
    free(gamestate);
}

void play_turn(gamestate_ptr gamestate) {
    tile_t move = get_move(gamestate);
    take_tile(gamestate->board, move, gamestate->currentPlayer);

    process_gamestate(gamestate);

    print_board(gamestate->board);
}

void print_game_result(gamestate_ptr gamestate) {
    if (gamestate->winningPlayer == NO_PLAYER)
        printf("Game ended in draw. ");
    else
        printf("Game won by player %d. ", gamestate->winningPlayer);

    printf("Exiting program.\n");
}

void process_gamestate(gamestate_ptr gamestate) {
    gamestate->winningPlayer = get_winner(gamestate->board);
    if (gamestate->winningPlayer != NO_PLAYER || gamestate->board->remainingTiles == 0)
        gamestate->isRunning = false;
    else
        gamestate->currentPlayer = get_other_player(gamestate->currentPlayer);

}

tile_t get_move(gamestate_ptr gamestate) {
    return is_current_player_human(gamestate) ? get_human_move(gamestate) : get_ai_move(gamestate);
}

bool is_current_player_human(gamestate_ptr gamestate) {
    return gamestate->isHuman[gamestate->currentPlayer - 1];
}

tile_t get_human_move(gamestate_ptr gamestate) {
    int tile;
    while (1) {
        // TODO Handle string input
        printf("Select tile...\n");
        scanf_s("%d", &tile);
        if (is_valid_move(gamestate, tile))
            break;
        printf("Invalid input, try again.\n");
    }
    printf("Selecting tile: %d\n", tile);
    return tile;
}

bool is_valid_move(gamestate_ptr gamestate, tile_t tile) {
    return tile_in_board(tile) && is_tile_empty(gamestate->board, tile);
}


tile_t get_ai_move(gamestate_ptr gamestate) {
    tile_t tile = calculate_optimal_move(gamestate->board, gamestate->currentPlayer);
    printf("AI chose tile %d\n", tile);
    return tile;
}

