#include "player.h"

player_t get_other_player(player_t player) {
    switch (player) {
        case PLAYER_X:
            return PLAYER_O;
        case PLAYER_O:
            return PLAYER_X;
        default:
            return NO_PLAYER;
    }
}

bool is_player_t(player_t player) {
    return player <= PLAYER_O;
}
