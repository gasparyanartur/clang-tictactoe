#include "player.h"

player_t get_other_player(player_t player) {
    switch (player) {
        case CROSS:
            return NAUGHT;
        case NAUGHT:
            return CROSS;
        default:
            return NO_PLAYER;
    }
}

bool is_player_t(player_t player) {
    return player <= NAUGHT;
}
