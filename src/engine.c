#include "player.h"
#include "board.h"
#include <stdbool.h>
#include <stdio.h>
#include "engine.h"

/*
 * Private types
 */
typedef enum {
    GAME_RUNNING
} gamestatus_t;

typedef struct {
    gamestatus_t status;
    player_t currentPlayer;
    bool isHuman[2];
} gamestate_t;

typedef gamestate_t* gamestate_ptr;

/*
 * Private function declaration
 */
void play_turn(gamestate_ptr gamestate, board_ptr board);
uint_fast8_t get_move(gamestate_ptr gamestate);
bool is_current_player_human(const gamestate_t *gamestate);
uint_fast8_t get_human_move(gamestate_ptr gamestate);
uint_fast8_t get_ai_move(gamestate_ptr gamestate);

/*
 * Public functions
 */
void run_game() {
    gamestate_t gamestate = {.status=GAME_RUNNING, .currentPlayer=NAUGHT, .isHuman={true, true}};
    board_t board = {.tiles={0}, .remainingTiles=0};

    while (gamestate.status == GAME_RUNNING) {
        play_turn(&gamestate, &board);
    }
}

/*
 * Private functions
 */
void play_turn(gamestate_ptr gamestate, board_ptr board) {
    uint_fast8_t move = get_move(gamestate);
}

uint_fast8_t get_move(gamestate_ptr gamestate) {
    return is_current_player_human(gamestate) ? get_human_move(gamestate) : get_ai_move(gamestate);
}

bool is_current_player_human(const gamestate_t *gamestate) {
    return gamestate->isHuman[gamestate->currentPlayer - 1];
}

uint_fast8_t get_human_move(gamestate_ptr gamestate) {
    int tile;
    while (1) {
        printf("Select tile...\n");
        scanf_s("%d", &tile);
        if (tile_in_board(tile))
            break;
        printf("Invalid input, try again.\n");
    }
    printf("Selecting tile: %d\n", tile);
    return tile;
}

uint_fast8_t get_ai_move(gamestate_ptr gamestate) {
    printf("Calling ai move despite it not being implemented.\n");
    return -1;
}


