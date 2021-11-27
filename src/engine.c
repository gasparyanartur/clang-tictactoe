#include "player.h"
#include "board.h"
#include <stdbool.h>
#include <stdio.h>
#include "engine.h"

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
uint_fast8_t get_move(gamestate_ptr gamestate);
bool is_current_player_human(gamestate_ptr gamestate);
uint_fast8_t get_human_move(gamestate_ptr gamestate);
uint_fast8_t get_ai_move(gamestate_ptr gamestate);

bool is_valid_move(gamestate_ptr gamestate, uint_fast8_t tile);

void process_gamestate(gamestate_ptr gamestate);

void print_game_result(gamestate_ptr gamestate);

/*
 * Public functions
 */
void run_game() {
    board_t board = {.tiles={0}, .remainingTiles=BOARD_SIZE};
    gamestate_t gamestate = {.board = &board, .isRunning=true, .winningPlayer=NO_PLAYER, .currentPlayer=PLAYER_X, .isHuman={true, true}};

    print_board(&board);
    while (gamestate.isRunning) {
        play_turn(&gamestate);
    }

    print_game_result(&gamestate);
}

/*
 * Private functions
 */
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

uint_fast8_t get_move(gamestate_ptr gamestate) {
    return is_current_player_human(gamestate) ? get_human_move(gamestate) : get_ai_move(gamestate);
}

bool is_current_player_human(gamestate_ptr gamestate) {
    return gamestate->isHuman[gamestate->currentPlayer - 1];
}

uint_fast8_t get_human_move(gamestate_ptr gamestate) {
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


uint_fast8_t get_ai_move(gamestate_ptr gamestate) {
    printf("Calling ai move despite it not being implemented.\n");
    return -1;
}

