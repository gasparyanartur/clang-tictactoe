#include "player.h"
#include "board.h"
#include <stdbool.h>
#include <stdio.h>
#include <malloc.h>
#include <vcruntime_string.h>
#include "engine.h"
#include "ai.h"

typedef struct {
    board_ptr board;
    bool isRunning;
    player_t currentPlayer;
    player_t winningPlayer;
    bool isHuman[2];
} gamestate_t;

typedef gamestate_t *gamestate_ptr;

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
gamestate_ptr setup_gamestate(board_ptr board);

bool get_continue_status(gamestate_ptr gamestate);

void run_game() {
    while (true) {
        tile_t tiles[BOARD_SIZE] = {0};
        board_ptr board = create_board(tiles);
        gamestate_ptr gamestate = setup_gamestate(board);

        print_board(board);
        while (gamestate->isRunning)
            play_turn(gamestate);

        print_game_result(gamestate);
        bool running = get_continue_status(gamestate);
        destroy_gamestate(gamestate);
        destroy_board(board);
        if (!running)
            break;
    }
}

bool get_continue_status(gamestate_ptr gamestate) {
    int state;
    while (true) {
        printf("Play again or exit?\n");
        printf("\t0: play again\n\t1: exit\n");
        scanf_s("%d", &state);
        if (state == 0 || state == 1)
            break;
        printf("Invalid input. Try again.\n");
    }
    if (state == 0) {
        printf("Restarting game.\n");
        return true;
    } else {
        printf("Exiting game.\n");
        gamestate->isRunning = false;
        return false;
    }

}

gamestate_ptr setup_gamestate(board_ptr board) {
    int state;
    while (true) {
        printf("Two players or vs AI?\nEnter the following number to choose game mode:\n");
        printf("\t0: player vs player\n\t1: player vs AI\n\t2: AI vs player\n\t3: AI vs AI\n");
        scanf_s("%d", &state);
        if (state >= 0 && state <= 3)
            break;
        
        printf("Invalid state. Try again.\n");
    }
    bool human1 = false;
    bool human2 = false;
    switch (state) {
        case 0:
            human1 = true;
            human2 = true;
            break;
        case 1:
            human1 = true;
            break;
        case 2:
            human2 = true;
            break;
        default:
            break;
    }

    return create_gamestate(board, human1, human2);
}

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
        printf("Game ended in draw.\n");
    else
        printf("Game won by player %d.\n", gamestate->winningPlayer);

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

