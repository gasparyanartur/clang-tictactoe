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
    if (is_current_player_human(gamestate)) {
        int t;
        printf("Select tile...\n");
        scanf_s("%d", &t);
        printf("Selecting tile: %d\n", t);
    }

    return 0;
}

bool is_current_player_human(const gamestate_t *gamestate) { return gamestate->isHuman[gamestate->currentPlayer - 1]; }

